#include "stdafx.h"
#include "Level1.h"
#include "GraphicsPipeline.h"

Level1::Level1(CPlayer* cPlayer)
{
	level1Player = cPlayer;
	BuildObjects();
}

Level1::~Level1()
{
	ReleaseObjects();
}

void Level1::BuildObjects()
{

	m_nRailIndex = 0;

	const int railLength = 114; // 레일 큐브 개수
	CCubeMesh* pCubeMesh = new CCubeMesh(1.0f, 1.0f, 1.0f);

	m_nObjects = railLength;
	m_ppObjects = new CGameObject * [m_nObjects];

	for (int i = 0; i < 10; ++i)
	{
		float x = float(i);
		XMFLOAT3 pos = { x, 0.0f, 0.0f };

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 10; i < 20; ++i)
	{
		float x = float(i) - 10;
		float getLastX = m_vecRailPositions[9].x;
		XMFLOAT3 pos = { getLastX, 0.0f, -x};

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 20; i < 30; ++i)
	{
		float x = float(i) - 20;
		XMFLOAT3 getLastPos = m_vecRailPositions[19];
		XMFLOAT3 pos = { (x + getLastPos.x), 0.0f, getLastPos.z };

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 30; i < 35; ++i)
	{
		float x = float(i) - 30;
		XMFLOAT3 getLastPos = m_vecRailPositions[29];
		XMFLOAT3 pos = { (getLastPos.x), 0.0f, -x + getLastPos.z };

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 35; i < 50; ++i)
	{
		float angleDeg = 40.0f;
		float angleRad = XMConvertToRadians(angleDeg);
		float unitLength = 1.0f;

		float dx = -cosf(angleRad);  
		float dy = sinf(angleRad);  
		float dz = 0.0f;            

		XMFLOAT3 base = m_vecRailPositions[34];
		base.x -= 0.90f;
		base.y += 0.30f;

		int step = i - 35;
		XMFLOAT3 pos = {
			base.x + dx * unitLength * step,
			base.y + dy * unitLength * step,
			base.z + dz * unitLength * step
		};

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Rotate(XMFLOAT3(0.0f, 0.0f, 1.0f), -angleDeg);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 50; i < 60; ++i)
	{
		float x = float(i) - 50;
		XMFLOAT3 getLastPos = m_vecRailPositions[49];
		XMFLOAT3 pos = { (-x + getLastPos.x), getLastPos.y, getLastPos.z };
		pos.x -= 0.90f;
		pos.y += 0.30f;

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 60; i < 70; ++i)
	{
		float angleDeg = 40.0f;
		float angleRad = XMConvertToRadians(angleDeg);
		float unitLength = 1.0f;

		float dx = -cosf(angleRad);
		float dy = sinf(angleRad);
		float dz = 0.0f;            

		XMFLOAT3 base = m_vecRailPositions[59];
		base.x -= 0.10f;
		base.y -= 0.30f;

		int step = i - 59;
		XMFLOAT3 pos = {
			base.x + dx * unitLength * step,
			base.y + dy * unitLength * step,
			base.z + dz * unitLength * step
		};

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Rotate(XMFLOAT3(0.0f, 0.0f, 1.0f), -angleDeg);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 70; i <75; ++i)
	{
		float x = float(i) - 70;
		XMFLOAT3 getLastPos = m_vecRailPositions[69];
		XMFLOAT3 pos = { (-x + getLastPos.x), getLastPos.y, getLastPos.z };
		pos.x -= 0.90f;
		pos.y += 0.30f;

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 75; i < 80; ++i)
	{
		float x = float(i) - 75;
		XMFLOAT3 getLastPos = m_vecRailPositions[74];
		XMFLOAT3 pos = { (getLastPos.x), getLastPos.y, (x + getLastPos.z) };

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 80; i < 100; ++i) // 확 떨어지는 부분
	{
		float angleDeg = 52.5f;
		float angleRad = XMConvertToRadians(angleDeg);
		float unitLength = 1.0f;

		float dx = cosf(angleRad);
		float dy = -sinf(angleRad);
		float dz = 0.0f;             

		XMFLOAT3 base = m_vecRailPositions[79];
		base.x += 0.20f;
		base.y += 0.40f;

		int step = i - 79;
		XMFLOAT3 pos = {
			base.x + dx * unitLength * step,
			base.y + dy * unitLength * step,
			base.z + dz * unitLength * step
		};

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Rotate(XMFLOAT3(0.0f, 0.0f, 1.0f), -angleDeg);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 100; i < 104; ++i)
	{
		float x = float(i) - 100;
		XMFLOAT3 getLastPos = m_vecRailPositions[99];
		XMFLOAT3 pos = { (x + getLastPos.x), getLastPos.y, (getLastPos.z) };
		pos.x += 0.80f;
		pos.y -= 0.45f;
		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}

	for (int i = 104; i < 114; ++i)
	{
		float x = float(i) - 104;
		XMFLOAT3 getLastPos = m_vecRailPositions[103];
		XMFLOAT3 pos = { (getLastPos.x), getLastPos.y, ( x + getLastPos.z) };

		m_ppObjects[i] = new CExplosiveObject();
		m_ppObjects[i]->SetMesh(pCubeMesh);
		m_ppObjects[i]->SetColor(RGB(0, 0, 0));
		m_ppObjects[i]->SetPosition(pos);
		m_ppObjects[i]->Scale(1.0f, 0.1f, 1.0f);

		m_vecRailPositions.push_back(pos);
	}
}

void Level1::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (!m_pCamera) return;

	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	if (nMessageID == WM_LBUTTONDOWN)
	{
		
	}
}

void Level1::ReleaseObjects()
{
	for (int i = 0; i < m_nObjects; i++)
		if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;
}

void Level1::Animate(float fElapsedTime)
{
	m_fTimer += fElapsedTime;

	if (!level1Player || m_vecRailPositions.empty()) return;

	XMFLOAT3 curPos = level1Player->GetPosition();
	XMFLOAT3 targetPos = m_vecRailPositions[m_nRailIndex];

	// 방향 벡터 계산
	XMVECTOR vCur = XMLoadFloat3(&curPos);
	XMVECTOR vTarget = XMLoadFloat3(&targetPos);
	XMVECTOR vDir = XMVector3Normalize(vTarget - vCur);

	// 기본 속도에서 구간별 조절
	float currentSpeed = m_fRailSpeed;

	if (m_nRailIndex >= 35 && m_nRailIndex < 50)
		currentSpeed *= 0.6f;
	else if (m_nRailIndex >= 60 && m_nRailIndex < 70)
		currentSpeed *= 0.6f;
	else if (m_nRailIndex >= 80 && m_nRailIndex < 100)
		currentSpeed *= 2.3f;

	// 이동 거리 계산
	float moveDist = currentSpeed * fElapsedTime;
	XMVECTOR vNew = vCur + vDir * moveDist;

	// 도착 여부 판단
	if (XMVectorGetX(XMVector3Length(vTarget - vNew)) < 0.1f)
	{
		m_nRailIndex++;
		if (m_nRailIndex >= static_cast<int>(m_vecRailPositions.size()))
			m_nRailIndex = 0; // 반복 (목표 도달 x)
	}

	// 이동 적용
	XMFLOAT3 newPos;
	XMStoreFloat3(&newPos, vNew);

	level1Player->SetPosition(newPos.x, newPos.y, newPos.z);
}

void Level1::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{

	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);
	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	for (int i = 0; i < m_nObjects; i++)
		if (m_ppObjects[i]) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	if (level1Player) level1Player->Render(hDCFrameBuffer, pCamera);

}
