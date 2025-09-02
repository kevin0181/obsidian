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

	//������ ���콺�� Ű���� �޽����� ó���Ѵ�. 
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

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

protected:

	//��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�. 
	CObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	float m_fPlayerRespawnTimer = 0.0f;
	bool m_bPlayerDead = false;

	std::vector<CBulletObject*> m_vBulletObjects; // �÷��̾� ��ũ �Ѿ�
	std::vector<CBulletObject*> m_vEnemyBulletObjects; // �� ��ũ �Ѿ�

	std::vector<CEnarmyTankPlayer*> m_vEnemyTankPlayers;
	std::vector<CExplosionCubeObject2*> m_vExplosions2;

	std::vector<CGameObject*> m_vWinObjects;
	std::vector<XMFLOAT3> m_vWinObjectLocalOffsets; // �� win ��ü ��� ��ġ ����

	CGameObject** m_ppShield = nullptr;
	bool shield_active = false;

	CEnarmyTankPlayer* m_pTargetTank = nullptr; //Ÿ�ٵ� ��ũ

	//��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 
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

	bool CheckPlayerObstacleCollision(); // ��ֹ� �浹

	void ActiveShield() { shield_active = true; }

	bool winStatus = false; // �¸� ����

public:
	//���� ��� ���� ��ü�鿡 ���� ���콺 ��ŷ�� �����Ѵ�.
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);
};

bool CheckCollision(const XMFLOAT3& pos1, float radius1, const XMFLOAT3& pos2, float radius2);
