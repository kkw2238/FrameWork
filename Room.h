#pragma once

#include "Shader.h"
#include "Scene.h"

class DefaultRoom
{
public:
	DefaultRoom();
	~DefaultRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	virtual ID3D12Resource* GetMaterialResource() { return m_pd3dcbMaterials; }

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CMyPlayer* pPlayer);
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

	CPlayer						*m_pPlayer = NULL;		// �ڽ�
	CPlayer						*m_ppOtherPlayer = NULL;// Ÿ �÷��̾�

	LIGHTS						*m_pLights = NULL;

	ID3D12Resource				*m_pd3dcbLights = NULL;
	LIGHTS						*m_pcbMappedLights = NULL;

	ID3D12Resource				*m_pd3dcbMaterials = NULL;
	MATERIALS					*m_pMaterials = NULL;
	MATERIAL					*m_pcbMappedMaterials = NULL;

};

//////////////////////////////////////////////////////////////////

class IceRoadRoom : public DefaultRoom		// ���Ǳ� ��
{
public:
	IceRoadRoom();
	~IceRoadRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CMyPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};

//////////////////////////////////////////////////////////////////

class SmogCliffRoom : public DefaultRoom	// �Ȱ� ���� ��
{
public:
	SmogCliffRoom();
	~SmogCliffRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	
	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CMyPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};

///////////////////////////////////////////////////////////////

class SmogMazeRoom : public DefaultRoom		// �Ȱ��� �̷�
{
public:
	SmogMazeRoom();
	~SmogMazeRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CMyPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};

//////////////////////////////////////////////////////////////////

class TrapRoom : public DefaultRoom			// ���� ��
{
public:
	TrapRoom();
	~TrapRoom();

public:
	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CMyPlayer* pPlayer);
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

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, CMyPlayer* pPlayer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void PlayerComeInRoom(int nEntrance);
	virtual void BuildLightsAndMaterials();
};
