#include "stdafx.h"
#include "Player.h"
#include "Shader.h"
#include "Scene.h"

CPlayer::CPlayer(int nMeshes) : CGameObject(nMeshes)
{
	m_pCamera = NULL;
	m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Gravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fMaxVelocityXZ = 0.0f;
	m_fMaxVelocityY = 0.0f;
	m_fFriction = 0.0f;
	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;
	m_pPlayerUpdatedContext = NULL;
	m_pCameraUpdatedContext = NULL;
}

CPlayer::~CPlayer()
{
	ReleaseShaderVariables();
	if (m_pCamera) delete m_pCamera;
}

void CPlayer::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	CGameObject::CreateShaderVariables(pd3dDevice, pd3dCommandList);
	if (m_pCamera) m_pCamera->CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CPlayer::ReleaseShaderVariables()
{
	CGameObject::ReleaseShaderVariables();
	if (m_pCamera) m_pCamera->ReleaseShaderVariables();
}

void CPlayer::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	CGameObject::UpdateShaderVariables(pd3dCommandList);
}

void CPlayer::Move(ULONG dwDirection, float fDistance, bool bUpdateVelocity)
{
	if (dwDirection)
	{
		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
		if (dwDirection & DIR_FORWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, fDistance);
		if (dwDirection & DIR_BACKWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, -fDistance);
		if (dwDirection & DIR_RIGHT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, fDistance);
		if (dwDirection & DIR_LEFT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, -fDistance);
		if (dwDirection & DIR_UP) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, fDistance);
		if (dwDirection & DIR_DOWN) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, -fDistance);
		Move(xmf3Shift, bUpdateVelocity);
	}
}

void CPlayer::Move(const XMFLOAT3& xmf3Shift, bool bUpdateVelocity)
{
	if (bUpdateVelocity)
	{
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Shift);
	}
	else
	{
		m_xmf3Position = Vector3::Add(m_xmf3Position, xmf3Shift);

		if (m_pCamera) m_pCamera->Move(xmf3Shift);
	}
}

void CPlayer::Rotate(float x, float y, float z)
{
	DWORD nCameraMode = m_pCamera->GetMode();
	if ((nCameraMode == FIRST_PERSON_CAMERA) || (nCameraMode == THIRD_PERSON_CAMERA))
	{
		if (x != 0.0f)
		{
			m_fPitch += x;
			if (m_fPitch > +89.0f) { x -= (m_fPitch - 89.0f); m_fPitch = +89.0f; }
			if (m_fPitch < -89.0f) { x -= (m_fPitch + 89.0f); m_fPitch = -89.0f; }
		}
		if (y != 0.0f)
		{
			m_fYaw += y;
			if (m_fYaw > 360.0f) m_fYaw -= 360.0f;
			if (m_fYaw < 0.0f) m_fYaw += 360.0f;
		}
		if (z != 0.0f)
		{
			m_fRoll += z;
			if (m_fRoll > +20.0f) { z -= (m_fRoll - 20.0f); m_fRoll = +20.0f; }
			if (m_fRoll < -20.0f) { z -= (m_fRoll + 20.0f); m_fRoll = -20.0f; }
		}
		m_pCamera->Rotate(x, y, z);
		
		if (y != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(y));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}
	}
	else if (nCameraMode == SPACESHIP_CAMERA)
	{
		m_pCamera->Rotate(x, y, z);
		if (x != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Right),
				XMConvertToRadians(x));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, xmmtxRotate);
		}
		if (y != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up),
				XMConvertToRadians(y));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}
		if (z != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Look),
				XMConvertToRadians(z));
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}
	}
	m_xmf3Look = Vector3::Normalize(m_xmf3Look);
	m_xmf3Right = Vector3::CrossProduct(m_xmf3Up, m_xmf3Look, true);
	m_xmf3Up = Vector3::CrossProduct(m_xmf3Look, m_xmf3Right, true);
}

