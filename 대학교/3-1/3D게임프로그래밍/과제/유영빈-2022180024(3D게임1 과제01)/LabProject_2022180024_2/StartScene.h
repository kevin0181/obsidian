#pragma once
#include "GameObject.h"
#include "OBJMeshLoader.h"

class StartScene
{
public:
	StartScene();
	virtual ~StartScene();

private:
	int							m_nObjects = 0;
	CGameObject** m_ppObjects = NULL;

	CCamera* m_pCamera = NULL;

	CGameObject* obj = nullptr;
	CGameObject* obj2 = nullptr;

	bool m_bExploding = false;   // ������ ������ üũ
	float m_fExplodeTimer = 0.0f; // �󸶳� �������� �ð� ����

public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();
	virtual void Animate(float fElapsedTime);
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void Render(HDC hDCFrameBuffer);
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);

	float getm_fExplodeTimer() { return m_fExplodeTimer; }
};

