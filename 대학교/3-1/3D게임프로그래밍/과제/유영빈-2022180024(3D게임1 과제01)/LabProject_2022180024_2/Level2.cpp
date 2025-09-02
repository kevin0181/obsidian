#include "stdafx.h"
#include "Level2.h"
#include "GraphicsPipeline.h"

Level2::Level2(CPlayer* cPlayer)
{
	level2Player = cPlayer;
	BuildObjects();
}

Level2::~Level2()
{
	ReleaseObjects();
}

void Level2::BuildObjects()
{

	m_bGameWin = false;

	float fHalfWidth = 100.0f, fHalfHeight = 5.0f, fHalfDepth = 100.0f;
	CLevel2WallMesh* pWallCubeMesh = new CLevel2WallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 30);
	m_pWallsObject = new CWallsObject();
	m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pWallsObject->SetMesh(pWallCubeMesh);
	m_pWallsObject->SetColor(RGB(0, 0, 0));
	m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
	m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
	m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
	m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);
	m_pWallsObject->m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.05f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	CTankMesh* pCubeMesh = new CTankMesh(1.0f, 1.0f, 1.0f);

	m_nObjects = 10;
	m_ppObjects = new CGameObject * [m_nObjects];

	m_ppObjects[0] = new CExplosiveObject();
	m_ppObjects[0]->SetMesh(pCubeMesh);
	m_ppObjects[0]->SetColor(RGB(255, 0, 0));
	m_ppObjects[0]->SetPosition(-13.5f, 0.0f, -14.0f);
	m_ppObjects[0]->Rotate(XMFLOAT3(1.0f, 0.0f, 0.0f), 90.0f);
	m_ppObjects[0]->Rotate(XMFLOAT3(0.0f, 0.0f, 1.0f), 90.0f);
	m_ppObjects[0]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, 0.0f));
	m_ppObjects[0]->SetMovingSpeed(10.5f);

	m_ppObjects[1] = new CExplosiveObject();
	m_ppObjects[1]->SetMesh(pCubeMesh);
	m_ppObjects[1]->SetColor(RGB(0, 0, 255));
	m_ppObjects[1]->SetPosition(+13.5f, 0.0f, -14.0f);
	m_ppObjects[1]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 0.0f));
	m_ppObjects[1]->SetMovingSpeed(8.8f);

	m_ppObjects[2] = new CExplosiveObject();
	m_ppObjects[2]->SetMesh(pCubeMesh);
	m_ppObjects[2]->SetColor(RGB(0, 255, 0));
	m_ppObjects[2]->SetPosition(0.0f, 0.0f, 20.0f);
	m_ppObjects[2]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, -1.0f));
	m_ppObjects[2]->SetMovingSpeed(5.2f);

	m_ppObjects[3] = new CExplosiveObject();
	m_ppObjects[3]->SetMesh(pCubeMesh);
	m_ppObjects[3]->SetColor(RGB(0, 255, 0));
	m_ppObjects[3]->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppObjects[3]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, 1.0f));
	m_ppObjects[3]->SetMovingSpeed(20.4f);

	m_ppObjects[4] = new CExplosiveObject();
	m_ppObjects[4]->SetMesh(pCubeMesh);
	m_ppObjects[4]->SetColor(RGB(128, 0, 255));
	m_ppObjects[4]->SetPosition(10.0f, 0.0f, 0.0f);
	m_ppObjects[4]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 1.0f));
	m_ppObjects[4]->SetMovingSpeed(6.4f);

	m_ppObjects[5] = new CExplosiveObject();
	m_ppObjects[5]->SetMesh(pCubeMesh);
	m_ppObjects[5]->SetColor(RGB(255, 0, 255));
	m_ppObjects[5]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[5]->SetMovingDirection(XMFLOAT3(1.0f, 0.0f, -1.0f));
	m_ppObjects[5]->SetMovingSpeed(8.9f);

	m_ppObjects[6] = new CExplosiveObject();
	m_ppObjects[6]->SetMesh(pCubeMesh);
	m_ppObjects[6]->SetColor(RGB(255, 0, 255));
	m_ppObjects[6]->SetPosition(-10.0f, 0.0f, -10.0f);
	m_ppObjects[6]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, -1.0f));
	m_ppObjects[6]->SetMovingSpeed(9.7f);

	m_ppObjects[7] = new CExplosiveObject();
	m_ppObjects[7]->SetMesh(pCubeMesh);
	m_ppObjects[7]->SetColor(RGB(255, 0, 128));
	m_ppObjects[7]->SetPosition(-10.0f, 0.0f, -20.0f);
	m_ppObjects[7]->SetMovingDirection(XMFLOAT3(-1.0f, 0.0f, 1.0f));
	m_ppObjects[7]->SetMovingSpeed(15.6f);

	m_ppObjects[8] = new CExplosiveObject();
	m_ppObjects[8]->SetMesh(pCubeMesh);
	m_ppObjects[8]->SetColor(RGB(128, 0, 255));
	m_ppObjects[8]->SetPosition(-15.0f, 0.0f, -30.0f);
	m_ppObjects[8]->SetMovingDirection(XMFLOAT3(0.0f, 0.0f, -1.0f));
	m_ppObjects[8]->SetMovingSpeed(15.0f);

	m_ppObjects[9] = new CExplosiveObject();
	m_ppObjects[9]->SetMesh(pCubeMesh);
	m_ppObjects[9]->SetColor(RGB(255, 64, 64));
	m_ppObjects[9]->SetPosition(+15.0f, 0.0f, 0.0f);
	m_ppObjects[9]->SetMovingDirection(XMFLOAT3(-0.0f, 0.0f, 1.0f));
	m_ppObjects[9]->SetMovingSpeed(15.0f);


	// 쉴드 오브젝트 생성
	m_pShield = new CShieldObject();
	m_pShield->SetMesh(new CCubeMesh(2.0f, 2.0f, 2.0f));
	m_pShield->SetColor(RGB(255, 0, 0));
	m_pShield->SetPosition(level2Player->GetPosition());
	m_bShieldActive = false;

	// 장애물 오브젝트 생성
	m_ppObstacles = new CGameObject * [m_nObstacles];
	CCubeMesh* pObstacleMesh = new CCubeMesh(1.0f, 1.0f, 1.0f);

	XMFLOAT3 obstaclePositions[5] = {
	{ 20.0f, 0.0f, 15.0f },
	{ -25.0f, 0.0f, 18.0f },
	{ 30.0f, 0.0f, -20.0f },
	{ -35.0f, 0.0f, -10.0f },
	{ 10.0f, 0.0f, -35.0f }
	};


	for (int i = 0; i < m_nObstacles; ++i)
	{
		m_ppObstacles[i] = new CGameObject();
		m_ppObstacles[i]->SetMesh(pObstacleMesh);
		m_ppObstacles[i]->SetColor(RGB(128, 128, 128));
		m_ppObstacles[i]->SetPosition(obstaclePositions[i]);
		m_ppObstacles[i]->UpdateBoundingBox();
	}


	m_bTankDestroyed = new bool[m_nObjects] {};

}

