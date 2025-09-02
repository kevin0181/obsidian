#pragma once

#include "Player.h"
#include "Scene.h"
#include "Timer.h"
#include "StartScene.h"
#include "MenuScene.h"
#include "Level1.h"
#include "Level2.h"

enum class SceneType { StartScene, MenuScene, Level_1, Level_2, NN }; // 장면 종류

class CGameFramework
{
public:
	CGameFramework() { }
	~CGameFramework() { }

private:
	HINSTANCE					m_hInstance = NULL;
	HWND						m_hWnd = NULL;

	bool						m_bActive = true;

	RECT						m_rcClient;

    HDC							m_hDCFrameBuffer = NULL;
    HBITMAP						m_hBitmapFrameBuffer = NULL;
    HBITMAP						m_hBitmapSelect = NULL;

	CPlayer*					m_pPlayer = NULL;
	bool 				        playerCameraStatus = true;

	CScene*						m_pScene = NULL;
	StartScene*                 startScene = NULL;
	MenuScene*					menuScene = NULL;
	Level1* 					level1 = NULL;
	Level2*                     level2 = NULL;

	CGameObject*				m_pLockedObject = NULL;

	CGameTimer					m_GameTimer;

	POINT						m_ptOldCursorPos;

	_TCHAR						m_pszFrameRate[50];

	SceneType m_CurrentScene = SceneType::StartScene; // -> 처음 시작시 시작 화면

public:
	void OnCreate(HINSTANCE hInstance, HWND hMainWnd);
	void OnDestroy();

	void BuildFrameBuffer();
	void ClearFrameBuffer(DWORD dwColor);
	void PresentFrameBuffer();

	void BuildObjects();
	void ReleaseObjects();

	void ProcessInput();
	void AnimateObjects();
	void FrameAdvance();

	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void SetActive(bool bActive) { m_bActive = bActive; }
};

