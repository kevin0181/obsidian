#pragma once
#include "stdafx.h"

//------------------------------------------------------------------------------------
//-------------------------------------CGameTimer-------------------------------------
//------------------------------------------------------------------------------------
/* ��ǻ�Ͱ� ���� ī����(Performance Counter) �ϵ��� ������ ������ 
���� ī���Ϳ� ���� ���ļ�(Performance Frequency)�� ����Ͽ� �ð� ������ �����Ѵ�. 
���� ���ļ��� ����� �� ������ ��Ƽ�̵�� Ÿ�̸Ӹ� ����Ѵ�. 
�� ��� �ð� ������ 0.001��(Millisecond)�̴�. 
���� ī���Ϳ� ���� �ڼ��� ������ ������ API ������ �����϶�. */

const ULONG MAX_SAMPLE_COUNT = 50; // 50ȸ�� ������ ó���ð��� �����Ͽ� ����Ѵ�.


class CGameTimer
{
public:
	CGameTimer();
	~CGameTimer();

	void Start() { }
	void Stop() { }
	void Reset();

	// Ÿ�̸��� �ð��� ����
	void Tick(float fLockFPS = 0.0f); 

	// ������ ����Ʈ ��ȯ
	unsigned long GetFrameRate(LPTSTR lpszString = nullptr, int nCharacters = 0);

	// �������� ��� ��� �ð� ��ȯ
	float GetTimeElapsed();

private:
	// ��ǻ�Ͱ� Performance Counter�� ������ �ִ°�
	bool m_bHardwareHasPerformanceCounter;

	// Scale Counter�� ��
	float m_fTimeScale;

	// ������ ������ ���� ������ �ð�
	float m_fTimeElapsed;

	// ������ �ð�
	__int64 m_nCurrentTime;

	// ������ �������� �ð�
	__int64 m_nLastTime;

	// ��ǻ���� Performance Frequency
	__int64 m_nPerformanceFrequency;

	// ������ �ð��� �����ϱ� ���� �迭
	float m_fFrameTime[MAX_SAMPLE_COUNT];

	// ������ ������ Ƚ��
	ULONG m_nSampleCount;

	// ������ ������ ����Ʈ
	unsigned long m_nCurrentFrameRate;

	// �ʴ� ������ ��
	unsigned long m_nFramesPerSecond;

	// ������ ����Ʈ ��� �ҿ� �ð�
	float m_fFPSTimeElapsed;

	bool m_bStopped;
};