void Level2::CheckPlayerByObstacleCollision()
{
	for (int i = 0; i < m_nObstacles; ++i)
	{
		if (m_ppObstacles[i]->m_xmOOBB.Intersects(level2Player->m_xmOOBB))
		{
			level2Player->SetPosition(m_xmf3PrevPlayerPos.x, m_xmf3PrevPlayerPos.y, m_xmf3PrevPlayerPos.z); // 직전 위치로 되돌리기
			level2Player->UpdateBoundingBox();
			break;
		}
	}
}


void Level2::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (!m_pCamera) return;

	// lParam에서 x, y 추출
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);

	if (nMessageID == WM_LBUTTONDOWN) // 왼쪽 버튼 눌렀을 때
	{

	}
}

void Level2::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}


void Level2::CheckObjectByWallCollisions()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_ppObjects[i]->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_ppObjects[i]->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&m_ppObjects[i]->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&m_ppObjects[i]->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
}

CGameObject* Level2::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{
	XMFLOAT3 xmf3PickPosition;
	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX;
	CGameObject* pNearestObject = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		float fHitDistance = FLT_MAX;
		nIntersected = m_ppObjects[i]->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance))
		{
			fNearestHitDistance = fHitDistance;
			pNearestObject = m_ppObjects[i];
		}
	}
	return(pNearestObject);
}

