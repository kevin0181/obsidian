#pragma once
#include "Timer.h"
//#include "GameObject.h"
#include "Shader.h"
#include "Player.h"

class CCamera;

class Level1Scene
{
public:
	Level1Scene();
	~Level1Scene() {}

	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);


	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	void ReleaseObjects();

	bool ProcessInput();

	void AnimateObjects(float fTimeElapsed);

	void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

	void ReleaseUploadBuffers();

	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

	CLevel1ScenePlayer* m_pLevel1ScenePlayer = NULL;
	CCamera* m_pCamera = NULL;

	int m_nCurrentPathIndex = 0;

	bool animation_status = true;

protected:

	CLevel1SceneShader* m_pShaders = NULL;
	int m_nShaders = 0;

	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;

protected:

public:

public:
};


