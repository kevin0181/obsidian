//-----------------------------------------------------------------------------
// File: CPlayer.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Player.h"
#include "Shader.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CPlayer

XMFLOAT3 CPlayer::m_pxmf3SphereVectors[EXPLOSION_DEBRISES];
CMesh* CPlayer::m_pExplosionMesh = NULL;


void CPlayer::PrepareExplosion(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	for (int i = 0; i < EXPLOSION_DEBRISES; i++) XMStoreFloat3(&m_pxmf3SphereVectors[i], Random::RandomUnitVectorOnSphere());
	m_pExplosionMesh = new CCubeMesh(pd3dDevice, pd3dCommandList, 3.f, 3.f, 3.f);
}

CPlayer::CPlayer()
{
	m_pCamera = NULL;
	m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_xmf3Gravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fMaxVelocityXZ = 0.0f;
	m_fMaxVelocityY = 20.0f;
	m_fFriction = 0.0f;

	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;
	fullHP = currentHP = 2000.f;
	m_pPlayerUpdatedContext = NULL;
	m_pCameraUpdatedContext = NULL;
}

CPlayer::~CPlayer()
{
	ReleaseShaderVariables();

	if (m_pCamera) delete m_pCamera;
}

void CPlayer::GetDamage()
{
	currentHP -= 5.f;
	if (currentHP <= 0)
		m_bBlowingUp = true;
}

void CPlayer::ResetOrientationVectors()
{
	m_xmf3Right = XMFLOAT3(1, 0, 0);
	m_xmf3Look = XMFLOAT3(0, 0, 1);
	m_xmf3Up = XMFLOAT3(0, 1, 0);
	OnPrepareRender();
}

void CPlayer::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	if (m_pCamera) m_pCamera->CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CPlayer::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CPlayer::ReleaseShaderVariables()
{
	if (m_pCamera) m_pCamera->ReleaseShaderVariables();
}

void CPlayer::Move(DWORD dwDirection, float fDistance, bool bUpdateVelocity)
{
	if (dwDirection)
	{
		XMFLOAT3 horizontalLook = m_xmf3Look;
		horizontalLook.y = 0.0f;
		horizontalLook = Vector3::Normalize(horizontalLook);

		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
		if (dwDirection & DIR_FORWARD) xmf3Shift = Vector3::Add(xmf3Shift, horizontalLook, fDistance);
		if (dwDirection & DIR_BACKWARD) xmf3Shift = Vector3::Add(xmf3Shift, horizontalLook, -fDistance);
		if (dwDirection & DIR_RIGHT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, fDistance);
		if (dwDirection & DIR_LEFT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, -fDistance);
		if (dwDirection & DIR_UP) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, fDistance);
		if (dwDirection & DIR_DOWN) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, -fDistance);
		
		Move(xmf3Shift, bUpdateVelocity);
	}
}

void CPlayer::ChangeMoveDirection()
{
	Vector3::ScalarProduct(m_xmf3Look, -1,false);
}

void CPlayer::LookAt(const XMFLOAT3& xmf3LookAt, const XMFLOAT3& xmf3Up)
{
	XMFLOAT4X4 xmf4x4View = Matrix4x4::LookAtLH(m_xmf3Position, xmf3LookAt, xmf3Up);
	m_xmf3Right = Vector3::Normalize(XMFLOAT3(xmf4x4View._11, xmf4x4View._21, xmf4x4View._31));
	m_xmf3Up = Vector3::Normalize(XMFLOAT3(xmf4x4View._12, xmf4x4View._22, xmf4x4View._32));
	m_xmf3Look = Vector3::Normalize(XMFLOAT3(xmf4x4View._13, xmf4x4View._23, xmf4x4View._33));
}