void CPlayer::Update(float fTimeElapsed, bool s)
{
	m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, Vector3::ScalarProduct(m_xmf3Gravity, fTimeElapsed, false));

	/*�÷��̾��� �ӵ� ������ XZ-������ ũ�⸦ ���Ѵ�. 
	�̰��� XZ-����� �ִ� �ӷº��� ũ�� �ӵ� ������ x�� z-���� ������ �����Ѵ�.*/
	//float fLength = sqrtf(m_xmf3Velocity.x * m_xmf3Velocity.x + m_xmf3Velocity.z * m_xmf3Velocity.z);
	//float fMaxVelocityXZ = m_fMaxVelocityXZ * fTimeElapsed;
	//if (fLength > m_fMaxVelocityXZ)
	//{
	//	m_xmf3Velocity.x *= (fMaxVelocityXZ / fLength);
	//	m_xmf3Velocity.z *= (fMaxVelocityXZ / fLength);
	//}

	/*�÷��̾��� �ӵ� ������ y-������ ũ�⸦ ���Ѵ�. 
	�̰��� y-�� ������ �ִ� �ӷº��� ũ�� �ӵ� ������ y-���� ������ �����Ѵ�.*/
	//float fMaxVelocityY = m_fMaxVelocityY * fTimeElapsed;
	//fLength = sqrtf(m_xmf3Velocity.y * m_xmf3Velocity.y);
	//if (fLength > m_fMaxVelocityY) m_xmf3Velocity.y *= (fMaxVelocityY / fLength);
	
	//�÷��̾ �ӵ� ���� ��ŭ ������ �̵��Ѵ�(ī�޶� �̵��� ���̴�).
	XMFLOAT3 xmf3Velocity = Vector3::ScalarProduct(m_xmf3Velocity, fTimeElapsed, false);
	Move(xmf3Velocity, false);
	
	/*�÷��̾��� ��ġ�� ����� �� �߰��� ������ �۾��� �����Ѵ�. 
	�÷��̾��� ���ο� ��ġ�� ��ȿ�� ��ġ�� �ƴ� ���� �ְ� �Ǵ� �÷��̾��� �浹 �˻� ���� ������ �ʿ䰡 �ִ�. 
	�̷��� ��Ȳ���� �÷��̾��� ��ġ�� ��ȿ�� ��ġ�� �ٽ� ������ �� �ִ�.*/
	if (m_pPlayerUpdatedContext) OnPlayerUpdateCallback(fTimeElapsed);
	DWORD nCameraMode = m_pCamera->GetMode();

	//�÷��̾��� ��ġ�� ����Ǿ����Ƿ� 3��Ī ī�޶� �����Ѵ�.
	if (nCameraMode == THIRD_PERSON_CAMERA) m_pCamera->Update(m_xmf3Position, fTimeElapsed);

	//ī�޶��� ��ġ�� ����� �� �߰��� ������ �۾��� �����Ѵ�. 
	if (m_pCameraUpdatedContext) OnCameraUpdateCallback(fTimeElapsed);
	
	//ī�޶� 3��Ī ī�޶��̸� ī�޶� ����� �÷��̾� ��ġ�� �ٶ󺸵��� �Ѵ�. 
	//if (nCameraMode == THIRD_PERSON_CAMERA) m_pCamera->SetLookAt(m_xmf3Position);
	
	//ī�޶��� ī�޶� ��ȯ ����� �ٽ� �����Ѵ�.
	m_pCamera->RegenerateViewMatrix();
	
	/*�÷��̾��� �ӵ� ���Ͱ� ������ ������ ������ �Ǿ�� �Ѵٸ� ���� ���͸� �����Ѵ�. �ӵ� ������ �ݴ� ���� ���͸� ���ϰ� ���� ���ͷ� �����. 
	  ���� ����� �ð��� ����ϵ��� �Ͽ� �������� ���Ѵ�. ���� ���Ϳ� �������� ���Ͽ� ���� ���͸� ���Ѵ�. 
	  �ӵ� ���Ϳ� ���� ���͸� ���Ͽ� �ӵ� ���͸� ���δ�. �������� �ӷº��� ũ�� �ӷ��� 0�� �� ���̴�.*/
	if (!s) {
		float fLength = Vector3::Length(m_xmf3Velocity);
		float fDeceleration = (m_fFriction * fTimeElapsed);
		if (fDeceleration > fLength) fDeceleration = fLength;
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, Vector3::ScalarProduct(m_xmf3Velocity,
			-fDeceleration, true));
	}
	else {
		// Ű �Է��� ������ �ӵ��� ��� 0���� ����
		m_xmf3Velocity = XMFLOAT3(0.f, 0.f, 0.f);
	}
}

