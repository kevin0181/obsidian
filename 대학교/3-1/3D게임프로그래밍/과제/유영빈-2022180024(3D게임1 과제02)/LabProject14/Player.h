#pragma once

#define DIR_FORWARD 0x01
#define DIR_BACKWARD 0x02
#define DIR_LEFT 0x04
#define DIR_RIGHT 0x08
#define DIR_UP 0x10
#define DIR_DOWN 0x20

#include "GameObject.h"
#include "Camera.h"

class CScene; // 전방 선언

class CPlayer : public CGameObject
{
protected:
	XMFLOAT3 m_xmf3Position;
	XMFLOAT3 m_xmf3Right;
	XMFLOAT3 m_xmf3Up;
	XMFLOAT3 m_xmf3Look;

	float m_fPitch;
	float m_fYaw;
	float m_fRoll;

	XMFLOAT3 m_xmf3Velocity;

	XMFLOAT3 m_xmf3Gravity;
	
	float m_fMaxVelocityXZ;
	
	float m_fMaxVelocityY;
	 
	float m_fFriction;

	LPVOID m_pPlayerUpdatedContext;
	
	LPVOID m_pCameraUpdatedContext;
	
	CCamera *m_pCamera = NULL;

public:
	CPlayer(int nMeshes = 1);
	virtual ~CPlayer();

	XMFLOAT3 GetPosition() { return(m_xmf3Position); }
	XMFLOAT3 GetLookVector() { return(m_xmf3Look); }
	XMFLOAT3 GetUpVector() { return(m_xmf3Up); }
	XMFLOAT3 GetRightVector() { return(m_xmf3Right); }

	void SetLookVector(const XMFLOAT3& xmf3Look)
	{
		m_xmf3Look = Vector3::Normalize(xmf3Look);

		XMFLOAT3 xmf3WorldUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_xmf3Right = Vector3::Normalize(Vector3::CrossProduct(xmf3WorldUp, m_xmf3Look));

		m_xmf3Up = Vector3::CrossProduct(m_xmf3Look, m_xmf3Right, true);
	}

	bool m_pActive = true;
	const bool IsActive() { return m_pActive; }
	void SetActive(bool s) { m_pActive = s; }


	void SetFriction(float fFriction) { m_fFriction = fFriction; }
	void SetGravity(const XMFLOAT3& xmf3Gravity) { m_xmf3Gravity = xmf3Gravity; }
	void SetMaxVelocityXZ(float fMaxVelocity) { m_fMaxVelocityXZ = fMaxVelocity; }
	void SetMaxVelocityY(float fMaxVelocity) { m_fMaxVelocityY = fMaxVelocity; }
	void SetVelocity(XMFLOAT3& xmf3Velocity) { m_xmf3Velocity = xmf3Velocity; }

	void SetPosition(const XMFLOAT3& xmf3Position) {
		Move(XMFLOAT3(xmf3Position.x - m_xmf3Position.x, 
			xmf3Position.y - m_xmf3Position.y, xmf3Position.z - m_xmf3Position.z), false);
	}
	XMFLOAT3& GetVelocity() { return(m_xmf3Velocity); }
	float GetYaw() { return(m_fYaw); }
	float GetPitch() { return(m_fPitch); }
	float GetRoll() { return(m_fRoll); }
	CCamera* GetCamera() { return(m_pCamera); }
	void SetCamera(CCamera* pCamera) { m_pCamera = pCamera; }
	
	//플레이어를 이동하는 함수이다. 
	void Move(ULONG nDirection, float fDistance, bool bVelocity = false);
	void Move(const XMFLOAT3& xmf3Shift, bool bVelocity = false);
	void Move(float fxOffset = 0.0f, float fyOffset = 0.0f, float fzOffset = 0.0f);
	
	//플레이어를 회전하는 함수이다. 
	void Rotate(float x, float y, float z);
	
