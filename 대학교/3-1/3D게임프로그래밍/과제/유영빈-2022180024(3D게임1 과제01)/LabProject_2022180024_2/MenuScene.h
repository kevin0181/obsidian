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

	float m_fTimer = 0.0f; // 얼마나 지났는지 시간 측정

	std::vector<CGameObject*> m_MenuObjects; // 메뉴 오브젝트 배열
	int m_nCurrentMenuIndex = 0;         // 현재 선택된 메뉴 인덱스
	std::vector<XMFLOAT3> m_vCameraTargets; // 각 메뉴의 카메라 타겟 위치들
public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();
	virtual void Animate(float fElapsedTime);
	int OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void Render(HDC hDCFrameBuffer);
};