/*ī�޶� ������ �� ChangeCamera() �Լ����� ȣ��Ǵ� �Լ��̴�. 
nCurrentCameraMode�� ���� ī�޶��� ����̰� nNewCameraMode�� ���� ������ ī�޶� ����̴�.*/
CCamera* CPlayer::OnChangeCamera(DWORD nNewCameraMode, DWORD nCurrentCameraMode)
{
	//���ο� ī�޶��� ��忡 ���� ī�޶� ���� �����Ѵ�. 
	CCamera *pNewCamera = NULL;
	switch (nNewCameraMode)
	{
	case FIRST_PERSON_CAMERA:
		pNewCamera = new CFirstPersonCamera(m_pCamera);
		break;
	case THIRD_PERSON_CAMERA:
		pNewCamera = new CThirdPersonCamera(m_pCamera);
		break;
	case SPACESHIP_CAMERA:
		pNewCamera = new CSpaceShipCamera(m_pCamera);
		break;
	}
	if (nCurrentCameraMode == SPACESHIP_CAMERA)
	{
		m_xmf3Right = Vector3::Normalize(XMFLOAT3(m_xmf3Right.x, 0.0f, m_xmf3Right.z));
		m_xmf3Up = Vector3::Normalize(XMFLOAT3(0.0f, 1.0f, 0.0f));
		m_xmf3Look = Vector3::Normalize(XMFLOAT3(m_xmf3Look.x, 0.0f, m_xmf3Look.z));
		
		m_fPitch = 0.0f;
		m_fRoll = 0.0f;
		m_fYaw = Vector3::Angle(XMFLOAT3(0.0f, 0.0f, 1.0f), m_xmf3Look);

		if (m_xmf3Look.x < 0.0f) m_fYaw = -m_fYaw;
	}
	else if ((nNewCameraMode == SPACESHIP_CAMERA) && m_pCamera)
	{
		m_xmf3Right = m_pCamera->GetRightVector();
		m_xmf3Up = m_pCamera->GetUpVector();
		m_xmf3Look = m_pCamera->GetLookVector();
	}
	if (pNewCamera)
	{
		pNewCamera->SetMode(nNewCameraMode);
		pNewCamera->SetPlayer(this);
	}
	if (m_pCamera) delete m_pCamera;
	return(pNewCamera);
}


void CPlayer::OnPrepareRender()
{
	m_xmf4x4World._11 = m_xmf3Right.x;
	m_xmf4x4World._12 = m_xmf3Right.y;
	m_xmf4x4World._13 = m_xmf3Right.z;
	m_xmf4x4World._21 = m_xmf3Up.x;
	m_xmf4x4World._22 = m_xmf3Up.y;
	m_xmf4x4World._23 = m_xmf3Up.z;
	m_xmf4x4World._31 = m_xmf3Look.x;
	m_xmf4x4World._32 = m_xmf3Look.y;
	m_xmf4x4World._33 = m_xmf3Look.z;
	m_xmf4x4World._41 = m_xmf3Position.x;
	m_xmf4x4World._42 = m_xmf3Position.y;
	m_xmf4x4World._43 = m_xmf3Position.z;
}

void CPlayer::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	if (!IsActive()) return; // �׾����� ������ �� ��

	DWORD nCameraMode = (pCamera) ? pCamera->GetMode() : 0x00;
	//ī�޶� ��尡 3��Ī�̸� �÷��̾� ��ü�� �������Ѵ�. 
	if (nCameraMode == THIRD_PERSON_CAMERA)
	{
		if (m_pShader) m_pShader->Render(pd3dCommandList, pCamera);
		CGameObject::Render(pd3dCommandList, pCamera);
	}
}



//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//---------------------------------------------CAirplanePlayer----------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------

CAirplanePlayer::CAirplanePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes)
{
	CMesh *pAirplaneMesh = new CAirplaneMeshDiffused(pd3dDevice, pd3dCommandList, 
		20.0f, 20.0f, 4.0f, XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f));

	SetMesh(0, pAirplaneMesh);

	m_pCamera = ChangeCamera(SPACESHIP_CAMERA, 0.0f);
	
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	
	SetPosition(XMFLOAT3(0.0f, 0.0f, -50.0f));
	
	CPlayerShader* pShader = new CPlayerShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	SetShader(pShader);
}

CAirplanePlayer::~CAirplanePlayer()
{

}

void CAirplanePlayer::OnPrepareRender()
{
	CPlayer::OnPrepareRender();
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);

}

