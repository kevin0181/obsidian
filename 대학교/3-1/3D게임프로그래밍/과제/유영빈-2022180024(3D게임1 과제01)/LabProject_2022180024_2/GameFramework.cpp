//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"

void CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	::srand(timeGetTime());

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	BuildFrameBuffer(); 

	BuildObjects(); 

	_tcscpy_s(m_pszFrameRate, _T("LabProject ("));
}

void CGameFramework::OnDestroy()
{
	ReleaseObjects();

	if (m_hBitmapFrameBuffer) ::DeleteObject(m_hBitmapFrameBuffer);
	if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);
}

void CGameFramework::BuildFrameBuffer()
{
	::GetClientRect(m_hWnd, &m_rcClient);

	HDC hDC = ::GetDC(m_hWnd);

    m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
    ::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
    ::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
	HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::SelectObject(m_hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{    
    HDC hDC = ::GetDC(m_hWnd);
    ::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
    ::ReleaseDC(m_hWnd, hDC);
}

void CGameFramework::BuildObjects()
{
	CCamera* pCamera = new CCamera();
	pCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	pCamera->GeneratePerspectiveProjectionMatrix(1.01f, 500.0f, 60.0f);
	pCamera->SetFOVAngle(60.0f);

	pCamera->GenerateOrthographicProjectionMatrix(1.01f, 50.0f, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

	//CAirplaneMesh* pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);
	CCubeMesh* CCubeMesh_Level1 = new CCubeMesh(1.0f, 1.0f, 1.0f);

	m_pPlayer = new CAirplanePlayer();
	m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
	m_pPlayer->SetMesh(CCubeMesh_Level1);
	m_pPlayer->SetColor(RGB(0, 0, 255));
	m_pPlayer->SetCamera(pCamera);
	m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 2.0f, -7.0f));
	playerCameraStatus = false;

	m_pScene = new CScene(m_pPlayer);
	m_pScene->BuildObjects();

	startScene = new StartScene();
	menuScene = new MenuScene();
	level1 = new Level1(m_pPlayer);

	level2 = new Level2(m_pPlayer);
}

void CGameFramework::ReleaseObjects()
{
	if (m_pScene)
	{
		m_pScene->ReleaseObjects();
		delete m_pScene;
	}

	if (m_pPlayer) {
		delete m_pPlayer;
	}
	if (startScene) {
		delete startScene; // 시작 장면
	}
	if (menuScene) {
		delete menuScene; // 메뉴 장면
	}
	if (level1) {
		delete level1; // 레벨 1 장면
	}
	if (level2) {
		delete level2; // 레벨 2 장면
	}
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pScene) m_pScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
	if (startScene) startScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);

	if (menuScene && m_CurrentScene == SceneType::MenuScene) {
		switch (menuScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam))
		{
		case 1:
			m_CurrentScene = SceneType::Level_1;
			break;
		case 2:
		{
			playerCameraStatus = true;

			level2->ReleaseObjects(); // 혹시 누적 방지
			level2->BuildObjects();

			CTankMesh* pTankMesh = new CTankMesh(1.0f, 1.0f, 1.0f);
			m_pPlayer->SetMesh(pTankMesh);
			m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);

			// 완전한 초기화
			m_pPlayer->m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
			m_pPlayer->m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_pPlayer->m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);
			XMStoreFloat4x4(&m_pPlayer->m_xmf4x4World, XMMatrixIdentity());

			m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 0.0f, -7.0f));

			m_CurrentScene = SceneType::Level_2;
			break;
		}
		case 0:
			m_CurrentScene = SceneType::NN;
			break;
		default:
			break;
		}
	}

	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos);
		if (nMessageID == WM_RBUTTONDOWN) m_pLockedObject = level2->PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		::ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pScene) m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
	if (level2) level2->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
	if (menuScene) menuScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);

	/*char buf[64];
	sprintf_s(buf, "Key Pressed - wParam: %d (char: %c)\n", (int)wParam, (char)wParam);
	::OutputDebugStringA(buf);*/

	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			if (m_CurrentScene == SceneType::Level_1) {
				m_CurrentScene = SceneType::MenuScene;
			}
			else if (m_CurrentScene == SceneType::Level_2) {
				m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
				playerCameraStatus = false;
				m_CurrentScene = SceneType::MenuScene;
			}
			else {
				::PostQuitMessage(0);
			}
			break;
		case VK_RETURN:
			break;
		case VK_CONTROL:
			if (playerCameraStatus) {
				((CAirplanePlayer*)m_pPlayer)->FireBullet(m_pLockedObject);
				m_pLockedObject = NULL;
			}
			break;
		case 78: // n
			if (m_CurrentScene == SceneType::Level_1) {

				playerCameraStatus = true;

				level2->ReleaseObjects(); // 혹시 누적 방지
				level2->BuildObjects();

				CTankMesh* pTankMesh = new CTankMesh(1.0f, 1.0f, 1.0f);
				m_pPlayer->SetMesh(pTankMesh);
				m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);

				// 완전한 초기화
				m_pPlayer->m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
				m_pPlayer->m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
				m_pPlayer->m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);
				XMStoreFloat4x4(&m_pPlayer->m_xmf4x4World, XMMatrixIdentity());

				m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 0.0f, -7.0f));

				m_CurrentScene = SceneType::Level_2;
			}
			break;
		default:
			m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
			break;
		}
		break;
	default:
		break;
	}
}

