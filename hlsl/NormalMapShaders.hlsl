#include "Light.hlsl"
#include "Common.hlsl"

struct VS_NORMALMAP_IN {
	float3 position : POSITION;	// ���� ����
	float3 normal : NORMAL;		// ������ ���� ���� ����
	float2 uv : TEXCOORD;		// �ؽ��� ����
	float3 tangentU : TANGENT;	// ���� ����
};

struct VS_NORMALMAP_OUT {
	float4 positionH : SV_POSITION;
	float3 positionW : POSITION;
	float3 normal : NORMAL;
	float3 tangentW : TANGENT;
	float2 uv : TEXCOORD;
};

Texture2D gNormalTex : register(t6);
Texture2D gTexture : register(t7);
SamplerState gNormalState : register(s3);

struct MATERIALDATA
{
	float4		m_cDiffuseAlbedo;	// �л� �ݻ���
	float3		m_vFresnelR0;		// �ݻ籤 
	float		m_fRoughness;		// ǥ�� ��ĥ�� 
	float4x4	m_mMatTransform;	// ���׸��� ��ȯ ��� 
};

VS_NORMALMAP_OUT VS_Normal(VS_NORMALMAP_IN input)
{
	VS_NORMALMAP_OUT output;
	
	MATERIALDATA material = gMaterialData[gnMaterial];

	float4 posW = mul(float4(input.position, 1.0f), gmtxGameObject);
	output.positionW = posW.xyz;

	output.normal = mul(input.normal, (float3x3)gmtxGameObject);
	output.tangentW = mul(input.tangentU, (float3x3)gmtxGameObject);

	output.positionH = mul(mul(float4(input.position, 1.0f), gmtxView), gmtxProjection);
	output.uv = input.uv;
	//float4 uv = mul(float4(input.uv, 0.0f, 1.0f), gmtxGameObject);
	//output.uv = uv;

	return output;
}

float4 PS_Normal(VS_NORMALMAP_OUT input)
{
	MATERIALDATA material = gMaterialData[gnMaterial];
	float4 diffuseAlbedo = material.m_cDiffuseAlbedo;

	input.NormalW = normalize(input.NormalW);

	float4 normalMapSample = gNormalTex.Sample(gNormalState, input.uv);	// �븻�� ������ ���Ѵ�.
	float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample.rgb, input.normalW, input.tangentW);	// ���� ���͸� ���� ��ǥ��� ����

	diffuseAlbedo *= bumpedNormalW;

	float3 toEyeW = normalize(gvCameraPosition - input.position);
	float4 ambient = gcGlobalAmbientLight * diffuseAlbedo;

	const float shininess = (1.0f - m_fRoughness) * normalMapSample.a;
	Material mat = { diffuseAlbedo, m_vFresnelR0, shininess };
	float3 shaowFactor = 1.0f;
	float4 directionLight = ComputeLighiting(gLights, mat, input.positionW, bumpedNormalW, toEyeW, shadowFactor);
	
	float4 litColor = ambient + directionLight;

	float3 r = reflect(-toEyeW, bumpedNormalW);
	float4 reflectionColor = gTexture.Sample(gNormalState, input.uv);
	float3 fresnelFactor = SchlickFresnel(fresnelR0, bumpedNormalW, r);
	litColor.rgb += shininess * fresnelFactor * reflectionColor.rgb;

	litColor.a = diffuseAlbedo.a;

	return litColor;
}