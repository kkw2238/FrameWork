cbuffer cbPlayerInfo : register(b0)
{
	matrix		gmtxPlayerWorld : packoffset(c0);
};

cbuffer cbCameraInfo : register(b1)
{
	matrix		gmtxView : packoffset(c0);
	matrix		gmtxProjection : packoffset(c4);
	float3		gvCameraPosition : packoffset(c8);
};

cbuffer cbGameObjectInfo : register(b2)
{
	matrix		gmtxGameObject : packoffset(c0);
	matrix		gmtxTexMatrix : packoffset(c4);
	uint		gnMaterial : packoffset(c8);
};

cbuffer cbBillBoardInfo : register(b6)
{
	matrix		gmtxBillBoard : packoffset(c0);
	uint		gnBillBoardMaterial : packoffset(c4);
};

cbuffer cbPass : register(b7)
{
	float4x4 gView;
	float4x4 gProj;
	float4x4 gInvProj;
	float4x4 gViewProj;
	float4x4 gInvViewProj;
	float3	 gEyePosW;
	float	 cbPerObjectPad1;
	float2	 gRenderTargetSize;
	float2	 gInvRenderTargetSize;
	float	 gNearZ;
	float	 gFarZ;
	float	 gTotalTime;
	float	 gDeltaTime;
	float4   gAmbientLight;
}

float3 NormalSampleToWorldSpace(float3 normalMapSample, float3 unitNormalW, float3 tangentW) 
{
	// �븻�� ������ �о�� �� [ 0, 1 ]�� ������ [ -1 , 1 ]�� ����
	float3 normalT = 2.0f * normalMapSample - 1.0f;

	float3 N = unitNormalW;
	// �׶� ����Ʈ�� ���� ����ȭ 
	float3 T = normalize(tangentW - dot(tangentW, N) * N); 
	float3 B = cross(N, T);

	float3x3 TBN = float3x3(T, B, N);

	// [ -1, 1 ]�� ����� �븻���� ���� ���͸� ���� ��ǥ��� ��ȯ
	float3 bumpedNormalW = mul(normalT, TBN);

	return bumpedNormalW;
}