LRESULT CALLBACK CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_INACTIVE)
			m_GameTimer.Stop();
		else
			m_GameTimer.Start();
		break;
	}
	case WM_SIZE:
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}
	return(0);
}

void CGameFramework::ProcessInput()
{
	static UCHAR pKeyBuffer[256];
	if (GetKeyboardState(pKeyBuffer))
	{
		DWORD dwDirection = 0;
		if (pKeyBuffer[0x57] & 0xF0) dwDirection |= DIR_FORWARD; // w
		if (pKeyBuffer[0x53] & 0xF0) dwDirection |= DIR_BACKWARD; // s
		if (pKeyBuffer[0x41] & 0xF0) dwDirection |= DIR_LEFT; // a
		if (pKeyBuffer[0x44] & 0xF0) dwDirection |= DIR_RIGHT; // d
		/*if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
		if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;*/

		if (dwDirection) m_pPlayer->Move(dwDirection, 0.15f);
	}

	if (GetCapture() == m_hWnd)
	{
		SetCursor(NULL);
		POINT ptCursorPos;
		GetCursorPos(&ptCursorPos);
		float cxMouseDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 5.0f;
		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
		if (cxMouseDelta)
		{
			if (playerCameraStatus)
			{
				m_pPlayer->Rotate(0.0f, cxMouseDelta, 0.0f);
			}
		}
	}

	m_pPlayer->Update(m_GameTimer.GetTimeElapsed());
}

void CGameFramework::AnimateObjects()
{
	float fTimeElapsed = m_GameTimer.GetTimeElapsed();

	if (m_pPlayer) m_pPlayer->Animate(fTimeElapsed);

	switch (m_CurrentScene)
	{
	case SceneType::StartScene:
		if (startScene) startScene->Animate(fTimeElapsed);
		break;
	case SceneType::MenuScene:
		if (menuScene) menuScene->Animate(fTimeElapsed);
		break;
	case SceneType::Level_1:
		if (level1) level1->Animate(fTimeElapsed);
		break;
	case SceneType::Level_2:
		if (level2) level2->Animate(fTimeElapsed);
		break;
	default:
		if (m_pScene) m_pScene->Animate(fTimeElapsed);
		break;
	}
	
	
}

void CGameFramework::FrameAdvance()
{    
	m_GameTimer.Tick(60.0f);

	ProcessInput();

	AnimateObjects();

    ClearFrameBuffer(RGB(255, 255, 255));

	HDC hDC = m_hDCFrameBuffer;

	switch (m_CurrentScene)
	{
	case SceneType::StartScene:
	{
		if (startScene) startScene->Render(m_hDCFrameBuffer);

		// 터지는 중이고 2초 이상 지났으면
		if (startScene->getm_fExplodeTimer() && startScene->getm_fExplodeTimer() > 2.0f)
		{
			m_CurrentScene = SceneType::MenuScene;
		}
	}
		break;
	case SceneType::MenuScene:
	{
		if (menuScene) menuScene->Render(m_hDCFrameBuffer);
	}
		break;
	case SceneType::Level_1:
	{
		CCubeMesh* CCubeMesh_Level1 = new CCubeMesh(1.0f, 1.0f, 1.0f);
		m_pPlayer->SetMesh(CCubeMesh_Level1);
		m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 2.0f, -7.0f));
		CCamera* pCamera = m_pPlayer->GetCamera();
		if (level1) level1->Render(m_hDCFrameBuffer, pCamera);
	}
		break;
	case SceneType::Level_2:
	{
		CCamera* pCamera = m_pPlayer->GetCamera();
		if (level2) level2->Render(m_hDCFrameBuffer, pCamera);
	}
		break;
	default:
	{
		CCamera* pCamera = m_pPlayer->GetCamera();
		if (m_pScene) m_pScene->Render(m_hDCFrameBuffer, pCamera);
	}
		break;
	}

	PresentFrameBuffer();

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37);
	::SetWindowText(m_hWnd, m_pszFrameRate);
}