CCamera *CAirplanePlayer::ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;
	if (nCurrentCameraMode == nNewCameraMode) return(m_pCamera);
	switch (nNewCameraMode)
	{
	case FIRST_PERSON_CAMERA:
		//�÷��̾��� Ư���� 1��Ī ī�޶� ��忡 �°� �����Ѵ�. �߷��� �������� �ʴ´�. 
		SetFriction(200.0f);
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(125.0f);
		SetMaxVelocityY(400.0f);

		m_pCamera = OnChangeCamera(FIRST_PERSON_CAMERA, nCurrentCameraMode);

		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
		m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
		m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);

		break;
	case SPACESHIP_CAMERA:
		//�÷��̾��� Ư���� �����̽�-�� ī�޶� ��忡 �°� �����Ѵ�. �߷��� �������� �ʴ´�. 
		SetFriction(125.0f);
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(400.0f);
		SetMaxVelocityY(400.0f);

		m_pCamera = OnChangeCamera(SPACESHIP_CAMERA, nCurrentCameraMode);

		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
		m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
		m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);

		break;
	case THIRD_PERSON_CAMERA:
		//�÷��̾��� Ư���� 3��Ī ī�޶� ��忡 �°� �����Ѵ�. ���� ȿ���� ī�޶� �������� �����Ѵ�. 
		SetFriction(250.0f);
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(125.0f);
		SetMaxVelocityY(400.0f);

		m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);

		m_pCamera->SetTimeLag(0.25f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, -50.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
		m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
		m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);

		break;
	default:
		break;
	}
	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));
	Update(fTimeElapsed, false);
	return(m_pCamera);
}


// ----------------------------------------------------------------------------------------------------------

CTerrainPlayer::CTerrainPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext, int
	nMeshes) : CPlayer(nMeshes)
{
	m_pCamera = ChangeCamera(THIRD_PERSON_CAMERA, 0.0f);

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;

	float fHeight = pTerrain->GetHeight(pTerrain->GetWidth() * 0.5f,
		pTerrain->GetLength() * 0.5f);
	SetPosition(XMFLOAT3(pTerrain->GetWidth() * 0.5f, fHeight + 300.0f,
		pTerrain->GetLength() * 0.5f));

	SetPlayerUpdatedContext(pTerrain);

	SetCameraUpdatedContext(pTerrain);

	CTankMesh* pCubeMesh = new CTankMesh(pd3dDevice, pd3dCommandList,
		10.0f, 10.0f, 10.0f, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	SetMesh(0, pCubeMesh);

	CPlayerShader *pShader = new CPlayerShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	SetShader(pShader);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

CTerrainPlayer::~CTerrainPlayer()
{

}

CCamera* CTerrainPlayer::ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;
	if (nCurrentCameraMode == nNewCameraMode) return(m_pCamera);
	switch (nNewCameraMode)
	{
	case FIRST_PERSON_CAMERA:
		SetFriction(250.0f);
		//1��Ī ī�޶��� �� �÷��̾ y-�� �������� �߷��� �ۿ��Ѵ�. 
		SetGravity(XMFLOAT3(0.0f, -250.0f, 0.0f));
		SetMaxVelocityXZ(300.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(FIRST_PERSON_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
		break;
	case SPACESHIP_CAMERA:
		SetFriction(125.0f);
		//�����̽� �� ī�޶��� �� �÷��̾ �߷��� �ۿ����� �ʴ´�. 
		SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
		SetMaxVelocityXZ(300.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(SPACESHIP_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.0f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
		break;
	case THIRD_PERSON_CAMERA:
		SetFriction(250.0f);
		//3��Ī ī�޶��� �� �÷��̾ y-�� �������� �߷��� �ۿ��Ѵ�. 
		SetGravity(XMFLOAT3(0.0f, -250.0f, 0.0f));
		SetMaxVelocityXZ(300.0f);
		SetMaxVelocityY(400.0f);
		m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);
		m_pCamera->SetTimeLag(0.25f);
		m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, -50.0f));
		m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
		break;
	default:
		break;
	}
	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));
	Update(fTimeElapsed, false);
	return(m_pCamera);
}