void CPlayer::Move(const XMFLOAT3& xmf3Shift, bool bUpdateVelocity)
{
	if (bUpdateVelocity) {
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Shift);
	}
	else {
		m_xmf3Position = Vector3::Add(m_xmf3Position, xmf3Shift);

		if (m_pGunFrame) {
			XMMATRIX worldMatrix = XMLoadFloat4x4(&m_pGunFrame->m_xmf4x4World);
			XMMATRIX recoilMatrix = XMMatrixTranslation(m_Recoiloffset.x, m_Recoiloffset.y, m_Recoiloffset.z);
			XMVECTOR positionVector = worldMatrix.r[3];


			// ������ �������� ��ġ ���Ϳ� ����
			XMVECTOR recoilOffset = XMLoadFloat3(&m_Recoiloffset);
			positionVector = XMVectorAdd(positionVector, recoilOffset);

			// ��ġ ���͸� �ٽ� ��Ŀ� ����
			worldMatrix.r[3] = positionVector;
			XMStoreFloat4x4(&m_pGunFrame->m_xmf4x4World, worldMatrix);
		}
		if (m_pCamera)
			m_pCamera->Move(xmf3Shift);
	}
}

void CPlayer::Rotate(float x, float y, float z)
{
	if (m_bBlowingUp) {
		return;
	}
	if (m_pCamera) {

		DWORD nCurrentCameraMode = m_pCamera->GetMode();
		if ((nCurrentCameraMode == FIRST_PERSON_CAMERA) || (nCurrentCameraMode == THIRD_PERSON_CAMERA))
		{
			// ���� ī�޶� ȸ��
			m_pCamera->Rotate(x, y, 0);
			if (x != 0.0f) {
				m_fPitch += x;
				if (m_fPitch > +20.0f) { x -= (m_fPitch - 20.0f); m_fPitch = +20.0f; }
				if (m_fPitch < -15.0f) { x -= (m_fPitch + 15.0f); m_fPitch = -15.0f; }

				XMVECTOR axis = XMLoadFloat3(&m_xmf3Right);
				XMMATRIX rotationMatrix = XMMatrixRotationAxis(axis, XMConvertToRadians(x));
				m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, rotationMatrix);
				m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, rotationMatrix);
			}
			if (y != 0.0f) {
				m_fYaw += y;
				if (m_fYaw > 360.0f) m_fYaw -= 360.0f;
				if (m_fYaw < 0.0f) m_fYaw += 360.0f;

				XMFLOAT3 upVector = { 0.0f, 1.0f, 0.0f };
				XMVECTOR axis = XMLoadFloat3(&upVector);
				XMMATRIX rotationMatrix = XMMatrixRotationAxis(axis, XMConvertToRadians(y));
				m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, rotationMatrix);
				m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, rotationMatrix);
				m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, rotationMatrix);
			}

		}
	}
}


void CPlayer::Update(float fTimeElapsed)
{
	if (m_bBlowingUp) {
		return;
	}
	/*�÷��̾��� �ӵ� ���͸� �߷� ���Ϳ� ���Ѵ�.
	�߷� ���Ϳ� fTimeElapsed�� ���ϴ� ���� �߷��� �ð��� ����ϵ��� �����Ѵٴ� �ǹ��̴�.*/
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
	float fLength = Vector3::Length(m_xmf3Velocity);
	float fDeceleration = (m_fFriction * fTimeElapsed);
	if (fDeceleration > fLength) fDeceleration = fLength;
	m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, Vector3::ScalarProduct(m_xmf3Velocity,
		-fDeceleration, true));
}

CCamera *CPlayer::OnChangeCamera(DWORD nNewCameraMode, DWORD nCurrentCameraMode)
{
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
	m_xmf4x4Transform._11 = m_xmf3Right.x; m_xmf4x4Transform._12 = m_xmf3Right.y; m_xmf4x4Transform._13 = m_xmf3Right.z;
	m_xmf4x4Transform._21 = m_xmf3Up.x; m_xmf4x4Transform._22 = m_xmf3Up.y; m_xmf4x4Transform._23 = m_xmf3Up.z;
	m_xmf4x4Transform._31 = m_xmf3Look.x; m_xmf4x4Transform._32 = m_xmf3Look.y; m_xmf4x4Transform._33 = m_xmf3Look.z;
	m_xmf4x4Transform._41 = m_xmf3Position.x; m_xmf4x4Transform._42 = m_xmf3Position.y; m_xmf4x4Transform._43 = m_xmf3Position.z;

	UpdateTransform(NULL);
}

void CPlayer::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	if(!m_bGameEnd)
		CGameObject::Render(pd3dCommandList, pCamera);
}

