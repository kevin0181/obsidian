#pragma once
#include "GameObject.h"
#include "Player.h"
#include <vector>
#include <algorithm>
#include "OBJMeshLoader.h"

class Level1
{
public:
	Level1(CPlayer* cPlayer);
	virtual ~Level1();

private:
	int							m_nObjects = 0;
	CGameObject** m_ppObjects = NULL;

	CCamera* m_pCamera = NULL;

	CPlayer* level1Player = NULL;

	float m_fTimer = 0.0f; // �󸶳� �������� �ð� ����

	std::vector<XMFLOAT3> m_vecRailPositions; // ���� ť�� ��ġ ����

	int m_nRailIndex = 0; // ���� ���� ť�� �ε���
	float m_fRailSpeed = 5.0f; // ���� ť�� �ӵ�

public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();
	virtual void Animate(float fElapsedTime);
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	CCamera* GetCamera() const {
		return m_pCamera;
	}
};