void CTerrainPlayer::OnPlayerUpdateCallback(float fTimeElapsed)
{
	XMFLOAT3 xmf3PlayerPosition = GetPosition();
	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)m_pPlayerUpdatedContext;

	float fHeight = pTerrain->GetHeight(xmf3PlayerPosition.x, xmf3PlayerPosition.z) + 6.0f;

	if (xmf3PlayerPosition.y < fHeight)
	{
		XMFLOAT3 xmf3PlayerVelocity = GetVelocity();

		xmf3PlayerVelocity.y = 0.0f;
		SetVelocity(xmf3PlayerVelocity);

		xmf3PlayerPosition.y = fHeight;
		SetPosition(xmf3PlayerPosition);
	}
}

void CTerrainPlayer::OnCameraUpdateCallback(float fTimeElapsed)
{
	XMFLOAT3 xmf3CameraPosition = m_pCamera->GetPosition();

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)m_pCameraUpdatedContext;
	float fHeight = pTerrain->GetHeight(xmf3CameraPosition.x, xmf3CameraPosition.z) + 5.0f;

	if (xmf3CameraPosition.y <= fHeight)
	{
		xmf3CameraPosition.y = fHeight;
		m_pCamera->SetPosition(xmf3CameraPosition);

		if (m_pCamera->GetMode() == THIRD_PERSON_CAMERA)
		{
			CThirdPersonCamera* p3rdPersonCamera = (CThirdPersonCamera*)m_pCamera;
			p3rdPersonCamera->SetLookAt(GetPosition());
		}
	}
}


// ----------------------------------------------------------------------------------------------------------

CStartScenePlayer::CStartScenePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes) : CPlayer(nMeshes)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;


	m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);
	m_pCamera->SetTimeLag(0.25f);
	m_pCamera->SetOffset(XMFLOAT3(450.0f, 20.0f, -1400.0f));
	m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));

	SetPosition(XMFLOAT3(0.0f, 0.0f, -100.0f));
}

CStartScenePlayer::~CStartScenePlayer()
{

}


// ----------------------------------------------------------------------------------------------------------

CMenuScenePlayer::CMenuScenePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes) : CPlayer(nMeshes)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;


	m_pCamera = OnChangeCamera(FIRST_PERSON_CAMERA, nCurrentCameraMode);
	m_pCamera->SetTimeLag(0.25f);
	m_pCamera->SetOffset(XMFLOAT3(0.0f, 0.0f, -50.0f));
	m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));

	SetPosition(XMFLOAT3(3000.0f, 0.0f, -2000.0f));

}

CMenuScenePlayer::~CMenuScenePlayer()
{

}



// ----------------------------------------------------------------------------------------------------------

CLevel1ScenePlayer::CLevel1ScenePlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, int nMeshes) : CPlayer(nMeshes)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;


	m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);
	m_pCamera->SetTimeLag(0.25f);
	m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, -50.0f));
	m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));

	SetPosition(XMFLOAT3(0.0f, 0.0f, -100.0f));

	CMesh* pAirplaneMesh = new CAirplaneMeshDiffused(pd3dDevice, pd3dCommandList,
		10.0f, 10.0f, 2.0f, XMFLOAT4(0.0f, 0.5f, 0.0f, 0.0f));

	SetMesh(0, pAirplaneMesh);

	CPlayerShader* pShader = new CPlayerShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	SetShader(pShader);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

CLevel1ScenePlayer::~CLevel1ScenePlayer()
{

}

void CLevel1ScenePlayer::OnPrepareRender()
{
	CPlayer::OnPrepareRender();
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(70.0f), 0.0f, 0.0f);
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);

}

// ----------------------------------------------------------------------------------------------------------

CEnarmyTankPlayer::CEnarmyTankPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext, CScene* pScene, int
	nMeshes) : CPlayer(nMeshes)
{

	m_pScene = pScene;

	m_pCamera = ChangeCamera(THIRD_PERSON_CAMERA, 0.0f);

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;

	float fHeight = pTerrain->GetHeight(pTerrain->GetWidth() * 0.5f,
		pTerrain->GetLength() * 0.5f);
	SetPosition(XMFLOAT3(pTerrain->GetWidth() * 0.5f, fHeight + 100.0f,
		pTerrain->GetLength() * 0.5f));

	SetPlayerUpdatedContext(pTerrain);

	SetCameraUpdatedContext(pTerrain);

	CTankMesh* pCubeMesh = new CTankMesh(pd3dDevice, pd3dCommandList,
		10.0f, 10.0f, 10.0f, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));

	SetMesh(0, pCubeMesh);

	CPlayerShader* pShader = new CPlayerShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	SetShader(pShader);
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