void CPlayer::InitBullets(CMesh* pbullet, float speed, float lifetime)
{
	for (int i = 0; i < BULLETS; i++) {
		CBulletObject* bullet = new CBulletObject();
		bullet->SetMesh(pbullet);
		bullet->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		bullet->SetRotationSpeed(300.0f);
		bullet->m_fMovingSpeed = speed;
		bullet->m_fLockingTime = lifetime;
		bullet->SetActive(false);
		bullet->SetShader(CMaterial::m_pIlluminatedShader);
		m_ppBullets.push_back(bullet);
	}
}

void CPlayer::CreateExp()
{
	for (int i = 0; i < EXPLOSION_DEBRISES; i++) {
		CExplosionCubeObject* EXP = new CExplosionCubeObject();
		EXP->SetMesh(m_pExplosionMesh);
		EXP->SetShader(CMaterial::m_pIlluminatedShader);
		m_exp.push_back(EXP);
	}
}


void CPlayer::Fire()
{
	if (m_bBlowingUp) return;
	CBulletObject* pBulletObject = NULL;
	for (int i = 0; i < m_ppBullets.size(); i++) {
		if (!m_ppBullets[i]->m_bActive) {
			pBulletObject = m_ppBullets[i];
			break;
		}
	}
	CPlayer::OnPrepareRender();

	if (pBulletObject) {
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Direction = GetLook();
		XMFLOAT3 xmf3FirePosition = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Direction, 2.0f, false));

		pBulletObject->m_xmf4x4World = m_xmf4x4World;

		pBulletObject->SetFirePosition(xmf3FirePosition);
		pBulletObject->SetMovingDirection(xmf3Direction);
		pBulletObject->SetActive(true);
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TankPlayer

TankPlayer::TankPlayer(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_pCamera = ChangeCamera(FIRST_PERSON_CAMERA, 0.0f);

//	CGameObject *pGameObject = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Apache.bin");
	CGameObject *pGameObject = CGameObject::LoadGeometryFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model2/M26.bin");

	pGameObject->Rotate(0.0f, 180.0f, 0.0f);
	pGameObject->SetScale(8.5f, 8.5f, 8.5f);
	pGameObject->SetPosition(0.f, 0.f,0.f);
	SetChild(pGameObject, true);
	CCubeMesh* bulletMesh = new CCubeMesh(pd3dDevice, pd3dCommandList, 8.f, 8.f, 8.f);
	OnInitialize();
	InitBullets(bulletMesh,600.f, 0.15f);
	CreateExp();
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

TankPlayer::~TankPlayer()
{
}


void TankPlayer::OnInitialize()
{
	m_pTurretFrame = FindFrame("TURRET");
	m_pCannonFrame = FindFrame("cannon");
	m_pGunFrame = FindFrame("gun");
}

void TankPlayer::Animate(float fTimeElapsed, XMFLOAT4X4* pxmf4x4Parent)
{
	if (m_bBlowingUp) {
	
		m_fElapsedTimes += fTimeElapsed;
		if (m_fElapsedTimes <= m_fDuration) {
			XMFLOAT3 xmf3Position = GetPosition();
			for (int i = 0; i < EXPLOSION_DEBRISES; i++) {
				m_pxmf4x4Transforms[i] = Matrix4x4::Identity();
				
				m_pxmf4x4Transforms[i]._41 = xmf3Position.x + m_pxmf3SphereVectors[i].x * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i]._42 = xmf3Position.y + m_pxmf3SphereVectors[i].y * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i]._43 = xmf3Position.z + m_pxmf3SphereVectors[i].z * m_fExplosionSpeed * m_fElapsedTimes;

				XMVECTOR axis = XMLoadFloat3(&m_pxmf3SphereVectors[i]);
				XMMATRIX rotationMatrix = XMMatrixRotationAxis(axis, m_fExplosionRotation * m_fElapsedTimes);

				XMMATRIX transformMatrix = XMLoadFloat4x4(&m_pxmf4x4Transforms[i]);
				transformMatrix = XMMatrixMultiply(rotationMatrix, transformMatrix);

				XMStoreFloat4x4(&m_pxmf4x4Transforms[i], transformMatrix);
			}

		}
		else {
		
			currentHP = fullHP;
			m_bBlowingUp = false;
			m_fElapsedTimes = 0.0f;
		}
	
	}
	else {
		CPlayer::Animate(fTimeElapsed, pxmf4x4Parent);
		for (auto& obj : m_ppBullets) {
			if (obj->m_bActive) obj->Animate(fTimeElapsed);
		}
	}
}