	//플레이어의 위치와 회전 정보를 경과 시간에 따라 갱신하는 함수이다. 
	void Update(float fTimeElapsed, bool s);
	
	//플레이어의 위치가 바뀔 때마다 호출되는 함수와 그 함수에서 사용하는 정보를 설정하는 함수이다.
	virtual void OnPlayerUpdateCallback(float fTimeElapsed) { }
	void SetPlayerUpdatedContext(LPVOID pContext) { m_pPlayerUpdatedContext = pContext; }
	
	//카메라의 위치가 바뀔 때마다 호출되는 함수와 그 함수에서 사용하는 정보를 설정하는 함수이다. 
	virtual void OnCameraUpdateCallback(float fTimeElapsed) { }
	void SetCameraUpdatedContext(LPVOID pContext) { m_pCameraUpdatedContext = pContext; }

	virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
	virtual void ReleaseShaderVariables();
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);

	//카메라를 변경하기 위하여 호출하는 함수이다. 
	CCamera *OnChangeCamera(DWORD nNewCameraMode, DWORD nCurrentCameraMode);
	virtual CCamera* ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed) {
		return(NULL);
	}

	//플레이어의 위치와 회전축으로부터 월드 변환 행렬을 생성하는 함수이다. 
	virtual void OnPrepareRender();

	//플레이어의 카메라가 3인칭 카메라일 때 플레이어(메쉬)를 렌더링한다. 
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera = NULL);
};


class CAirplanePlayer : public CPlayer
{
public:
	CAirplanePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes = 1);
	virtual ~CAirplanePlayer();
	virtual CCamera* ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed);
	virtual void OnPrepareRender();
};


class CTerrainPlayer : public CPlayer
{
public:
	CTerrainPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext, int nMeshes = 1);
	virtual ~CTerrainPlayer();

	virtual CCamera* ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed);

	virtual void OnPlayerUpdateCallback(float fTimeElapsed);
	virtual void OnCameraUpdateCallback(float fTimeElapsed);
};


class CStartScenePlayer : public CPlayer
{
public:
	CStartScenePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes = 1);
	virtual ~CStartScenePlayer();
};

class CMenuScenePlayer : public CPlayer
{
public:
	CMenuScenePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes = 1);
	virtual ~CMenuScenePlayer();
};

class CLevel1ScenePlayer : public CPlayer
{
public:
	CLevel1ScenePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes = 1);
	virtual ~CLevel1ScenePlayer();
	virtual void OnPrepareRender();
};

class CEnarmyTankPlayer : public CPlayer
{
public:
	CEnarmyTankPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList,
		ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext, CScene* pScene,int nMeshes = 1);
	virtual ~CEnarmyTankPlayer();

	virtual CCamera* ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed);

	virtual void OnPlayerUpdateCallback(float fTimeElapsed);
	virtual void OnCameraUpdateCallback(float fTimeElapsed);

	bool m_bActive = true;
	void SetActive(bool b) { m_bActive = b; }
	bool IsActive() const { return m_bActive; }

	void Update(float fTimeElapsed);

	void SetLookVector(const XMFLOAT3& xmf3Look)
	{
		m_xmf3Look = Vector3::Normalize(xmf3Look);

		XMFLOAT3 xmf3WorldUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_xmf3Right = Vector3::Normalize(Vector3::CrossProduct(xmf3WorldUp, m_xmf3Look));

		m_xmf3Up = Vector3::CrossProduct(m_xmf3Look, m_xmf3Right, true);
	}

	XMFLOAT3 m_xmf3MoveDirection;
	float m_fMoveTime = 0.0f;
	float m_fMaxMoveTime = 1.0f;

	float m_fFireCooldown = 3.0f + static_cast<float>(rand() % 2001) / 1000.0f; // 3.0 ~ 5.0
	float m_fFireElapsed = 0.0f;      // 누적 시간

	CScene* m_pScene = NULL;
};