void Level2::CheckObjectByBulletCollisions()
{	
	CBulletObject** ppBullets = ((CAirplanePlayer*)level2Player)->m_ppBullets;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = 0; j < BULLETS; j++)
		{
			if (ppBullets[j]->m_bActive && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
			{
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
				ppBullets[j]->Reset();
			}
		}
	}

	// 추가: 폭발 애니메이션이 끝났으면 해당 탱크를 비활성화 처리
	for (int i = 0; i < m_nObjects; i++)
	{
		CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
		if (!m_bTankDestroyed[i] && pExplosiveObject->IsExplosionFinished())
		{
			m_bTankDestroyed[i] = true;
		}
	}
}

void Level2::CheckPlayerByWallCollision()
{
	BoundingOrientedBox xmOOBBPlayerMoveCheck;
	m_pWallsObject->m_xmOOBBPlayerMoveCheck.Transform(xmOOBBPlayerMoveCheck, XMLoadFloat4x4(&m_pWallsObject->m_xmf4x4World));
	XMStoreFloat4(&xmOOBBPlayerMoveCheck.Orientation, XMQuaternionNormalize(XMLoadFloat4(&xmOOBBPlayerMoveCheck.Orientation)));

	//if (!xmOOBBPlayerMoveCheck.Intersects(level2Player->m_xmOOBB)) m_pWallsObject->SetPosition(level2Player->m_xmf3Position);  -> 중심 복원
	if (level2Player->GetPosition().z > 100.0f || level2Player->GetPosition().z < -100.0f) {
		level2Player->SetPosition(m_pWallsObject->GetPosition().x, m_pWallsObject->GetPosition().y, m_pWallsObject->GetPosition().z);
	}

	if (level2Player->GetPosition().x > 100.0f || level2Player->GetPosition().x < -100.0f) {
		level2Player->SetPosition(m_pWallsObject->GetPosition().x, m_pWallsObject->GetPosition().y, m_pWallsObject->GetPosition().z);
	}

}

void Level2::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

	if (nMessageID == WM_KEYDOWN)
	{
		if (wParam == 82)  // r 키 눌렀을 때
		{
			m_bShieldActive = !m_bShieldActive;
			if (m_bShieldActive)
			{
				m_pShield->SetPosition(level2Player->GetPosition());
				m_fShieldElapsedTime = 0.0f; // 쉴드 켤 때 시간 초기화
			}
		}
		else if (wParam == 81) // q 키 누르면 강제로 Win
		{
			m_bGameWin = true;
		}
	}
}

void Level2::ReleaseObjects()
{
	for (int i = 0; i < m_nObjects; i++)
		if (m_ppObjects[i]) delete m_ppObjects[i];

	if (m_ppObjects) delete[] m_ppObjects;

	if (m_pWallsObject) delete m_pWallsObject;

	if (m_ppObstacles)
	{
		for (int i = 0; i < m_nObstacles; ++i)
			if (m_ppObstacles[i]) delete m_ppObstacles[i];
		delete[] m_ppObstacles;
	}

	if (m_bTankDestroyed) delete[] m_bTankDestroyed;
}