void TankPlayer::Fire()
{
	CBulletObject* pBulletObject = NULL;
	for (int i = 0; i < m_ppBullets.size(); i++) {
		if (!m_ppBullets[i]->m_bActive) {
			pBulletObject = m_ppBullets[i];
			break;
		}
	}
	CPlayer::OnPrepareRender();

	if (pBulletObject) {
		XMFLOAT3 xmf3Position = m_pGunFrame->GetPosition();
		xmf3Position.y += 10.f;
		m_pGunFrame->OnPrepareRender();
		XMFLOAT3 xmf3Direction = Vector3::ScalarProduct(m_pGunFrame->GetLook(), -1.0f, false);
		XMFLOAT3 xmf3FirePosition = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Direction, 50.0f, false));

		pBulletObject->m_xmf4x4World = m_xmf4x4World;

		pBulletObject->SetFirePosition(xmf3FirePosition);
		pBulletObject->SetMovingDirection(xmf3Direction);
		pBulletObject->SetActive(true);
	}
}

void TankPlayer::OnPrepareRender()
{
	if (m_bBlowingUp) {
		return;
	}
	CPlayer::OnPrepareRender();
}

void TankPlayer::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	if (m_bBlowingUp) {

		for (int i = 0; i < EXPLOSION_DEBRISES; i++) {
			m_exp[i]->m_xmf4x4World = m_pxmf4x4Transforms[i];
			m_exp[i]->Render(pd3dCommandList, pCamera);

		}
	}
	else
	{
		CPlayer::Render(pd3dCommandList, pCamera);
		for (auto& obj : m_ppBullets) {
			if (obj->m_bActive)obj->Render(pd3dCommandList, pCamera);

		}
	}
}


CCamera * TankPlayer::ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed)
{
	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;
	if (nCurrentCameraMode == nNewCameraMode) return(m_pCamera);
	switch (nNewCameraMode)
	{
		case FIRST_PERSON_CAMERA:
			SetFriction(130.f);
			SetGravity(XMFLOAT3(0.0f, -50.0f, 0.0f));
			SetMaxVelocityXZ(70.0f);
			SetMaxVelocityY(120.0f);
			m_pCamera = OnChangeCamera(FIRST_PERSON_CAMERA, nCurrentCameraMode);
			m_pCamera->SetTimeLag(0.0f);
			m_pCamera->SetOffset(XMFLOAT3(-25.0f, 25.0f, -25.0f));
			m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
			m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
			m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
			break;
		case SPACESHIP_CAMERA:
			SetFriction(100.5f);
			SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
			SetMaxVelocityXZ(40.0f);
			SetMaxVelocityY(40.0f);
			m_pCamera = OnChangeCamera(SPACESHIP_CAMERA, nCurrentCameraMode);
			m_pCamera->SetTimeLag(0.0f);
			m_pCamera->SetOffset(XMFLOAT3(30.0f, 25.0f, -34.0f));
			m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
			m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
			m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
			break;
		case THIRD_PERSON_CAMERA:
			SetFriction(20.5f);
			SetGravity(XMFLOAT3(0.0f, -50.0f, 0.0f));
			SetMaxVelocityXZ(70.0f);
			SetMaxVelocityY(120.0f);
			m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);
			m_pCamera->SetTimeLag(0.25f);
			m_pCamera->SetOffset(XMFLOAT3(0.0f, 105.0f, -140.0f));
			m_pCamera->GenerateProjectionMatrix(1.01f, 5000.0f, ASPECT_RATIO, 60.0f);
			m_pCamera->SetViewport(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f);
			m_pCamera->SetScissorRect(0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT);
			break;
		default:
			break;
	}

	m_pCamera->SetPosition(Vector3::Add(m_xmf3Position, m_pCamera->GetOffset()));
	Update(fTimeElapsed);

	return(m_pCamera);
}
