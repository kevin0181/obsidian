#include "stdafx.h"
#include "MenuScene.h"
#include "GraphicsPipeline.h"

MenuScene::MenuScene()
{
	BuildObjects();
}

MenuScene::~MenuScene()
{
	ReleaseObjects();
}

void MenuScene::BuildObjects()
{

	struct MenuItem {
		const char* filename;
		XMFLOAT3 position;
	};

	std::vector<MenuItem> items = {
		{ "Assets/Tutorial.obj",    XMFLOAT3(-180.0f, 0.0f, 0.0f) },
		{ "Assets/START.obj",    XMFLOAT3(-90.0f, 0.0f, 0.0f) },
		{ "Assets/Level-1.obj",  XMFLOAT3(0.0f,   0.0f, 0.0f) },
		{ "Assets/Level-2.obj",  XMFLOAT3(90.0f,   0.0f, 0.0f) },
		{ "Assets/End.obj",     XMFLOAT3(180.0f, 0.0f, 0.0f) }
	};

	for (const auto& item : items)
	{
		CMesh* mesh = LoadOBJToMesh(item.filename);
		if (mesh)
		{
			CGameObject* menuObj = new CGameObject();
			menuObj->SetMesh(mesh);
			menuObj->SetColor(RGB(255, 0, 0));
			menuObj->SetPosition(item.position.x, item.position.y, item.position.z);
			m_MenuObjects.push_back(menuObj);

			m_vCameraTargets.push_back(item.position);
		}
	}

	//카메라
	m_pCamera = new CCamera();
	m_pCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	m_pCamera->GeneratePerspectiveProjectionMatrix(0.01f, 1000.0f, 90.0f);
	m_pCamera->SetFOVAngle(90.0f);

	XMFLOAT3 target = m_vCameraTargets[m_nCurrentMenuIndex]; // 선택된 메뉴 위치
	XMFLOAT3 eye = XMFLOAT3(target.x, target.y + 10.0f, target.z - 100.0f); // 항상 뒤에서 봄
	XMFLOAT3 lookAt = target;
	m_pCamera->SetLookAt(eye, lookAt, XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pCamera->GenerateViewMatrix();
}

int MenuScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (!m_pCamera) return 0;

	if (nMessageID == WM_LBUTTONDOWN && m_fTimer > 1.0f)
	{
		switch (m_nCurrentMenuIndex)
		{
		case 1: // START.obj
		case 2: // Level-1.obj
			return 1; // 숫자 1
		case 3: // Level-2.obj
			return 2; // 숫자 2
		case 4: // End.obj
			exit(0); // 프로그램 종료
			break;
		default:
			return 0;
			break;
		}
	}
	return -1; // 아무 것도 선택되지 않았을 때
}

bool MenuScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (!m_pCamera) return false;

	if (nMessageID == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_LEFT:
			if (m_nCurrentMenuIndex > 0)
				m_nCurrentMenuIndex--;
			break;
		case VK_RIGHT:
			if (m_nCurrentMenuIndex < (int)m_vCameraTargets.size() - 1)
				m_nCurrentMenuIndex++;
			break;
		default:
			break;
		}

		// 카메라를 새로운 메뉴로 이동
		XMFLOAT3 target = m_vCameraTargets[m_nCurrentMenuIndex]; // 선택된 메뉴 위치
		XMFLOAT3 eye = XMFLOAT3(target.x, target.y + 10.0f, target.z - 100.0f); // 항상 뒤에서 봄
		XMFLOAT3 lookAt = target;

		m_pCamera->SetLookAt(eye, lookAt, XMFLOAT3(0.0f, 1.0f, 0.0f));
		m_pCamera->GenerateViewMatrix();
	}
	return false;
}

void MenuScene::ReleaseObjects()
{
	for (auto obj : m_MenuObjects)
	{
		if (obj) delete obj;
	}
	m_MenuObjects.clear();
}

void MenuScene::Animate(float fElapsedTime)
{
	m_fTimer += fElapsedTime; // 시간 측정
}

void MenuScene::Render(HDC hDCFrameBuffer)
{

	CGraphicsPipeline::SetViewport(&m_pCamera->m_Viewport);
	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&m_pCamera->m_xmf4x4ViewPerspectiveProject);

	for (auto obj : m_MenuObjects)
	{
		if (obj) obj->Render(hDCFrameBuffer, m_pCamera);
	}
}
