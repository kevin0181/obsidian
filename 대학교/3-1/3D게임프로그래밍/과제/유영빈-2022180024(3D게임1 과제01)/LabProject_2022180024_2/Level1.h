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

	float m_fTimer = 0.0f; // 얼마나 지났는지 시간 측정

	std::vector<XMFLOAT3> m_vecRailPositions; // 레일 큐브 위치 저장

	int m_nRailIndex = 0; // 현재 레일 큐브 인덱스
	float m_fRailSpeed = 5.0f; // 레일 큐브 속도

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

