#pragma once
#include "GameObject.h"
#include "OBJMeshLoader.h"
#include <vector>

class MenuScene
{
public:
	MenuScene();
	virtual ~MenuScene();

private:
	int							m_nObjects = 0;
	CGameObject** m_ppObjects = NULL;

	CCamera* m_pCamera = NULL;

	float m_fTimer = 0.0f; // �󸶳� �������� �ð� ����

	std::vector<CGameObject*> m_MenuObjects; // �޴� ������Ʈ �迭
	int m_nCurrentMenuIndex = 0;         // ���� ���õ� �޴� �ε���
	std::vector<XMFLOAT3> m_vCameraTargets; // �� �޴��� ī�޶� Ÿ�� ��ġ��
public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();
	virtual void Animate(float fElapsedTime);
	int OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void Render(HDC hDCFrameBuffer);
};

