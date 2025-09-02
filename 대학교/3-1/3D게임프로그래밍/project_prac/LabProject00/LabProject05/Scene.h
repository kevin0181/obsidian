#pragma once

#include "Timer.h"

#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <DirectXMath.h>  // (�ʿ��ϸ� �߰�)
#include <windows.h>  // ZeroMemory ����� ���� �߰�
#include <wrl.h>     // Microsoft�� ComPtr�� ���� ���
#include <memory>
#include <vector>

#pragma comment(lib, "d3d12.lib")  // Direct3D 12 ���̺귯�� ��ũ
#pragma comment(lib, "dxgi.lib")   // DXGI ���̺귯�� ��ũ
#pragma comment(lib, "d3dcompiler.lib")  // ���̴� ������ ���̺귯�� ��ũ

class CScene
{
public:
	CScene();
	~CScene();
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	void CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
	void CreateGraphicsPipelineState(ID3D12Device* pd3dDevice);
	void BuildObjects(ID3D12Device* pd3dDevice);
	void ReleaseObjects();
	bool ProcessInput();
	void AnimateObjects(float fTimeElapsed);
	void PrepareRender(ID3D12GraphicsCommandList* pd3dCommandList);
	void Render(ID3D12GraphicsCommandList* pd3dCommandList);
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
	//��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 
	ID3D12PipelineState* m_pd3dPipelineState = NULL;
	//���������� ���¸� ��Ÿ���� �������̽� �������̴�. 
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc = {};
	ID3DBlob* pd3dVertexShaderBlob = nullptr;
	D3D12_RASTERIZER_DESC d3dRasterizerDesc = {};
	D3D12_BLEND_DESC d3dBlendDesc = {};
	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc = {};

};
