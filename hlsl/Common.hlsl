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
	// 노말맵 색상을 읽어와 각 [ 0, 1 ]의 성분을 [ -1 , 1 ]로 변경
	float3 normalT = 2.0f * normalMapSample - 1.0f;

	float3 N = unitNormalW;
	// 그람 슈미트의 직교 정규화 
	float3 T = normalize(tangentW - dot(tangentW, N) * N); 
	float3 B = cross(N, T);

	float3x3 TBN = float3x3(T, B, N);

	// [ -1, 1 ]로 사상한 노말맵의 법선 백터를 월드 좌표계로 변환
	float3 bumpedNormalW = mul(normalT, TBN);

	return bumpedNormalW;
}