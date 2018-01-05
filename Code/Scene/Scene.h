//-----------------------------------------------------------------------------
// File: Scene.h
//-----------------------------------------------------------------------------

#pragma once

#include "Shader.h"
#include "Player.h"
#include "Room.h"

class CScene
{
public:
    CScene();
    ~CScene();

	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	void SetGraphicsRootSignature(ID3D12GraphicsCommandList *pd3dCommandList, int index = 0) { pd3dCommandList->SetGraphicsRootSignature(m_ppd3dGraphicsRootSignature[index]); }

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseObjects();
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual bool ProcessInput(UCHAR *pKeysBuffer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera=NULL);

	virtual void ReleaseUploadBuffers();

	ID3D12RootSignature *GetGraphicsRootSignature() { return(*m_ppd3dGraphicsRootSignature); }
	ID3D12Resource* GetMaterialResource() { return m_pd3dcbMaterials; }

protected:
	ID3D12RootSignature			**m_ppd3dGraphicsRootSignature = NULL;
	int							m_nRootSignature = 0;

	CShader						**m_ppShaders = NULL;
	int							m_nShaders = 0;

	ID3D12Resource				*m_pd3dcbMaterials = NULL;
};

/////////////////////////////////////////////////////////////////////////////////////

class MainScene : public CScene
{
public:
	MainScene();
	~MainScene();

	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature *GetGraphicsRootSignature() { return(*m_ppd3dGraphicsRootSignature); }
	ID3D12Resource* GetMaterialResource() { return m_pd3dcbMaterials; }
	
	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseObjects();
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual bool ProcessInput(UCHAR *pKeysBuffer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera = NULL);

	virtual void ReleaseUploadBuffers();
};

class GameScene : public CScene
{
public:
	GameScene();
	~GameScene();

	void BuildLightsAndMaterials();

	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	virtual ID3D12Resource* GetMaterialResource() { return m_pd3dcbMaterials; }
	
	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseObjects();
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual bool ProcessInput(UCHAR *pKeysBuffer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera = NULL);

	virtual void ReleaseUploadBuffers();

	CPlayer						*m_pPlayer = NULL;		// 자신
	CPlayer						*m_ppOtherPlayer = NULL;// 타 플레이어

protected:
	int					m_nRooms;
	DefaultRoom**		m_ppRooms;
};

class ShopScene : public CScene
{
	ShopScene();
	~ShopScene();

	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual ID3D12RootSignature *CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);

	virtual void BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseObjects();
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	virtual bool ProcessInput(UCHAR *pKeysBuffer);
	virtual void AnimateObjects(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera = NULL);

	virtual void ReleaseUploadBuffers();

protected:
	MATERIALS					*m_pMaterials = NULL;

	ID3D12Resource				*m_pd3dcbMaterials = NULL;
	MATERIAL					*m_pcbMappedMaterials = NULL;
};