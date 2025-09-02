#pragma once

#include "stdafx.h"
#define ASPECT_RATIO (float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT)

//카메라의 종류(모드: Mode)를 나타내는 상수를 다음과 같이 선언한다. 
#define FIRST_PERSON_CAMERA	 0x01
#define SPACESHIP_CAMERA	 0x02	
#define THIRD_PERSON_CAMERA  0x03

//프레임 버퍼의 크기와 종횡비(Aspect Ratio)를 나타내는 상수를 다음과 같이 선언한다. 
#define ASPECT_RATIO (float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT))

class CPlayer;

struct VS_CB_CAMERA_INFO
{
	XMFLOAT4X4 m_xmf4x4View;
	XMFLOAT4X4 m_xmf4x4Projection;
};

class CCamera
{
protected:
	//카메라의 위치(월드좌표계) 벡터이다.
	XMFLOAT3	m_xmf3Position;

	XMFLOAT3	m_xmf3Right;
	XMFLOAT3	m_xmf3Up;
	XMFLOAT3	m_xmf3Look;

	float	m_fPitch;
	float	m_fRoll;
	float	m_fYaw;

	DWORD	m_nMode;

	XMFLOAT3	m_xmf3LookAtWorld;

	XMFLOAT3	m_xmf3Offset;

	float		m_fTimeLag;

	XMFLOAT4X4		m_xmf4x4View;
	XMFLOAT4X4		m_xmf4x4Projection;
	
	D3D12_VIEWPORT	m_d3dViewport;
	D3D12_RECT		m_d3dScissorRect;

	CPlayer* m_pPlayer = NULL;

public:
	CCamera();
	CCamera(CCamera* pCamera);
	virtual ~CCamera();

	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);

	void GenerateViewMatrix();
	void GenerateViewMatrix(XMFLOAT3 xmf3Position, XMFLOAT3 xmf3LookAt, XMFLOAT3 xmf3Up);

	void RegenerateViewMatrix();

	void GenerateProjectionMatrix(float fNearPlaneDistance, float fFarPlaneDistance, float fAspectRatio, float fFOVAngle);

	void SetViewPort(int xTopLeft, int yTopLeft, int nWidth, int nHeight, float fMinZ, float fMaxZ);

	void SetScissorRect(LONG xLeft, LONG yTop, LONG xRight, LONG yBottom);

	virtual void SetViewportsAndScissorRects(ID3D12GraphicsCommandList* pd3dCommandList);

	void SetPlayer(CPlayer* pPlayer) { m_pPlayer = pPlayer; }
	CPlayer* GetPlayer() { return(m_pPlayer); }

	void SetMode(DWORD nMode) { m_nMode = nMode; }
	DWORD GetMode() { return(m_nMode); }

	void SetPosition(XMFLOAT3 xmf3Position) { m_xmf3Position = xmf3Position; }
	XMFLOAT3& GetPosition() { return(m_xmf3Position); }

	void SetLookAtPosition(XMFLOAT3 xmf3LookAtWorld) { m_xmf3LookAtWorld = xmf3LookAtWorld; }
	XMFLOAT3& GetLookAtPosition() { return (m_xmf3LookAtWorld); }

	XMFLOAT3& GetRightVector() { return(m_xmf3Right); }
	XMFLOAT3& GetUpVector() { return(m_xmf3Up); }
	XMFLOAT3& GetLookVector() { return(m_xmf3Look); }

	float& GetPitch() { return(m_fPitch); }
	float& GetRoll() { return(m_fRoll); }
	float& GetYaw() { return(m_fYaw); }

	void SetOffset(XMFLOAT3 xmf3Offset) { m_xmf3Offset = xmf3Offset; }
	XMFLOAT3& GetOffset() { return(m_xmf3Offset); }

	void SetTimeLag(float fTimeLag) { m_fTimeLag = fTimeLag; }
	float GetTimeLag() { return(m_fTimeLag); }

	XMFLOAT4X4 GetViewMatrix() { return(m_xmf4x4View); }
	XMFLOAT4X4 GetProjectionMatrix() { return(m_xmf4x4Projection); }
	D3D12_VIEWPORT GetViewport() { return(m_d3dViewport); }
	D3D12_RECT GetScissorRect() { return(m_d3dScissorRect); }

	//카메라를 xmf3Shift 만큼 이동한다.
	virtual void Move(const XMFLOAT3& xmf3Shift) {
		m_xmf3Position.x += xmf3Shift.x;
		m_xmf3Position.y += xmf3Shift.y; m_xmf3Position.z += xmf3Shift.z;
	}

	//카메라를 x-축, y-축, z-축으로 회전하는 가상함수이다.
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f) { }

	//카메라의 이동, 회전에 따라 카메라의 정보를 갱신하는 가상함수이다.
	virtual void Update(XMFLOAT3& xmf3LookAt, float fTimeElapsed) { }

	//3인칭 카메라에서 카메라가 바라보는 지점을 설정한다. 일반적으로 플레이어를 바라보도록 설정한다.
	virtual void SetLookAt(XMFLOAT3& xmf3LookAt) { }
};

class CSpaceShipCamera : public CCamera
{
public:
	CSpaceShipCamera(CCamera* pCamera);
	virtual ~CSpaceShipCamera() { }
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
};

class CFirstPersonCamera : public CCamera // 1인칭 카메라
{
public:
	CFirstPersonCamera(CCamera* pCamera);
	virtual ~CFirstPersonCamera() { }
	virtual void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);
};

class CThirdPersonCamera : public CCamera // 3인칭 카메라
{
public:
	CThirdPersonCamera(CCamera* pCamera);
	virtual ~CThirdPersonCamera() { }
	virtual void Update(XMFLOAT3& xmf3LookAt, float fTimeElapsed);
	virtual void SetLookAt(XMFLOAT3& vLookAt);
};