CEnarmyTankPlayer::~CEnarmyTankPlayer()
{

}


CCamera* CEnarmyTankPlayer::ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;
	if (nCurrentCameraMode == nNewCameraMode) return(m_pCamera);

	SetFriction(250.0f);
	//3��Ī ī�޶��� �� �÷��̾ y-�� �������� �߷��� �ۿ��Ѵ�. 
	SetGravity(XMFLOAT3(0.0f, -500.0f, 0.0f));
	SetMaxVelocityXZ(300.0f);
	SetMaxVelocityY(400.0f);
	m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);
	m_pCamera->SetTimeLag(0.25f);
	m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, -50.0f));
	m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));
	Update(fTimeElapsed);

	return(m_pCamera);
}

void CEnarmyTankPlayer::OnPlayerUpdateCallback(float fTimeElapsed)
{
	XMFLOAT3 xmf3PlayerPosition = GetPosition();
	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)m_pPlayerUpdatedContext;

	float fHeight = pTerrain->GetHeight(xmf3PlayerPosition.x, xmf3PlayerPosition.z) + 6.0f;

	if (xmf3PlayerPosition.y < fHeight)
	{
		XMFLOAT3 xmf3PlayerVelocity = GetVelocity();

		xmf3PlayerVelocity.y = 0.0f;
		SetVelocity(xmf3PlayerVelocity);

		xmf3PlayerPosition.y = fHeight;
		SetPosition(xmf3PlayerPosition);
	}
}

void CEnarmyTankPlayer::OnCameraUpdateCallback(float fTimeElapsed)
{
	XMFLOAT3 xmf3CameraPosition = m_pCamera->GetPosition();

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)m_pCameraUpdatedContext;
	float fHeight = pTerrain->GetHeight(xmf3CameraPosition.x, xmf3CameraPosition.z) + 5.0f;

	if (xmf3CameraPosition.y <= fHeight)
	{
		xmf3CameraPosition.y = fHeight;
		m_pCamera->SetPosition(xmf3CameraPosition);

		if (m_pCamera->GetMode() == THIRD_PERSON_CAMERA)
		{
			CThirdPersonCamera* p3rdPersonCamera = (CThirdPersonCamera*)m_pCamera;
			p3rdPersonCamera->SetLookAt(GetPosition());
		}
	}
}

void CEnarmyTankPlayer::Update(float fTimeElapsed) {
	CPlayer::Update(fTimeElapsed, false);

	// �̵� �ð� ����
	m_fMoveTime += fTimeElapsed;

	// ���� �ð����� ������ ����
	if (m_fMoveTime >= m_fMaxMoveTime)
	{
		// ������ ���� ���� ����
		float fAngle = (rand() % 360) * XM_PI / 180.0f;
		m_xmf3MoveDirection = Vector3::Normalize(XMFLOAT3(cosf(fAngle), 0.0f, sinf(fAngle)));

		// ���� ���� �ð� �������� ���� (1 ~ 3��)
		m_fMoveTime = 0.0f;
		m_fMaxMoveTime = 1.0f + ((rand() % 2000) / 1000.0f);
	}

	// ���� ��ġ
	XMFLOAT3 pos = GetPosition();

	// �̵� �Ÿ�
	XMFLOAT3 delta = Vector3::ScalarProduct(m_xmf3MoveDirection, 30.0f * fTimeElapsed, false);
	XMFLOAT3 newPos = { pos.x + delta.x, pos.y, pos.z + delta.z };

	// ���� ũ��
	float width = 5000.0f;
	float length = 5000.0f;

	// ��� ���̸� ���� ����
	if (newPos.x < 0.0f || newPos.x > width || newPos.z < 0.0f || newPos.z > length)
	{
		m_xmf3MoveDirection.x *= -1.0f;
		m_xmf3MoveDirection.z *= -1.0f;
		return;
	}

	SetPosition(newPos);
	SetLookVector(m_xmf3MoveDirection);

	m_fFireElapsed += fTimeElapsed;
	if (m_fFireElapsed >= m_fFireCooldown)
	{
		m_fFireElapsed = 0.0f;
		if (m_pScene) m_pScene->FireEnemyBullet(this);
	}
}
