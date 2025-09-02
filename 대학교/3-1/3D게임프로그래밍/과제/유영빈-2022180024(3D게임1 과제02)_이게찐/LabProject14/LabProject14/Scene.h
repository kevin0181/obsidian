#pragma once
#include "Timer.h"
#include "GameObject.h"
#include "Shader.h"
#include "Player.h"

class CCamera;

class CScene
{
public:
	CScene();
	~CScene() {}

	//씬에서 마우스와 키보드 메시지를 처리한다. 
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

	//그래픽 루트 시그너쳐를 생성한다. 
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

protected:

	//배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다. 
	CObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	float m_fPlayerRespawnTimer = 0.0f;
	bool m_bPlayerDead = false;

	std::vector<CBulletObject*> m_vBulletObjects; // 플레이어 탱크 총알
	std::vector<CBulletObject*> m_vEnemyBulletObjects; // 적 탱크 총알

	std::vector<CEnarmyTankPlayer*> m_vEnemyTankPlayers;
	std::vector<CExplosionCubeObject2*> m_vExplosions2;

	std::vector<CGameObject*> m_vWinObjects;
	std::vector<XMFLOAT3> m_vWinObjectLocalOffsets; // ← win 객체 상대 위치 보관

	CGameObject** m_ppShield = nullptr;
	bool shield_active = false;

	CEnarmyTankPlayer* m_pTargetTank = nullptr; //타겟된 탱크

	//루트 시그너쳐를 나타내는 인터페이스 포인터이다. 
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
	
protected:
	CHeightMapTerrain* m_pTerrain = NULL;

public:
	CHeightMapTerrain* GetTerrain() { return(m_pTerrain); }

	CPlayer* m_pPlayer = NULL;
	void fire(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);
	void CheckBulletEnemyCollisions();
	void CreateExplosionAt(XMFLOAT3 position);
	void FireEnemyBullet(CEnarmyTankPlayer* pTank);
	void CheckEnemyBulletPlayerCollisions();

	bool CheckPlayerObstacleCollision(); // 장애물 충돌

	void ActiveShield() { shield_active = true; }

	bool winStatus = false; // 승리 상태

public:
	//씬의 모든 게임 객체들에 대한 마우스 픽킹을 수행한다.
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

bool CheckCollision(const XMFLOAT3& pos1, float radius1, const XMFLOAT3& pos2, float radius2);
