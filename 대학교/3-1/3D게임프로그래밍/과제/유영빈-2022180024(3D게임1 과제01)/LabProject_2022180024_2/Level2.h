#pragma once

#include "GameObject.h"
#include "Player.h"
#include <vector>
#include <algorithm>
#include "OBJMeshLoader.h"

class Level2
{
public:
	Level2(CPlayer* cPlayer);
	virtual ~Level2();

private:
	int							m_nObjects = 0;
	CGameObject** m_ppObjects = NULL;

	CCamera* m_pCamera = NULL;

	CPlayer* level2Player = NULL;

	CWallsObject* m_pWallsObject = NULL;

	float m_fTimer = 0.0f; // 얼마나 지났는지 시간 측정

	CShieldObject* m_pShield = nullptr;
	bool m_bShieldActive = false;
	float m_fShieldElapsedTime = 0.0f;

	CGameObject** m_ppObstacles = nullptr; // 장애물 배열
	int m_nObstacles = 5;

	XMFLOAT3 m_xmf3PrevPlayerPos{};

	bool* m_bTankDestroyed = nullptr; // 탱크 파괴 여부 저장
	bool m_bGameWin = false;

public:
	virtual void BuildObjects();
	virtual void ReleaseObjects();
	virtual void Animate(float fElapsedTime);
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void CheckPlayerByWallCollision();
	void CheckObjectByWallCollisions();
	void CheckObjectByObjectCollisions();
	void CheckObjectByBulletCollisions();
	void CheckPlayerByObstacleCollision();
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	CCamera* GetCamera() const {
		return m_pCamera;
	}
};

