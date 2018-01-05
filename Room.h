#pragma once

#include "Shader.h"
#include "Player.h"

struct LIGHT
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular;
	XMFLOAT3				m_xmf3Position;
	float 					m_fFalloff;
	XMFLOAT3				m_xmf3Direction;
	float 					m_fTheta; //cos(m_fTheta)
	XMFLOAT3				m_xmf3Attenuation;
	float					m_fPhi; //cos(m_fPhi)
	bool					m_bEnable;
	int						m_nType;
	float					m_fRange;
	float					padding;
};

struct LIGHTS
{
	LIGHT					m_pLights[MAX_LIGHTS];
	XMFLOAT4				m_xmf4GlobalAmbient;
};

struct MATERIAL
{
	XMFLOAT4				m_xmf4Ambient;
	XMFLOAT4				m_xmf4Diffuse;
	XMFLOAT4				m_xmf4Specular; //(r,g,b,a=power)
	XMFLOAT4				m_xmf4Emissive;
};

struct MATERIALS
{
	MATERIAL				m_pReflections[MAX_MATERIALS];
};

class DefaultRoom
{
public:
	DefaultRoom();
	~DefaultRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	virtual ID3D12Resource* GetMaterialResource() { return m_pd3dcbMaterials; }

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CPlayer* pPlayer);
	virtual void ReleaseObjects();
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual bool ProcessInput(UCHAR *pKeysBuffer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera = NULL);

	virtual void ReleaseUploadBuffers();
	virtual void PlayerComeInRoom(int nEntrance);

	virtual void BuildLightsAndMaterials();
	ID3D12RootSignature *GetGraphicsRootSignature() { return(*m_ppd3dGraphicsRootSignature); }

protected:
	ID3D12RootSignature			**m_ppd3dGraphicsRootSignature = NULL;
	int							m_nRootSignature = 0;

	CShader						**m_ppShaders = NULL;
	int							m_nShaders = 0;

	CPlayer						*m_pPlayer = NULL;		// ÀÚ½Å
	CPlayer						*m_ppOtherPlayer = NULL;// Å¸ ÇÃ·¹ÀÌ¾î

	LIGHTS						*m_pLights = NULL;

	ID3D12Resource				*m_pd3dcbLights = NULL;
	LIGHTS						*m_pcbMappedLights = NULL;

	ID3D12Resource				*m_pd3dcbMaterials = NULL;
	MATERIALS					*m_pMaterials = NULL;
	MATERIAL					*m_pcbMappedMaterials = NULL;

};

//////////////////////////////////////////////////////////////////

class IceRoadRoom : public DefaultRoom		// ºùÆÇ±æ ¸Ê
{
public:
	IceRoadRoom();
	~IceRoadRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};

//////////////////////////////////////////////////////////////////

class SmogCliffRoom : public DefaultRoom	// ¾È°³ Àýº® ¸Ê
{
public:
	SmogCliffRoom();
	~SmogCliffRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	
	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};

///////////////////////////////////////////////////////////////

class SmogMazeRoom : public DefaultRoom		// ¾È°³³¤ ¹Ì·Î
{
public:
	SmogMazeRoom();
	~SmogMazeRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};

//////////////////////////////////////////////////////////////////

class TrapRoom : public DefaultRoom			// ÇÔÁ¤ ¸Ê
{
public:
	TrapRoom();
	~TrapRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};

//////////////////////////////////////////////////

class BossRoom : public DefaultRoom
{
public:
	BossRoom();
	~BossRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};