void Level2::Animate(float fElapsedTime)
{
	m_fTimer += fElapsedTime;
	m_pWallsObject->Animate(fElapsedTime);

	for (int i = 0; i < m_nObjects; i++) {
		XMFLOAT3 dir = Vector3::Normalize(m_ppObjects[i]->m_xmf3MovingDirection);
		XMFLOAT3 forward = { 0.0f, 0.0f, 1.0f }; // 탱크 모델의 기본 전방 (Z+)

		float dot = Vector3::DotProduct(forward, dir);
		dot = std::clamp(dot, -1.0f, 1.0f);
		float angleY = acosf(dot);

		//	// Y축 회전 방향 결정
		float crossY = forward.x * dir.z - forward.z * dir.x;
		if (crossY < 0.0f) angleY = -angleY;

		// 기본 X축 90도 회전 + Y축 방향 회전
		XMMATRIX rotX = XMMatrixRotationX(XMConvertToRadians(90.0f));
		XMMATRIX rotY = XMMatrixRotationY(angleY);
		XMMATRIX worldRot = XMMatrixMultiply(rotX, rotY);

		XMFLOAT4X4 xform;
		XMStoreFloat4x4(&xform, worldRot);
		m_ppObjects[i]->SetRotationTransform(&xform);
	}

	for (int i = 0; i < m_nObjects; i++)
		if (!m_bTankDestroyed[i]) m_ppObjects[i]->Animate(fElapsedTime);

	CheckPlayerByWallCollision();
	CheckObjectByWallCollisions();
	CheckObjectByObjectCollisions();
	CheckObjectByBulletCollisions();

	for (int i = 0; i < m_nObstacles; ++i)
		if (m_ppObstacles[i]) m_ppObstacles[i]->Animate(fElapsedTime); 

	m_xmf3PrevPlayerPos = level2Player->GetPosition();
	level2Player->UpdateBoundingBox();

	CheckPlayerByObstacleCollision(); // 장애물과 충돌 체크


	if (m_bShieldActive)
	{
		m_fShieldElapsedTime += fElapsedTime;
		m_pShield->SetPosition(level2Player->GetPosition()); // 따라다님

		if (m_fShieldElapsedTime > 1.0f) // 1초 경과하면 자동 종료
		{
			m_bShieldActive = false;
			m_fShieldElapsedTime = 0.0f;
		}
	}

	// 탱크가 모두 파괴되었는지 체크
	if (!m_bGameWin)
	{
		bool allDestroyed = true;
		for (int i = 0; i < m_nObjects; ++i)
		{
			if (!m_bTankDestroyed[i])
			{
				allDestroyed = false;
				break;
			}
		}
		if (allDestroyed)
			m_bGameWin = true;
	}
}

void Level2::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{

	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);
	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	if (m_bGameWin)
	{
		SetTextColor(hDCFrameBuffer, RGB(255, 0, 0));
		SetBkMode(hDCFrameBuffer, TRANSPARENT);
		HFONT hFont = CreateFont(48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
			VARIABLE_PITCH, TEXT("Arial"));
		HFONT hOldFont = (HFONT)SelectObject(hDCFrameBuffer, hFont);

		RECT rect = { 0, 0, 1280, 720 };
		DrawText(hDCFrameBuffer, TEXT("YOU WIN!"), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(hDCFrameBuffer, hOldFont);
		DeleteObject(hFont);
	}

	m_pWallsObject->Render(hDCFrameBuffer, pCamera);

	for (int i = 0; i < m_nObjects; i++)
		if (m_ppObjects[i] && !m_bTankDestroyed[i])
			m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	if (level2Player) level2Player->Render(hDCFrameBuffer, pCamera);

	if (m_bShieldActive && m_pShield)
		m_pShield->Render(hDCFrameBuffer, pCamera);

	for (int i = 0; i < m_nObstacles; ++i)
		if (m_ppObstacles[i]) m_ppObstacles[i]->Render(hDCFrameBuffer, pCamera);
}
