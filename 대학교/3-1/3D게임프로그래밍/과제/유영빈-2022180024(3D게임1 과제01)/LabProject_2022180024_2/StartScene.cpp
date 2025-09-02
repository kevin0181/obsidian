#include "stdafx.h"
#include "StartScene.h"
#include "GraphicsPipeline.h"

StartScene::StartScene()
{
	BuildObjects();
}

StartScene::~StartScene()
{
	ReleaseObjects();
}

void StartScene::BuildObjects()
{

	CExplosiveObject::PrepareExplosion();

	CMesh* objMesh = LoadOBJToMesh("Assets/3dgame.obj");
	if (objMesh)
	{
		obj = new CExplosiveObject();
		obj->SetMesh(objMesh);
		obj->SetColor(RGB(255, 0, 0));
		obj->SetPosition(0.0f, 8.0f, 50.0f);
		obj->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		obj->SetRotationSpeed(90.0f);
	}

	CMesh* objMesh2 = LoadOBJToMesh("Assets/name.obj");
	if (objMesh2)
	{
		obj2 = new CExplosiveObject();
		obj2->SetMesh(objMesh2);
		obj2->SetColor(RGB(0, 0, 255));
		obj2->SetPosition(0.0f, -20.0f, 50.0f);
		obj2->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		obj2->SetRotationSpeed(90.0f);
		obj2->UpdateBoundingBox();
	}

	m_nObjects = 1;
	m_ppObjects = new CGameObject * [m_nObjects];
	m_ppObjects[0] = obj2;

	//카메라
	m_pCamera = new CCamera();
	m_pCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	m_pCamera->GeneratePerspectiveProjectionMatrix(1.01f, 500.0f, 60.0f);
	m_pCamera->SetFOVAngle(60.0f);
	// 고정된 카메라 세팅
	XMFLOAT3 eye = XMFLOAT3(0.0f, 10.0f, -50.0f);   // 카메라 위치
	XMFLOAT3 lookAt = XMFLOAT3(0.0f, 0.0f, 0.0f);   // 바라보는 점
	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);       // 위쪽

	// 1단계. LookAt 세팅
	m_pCamera->SetLookAt(eye, lookAt, up);

	// 2단계. ViewMatrix 생성
	m_pCamera->GenerateViewMatrix();

}

CGameObject* StartScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
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

void StartScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (!m_pCamera) return;

	// lParam에서 x, y 추출
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);	

	if (nMessageID == WM_LBUTTONDOWN) // 왼쪽 버튼 눌렀을 때
	{
		CGameObject* pPicked = PickObjectPointedByCursor(x, y, m_pCamera);
		if (pPicked == obj2) {
			CExplosiveObject* pExplosiveObject = static_cast<CExplosiveObject*>(obj2);
			CExplosiveObject* pExplosiveObject1 = static_cast<CExplosiveObject*>(obj);
			pExplosiveObject1->EXPLOSION_DEBRISES_COUNT = 240;
			pExplosiveObject->EXPLOSION_DEBRISES_COUNT = 240;
			pExplosiveObject->m_bBlowingUp = true;
			pExplosiveObject1->m_bBlowingUp = true;
			m_bExploding = true;
			m_fExplodeTimer = 0.0f;
		}
	}
}

void StartScene::ReleaseObjects()
{
	if (obj) delete obj;
	if (obj2) delete obj2;
}

void StartScene::Animate(float fElapsedTime)
{

	obj->Animate(fElapsedTime); // 자전+이동
	obj2->Animate(fElapsedTime); // 자전+이동

	if (m_bExploding) // 이름 폭발 후 계산
	{
		m_fExplodeTimer += fElapsedTime;
	}
}

void StartScene::Render(HDC hDCFrameBuffer)
{

	CGraphicsPipeline::SetViewport(&m_pCamera->m_Viewport);
	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&m_pCamera->m_xmf4x4ViewPerspectiveProject);

	obj->Render(hDCFrameBuffer, m_pCamera);
	obj2->Render(hDCFrameBuffer, m_pCamera);

}
