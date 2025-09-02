#include "stdafx.h"
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "SceneType.h"

CGameObject::CGameObject(int nMeshes)
{
	m_xmf4x4World = Matrix4x4::Identity();

	m_nMeshes = nMeshes;
	m_ppMeshes = NULL;

	if (m_nMeshes > 0)
	{
		m_ppMeshes = new CMesh * [m_nMeshes];
		for (int i = 0; i < m_nMeshes; i++) m_ppMeshes[i] = NULL;
	}
}

CGameObject::~CGameObject()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Release();
			m_ppMeshes[i] = NULL;
		}
		delete[] m_ppMeshes;
		m_ppMeshes = NULL;
	}

	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CGameObject::SetShader(CShader* pShader)
{
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader;
	if (m_pShader) m_pShader->AddRef();
}

void CGameObject::SetMesh(int nIndex, CMesh* pMesh)
{
	if (m_ppMeshes)
	{
		if (m_ppMeshes[nIndex]) m_ppMeshes[nIndex]->Release();
		m_ppMeshes[nIndex] = pMesh;
		if (pMesh) pMesh->AddRef();
	}
}

void CGameObject::ReleaseUploadBuffers()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->ReleaseUploadBuffers();
		}
	}
}

void CGameObject::Animate(float fTimeElapsed)
{

}

void CGameObject::OnPrepareRender()
{

}


void CGameObject::Rotate(XMFLOAT3* pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis),
		XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender();

	if (IsVisible(pCamera))
	{
		UpdateShaderVariables(pd3dCommandList);

		if (m_ppMeshes)
		{
			for (int i = 0; i < m_nMeshes; i++)
			{
				if (m_ppMeshes[i]) m_ppMeshes[i]->Render(pd3dCommandList);
			}
		}
	}
}

void CGameObject::CreateShaderVariables(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList)
{

}

void CGameObject::ReleaseShaderVariables()
{

}

void CGameObject::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
	
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

XMFLOAT3 CGameObject::GetPosition()
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

XMFLOAT3 CGameObject::GetLook()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._31, m_xmf4x4World._32,
		m_xmf4x4World._33)));
}

XMFLOAT3 CGameObject::GetUp()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._21, m_xmf4x4World._22,
		m_xmf4x4World._23)));
}

XMFLOAT3 CGameObject::GetRight()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._11, m_xmf4x4World._12,
		m_xmf4x4World._13)));
}

void CGameObject::MoveStrafe(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveUp(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::MoveForward(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch),
		XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

bool CGameObject::IsVisible(CCamera* pCamera)
{
	OnPrepareRender();
	bool bIsVisible = false;
	//BoundingOrientedBox xmBoundingBox = m_pMesh->GetBoundingBox();
	for (int i = 0; i < m_nMeshes; i++) {
		if (m_ppMeshes[i])
		{
			BoundingOrientedBox xmBoundingBox = m_ppMeshes[i]->GetBoundingBox();
			xmBoundingBox.Transform(xmBoundingBox, XMLoadFloat4x4(&m_xmf4x4World));
			if (pCamera) bIsVisible = pCamera->IsInFrustum(xmBoundingBox);
			return(bIsVisible);
		}
	}
}

void CGameObject::GenerateRayForPicking(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4&
	xmf4x4View, XMFLOAT3* pxmf3PickRayOrigin, XMFLOAT3* pxmf3PickRayDirection)
{
	XMFLOAT4X4 xmf4x4WorldView = Matrix4x4::Multiply(m_xmf4x4World, xmf4x4View);
	XMFLOAT4X4 xmf4x4Inverse = Matrix4x4::Inverse(xmf4x4WorldView);
	XMFLOAT3 xmf3CameraOrigin(0.0f, 0.0f, 0.0f);

	*pxmf3PickRayOrigin = Vector3::TransformCoord(xmf3CameraOrigin, xmf4x4Inverse);

	*pxmf3PickRayDirection = Vector3::TransformCoord(xmf3PickPosition, xmf4x4Inverse);

	*pxmf3PickRayDirection = Vector3::Normalize(Vector3::Subtract(*pxmf3PickRayDirection, *pxmf3PickRayOrigin));
}

int CGameObject::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4&
	xmf4x4View, float* pfHitDistance)
{
	int nIntersected = 0;
	for (int i = 0; i < m_nMeshes; i++)
	{
		if (m_ppMeshes[i])
		{
			XMFLOAT3 xmf3PickRayOrigin, xmf3PickRayDirection;
			GenerateRayForPicking(xmf3PickPosition, xmf4x4View, &xmf3PickRayOrigin, &xmf3PickRayDirection);

			nIntersected = m_ppMeshes[i]->CheckRayIntersection(xmf3PickRayOrigin,
				xmf3PickRayDirection, pfHitDistance);
		}
	}
	return(nIntersected);
}

//------------------------------------------------------------------------------------------------
//----------------------------------------COrbitingObject-----------------------------------------
//------------------------------------------------------------------------------------------------

COrbitingObject::COrbitingObject(int nMeshes) : CGameObject(nMeshes)
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 60.0f;
}

COrbitingObject::~COrbitingObject()
{

}

void COrbitingObject::Animate(float fTimeElapsed)
{
	XMFLOAT3 center = { 300.0f, 0.0f, 0.0f }; // 공전 중심점

	XMFLOAT3 pos = GetPosition();
	XMVECTOR vPos = XMLoadFloat3(&pos);
	XMVECTOR vCenter = XMLoadFloat3(&center);

	// 중심 기준 상대 위치
	XMVECTOR vRelative = XMVectorSubtract(vPos, vCenter);

	// 회전
	XMMATRIX mtxRotation = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3RotationAxis), XMConvertToRadians(m_fRotationSpeed * fTimeElapsed));
	vRelative = XMVector3TransformCoord(vRelative, mtxRotation);

	// 다시 중심점 위치로 이동
	vPos = XMVectorAdd(vRelative, vCenter);

	XMFLOAT3 newPos;
	XMStoreFloat3(&newPos, vPos);
	SetPosition(newPos);
}


//------------------------------------------------------------------------------------------------
//----------------------------------------CRotatingObject-----------------------------------------
//------------------------------------------------------------------------------------------------

CRotatingObject::CRotatingObject(int nMeshes) : CGameObject(nMeshes)
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 15.0f;
}

CRotatingObject::~CRotatingObject()
{

}

void CRotatingObject::Animate(float fTimeElapsed)
{
	CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
}



//----------------------------------------------------------------------------------------------------
//----------------------------------------CHeightMapTerrain-------------------------------------------
//----------------------------------------------------------------------------------------------------

CHeightMapTerrain::CHeightMapTerrain(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, LPCTSTR pFileName, int
	nWidth, int nLength, int nBlockWidth, int nBlockLength, XMFLOAT3 xmf3Scale, XMFLOAT4
	xmf4Color) : CGameObject(0)
{
	m_nWidth = nWidth;
	m_nLength = nLength;

	int cxQuadsPerBlock = nBlockWidth - 1;
	int czQuadsPerBlock = nBlockLength - 1;

	m_xmf3Scale = xmf3Scale;

	m_pHeightMapImage = new CHeightMapImage(pFileName, nWidth, nLength, xmf3Scale);

	long cxBlocks = (m_nWidth - 1) / cxQuadsPerBlock;
	long czBlocks = (m_nLength - 1) / czQuadsPerBlock;

	m_nMeshes = cxBlocks * czBlocks;

	m_ppMeshes = new CMesh * [m_nMeshes];
	for (int i = 0; i < m_nMeshes; i++) m_ppMeshes[i] = NULL;

	CHeightMapGridMesh* pHeightMapGridMesh = NULL;

	for (int z = 0, zStart = 0; z < czBlocks; z++)
	{
		for (int x = 0, xStart = 0; x < cxBlocks; x++)
		{
			xStart = x * (nBlockWidth - 1);
			zStart = z * (nBlockLength - 1);

			pHeightMapGridMesh = new CHeightMapGridMesh(pd3dDevice, pd3dCommandList, xStart,
				zStart, nBlockWidth, nBlockLength, xmf3Scale, xmf4Color, m_pHeightMapImage);

			SetMesh(x + (z * cxBlocks), pHeightMapGridMesh);
		}
	}

	CTerrainShader *pShader = new CTerrainShader();
	pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);

	SetShader(pShader);
}

CHeightMapTerrain::~CHeightMapTerrain(void)
{
	if (m_pHeightMapImage) delete m_pHeightMapImage;
}

void CHeightMapTerrain::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	m_pShader->Render(pd3dCommandList, pCamera);

	CGameObject::Render(pd3dCommandList, pCamera);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


CExplosionCubeObject::CExplosionCubeObject(int nMeshes)
{
	m_xmf4x4World = Matrix4x4::Identity();

	m_nMeshes = nMeshes;
	m_ppMeshes = NULL;

	if (m_nMeshes > 0)
	{
		m_ppMeshes = new CMesh * [m_nMeshes];
		for (int i = 0; i < m_nMeshes; i++) m_ppMeshes[i] = NULL;
	}
}

CExplosionCubeObject::~CExplosionCubeObject()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Release();
			m_ppMeshes[i] = NULL;
		}
		delete[] m_ppMeshes;
		m_ppMeshes = NULL;
	}

	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CExplosionCubeObject::Move(XMFLOAT3& vDirection, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);
}

void CExplosionCubeObject::Animate(float fElapsedTime, XMFLOAT4X4* pxmf4x4Parent)
{
	if (!m_bExploding) return; // 폭발 활성화된 경우에만 실행

	CGameObject::Animate(fElapsedTime);

	m_fLivedTime += fElapsedTime;

	if (m_fLivedTime >= m_fLifetime)
	{
		m_bActive = false;
		m_bExploding = false;
		if (m_CurrentScene == SceneType::StartScene) {
			m_CurrentScene = SceneType::MenuScene;
		}
	}

	XMFLOAT3 direction = GetMovingDirection();
	float speed = GetMovingSpeed();
	Move(direction, speed * fElapsedTime);
}

void CExplosionCubeObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	if (!m_bExploding) return;

	CGameObject::Render(pd3dCommandList, pCamera);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


CMenuSceneObject::CMenuSceneObject(int nMeshes)
{
	m_xmf4x4World = Matrix4x4::Identity();

	m_nMeshes = nMeshes;
	m_ppMeshes = NULL;

	if (m_nMeshes > 0)
	{
		m_ppMeshes = new CMesh * [m_nMeshes];
		for (int i = 0; i < m_nMeshes; i++) m_ppMeshes[i] = NULL;
	}
}

CMenuSceneObject::~CMenuSceneObject()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Release();
			m_ppMeshes[i] = NULL;
		}
		delete[] m_ppMeshes;
		m_ppMeshes = NULL;
	}

	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CMenuSceneObject::Animate(float fElapsedTime, XMFLOAT4X4* pxmf4x4Parent)
{
	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//


CBulletObject::CBulletObject(int nMeshes)
{
	m_xmf4x4World = Matrix4x4::Identity();

	m_nMeshes = nMeshes;
	m_ppMeshes = NULL;

	if (m_nMeshes > 0)
	{
		m_ppMeshes = new CMesh * [m_nMeshes];
		for (int i = 0; i < m_nMeshes; i++) m_ppMeshes[i] = NULL;
	}
}

CBulletObject::~CBulletObject()
{
	if (m_ppMeshes)
	{
		for (int i = 0; i < m_nMeshes; i++)
		{
			if (m_ppMeshes[i]) m_ppMeshes[i]->Release();
			m_ppMeshes[i] = NULL;
		}
		delete[] m_ppMeshes;
		m_ppMeshes = NULL;
	}

	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CBulletObject::Move(XMFLOAT3& vDirection, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);
}

void CBulletObject::Animate(float fElapsedTime, XMFLOAT4X4* pxmf4x4Parent)
{
	CGameObject::Animate(fElapsedTime);
	if (!m_bActive) return;

	// 방향 * 속도 * 시간
	XMFLOAT3 pos = GetPosition();
	pos.x += m_xmf3Direction.x * m_fSpeed * fElapsedTime;
	pos.y += m_xmf3Direction.y * m_fSpeed * fElapsedTime;
	pos.z += m_xmf3Direction.z * m_fSpeed * fElapsedTime;
	
	SetPosition(pos);

	if (pos.z > 5000.0f || pos.z < -5000.0f) {
		m_bActive = false;
		SetPosition(0.0f, -10000.0f, 0.0f);
	}
}

void CBulletObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CGameObject::Render(pd3dCommandList, pCamera);
}

//----------------------폭발--


CExplosionCubeObject2::CExplosionCubeObject2()
{
	m_xmf4x4World = Matrix4x4::Identity();
}

CExplosionCubeObject2::~CExplosionCubeObject2()
{
	for (auto frag : m_vFragments)
		delete frag;
	m_vFragments.clear();
}

void CExplosionCubeObject2::CreateFragments(int nCount, ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	XMFLOAT3 center = GetPosition();

	for (int i = 0; i < nCount; ++i)
	{
		CExplosionCubeObject* p = new CExplosionCubeObject(1);

		CCubeMeshDiffused* pMesh = new CCubeMeshDiffused(
			pd3dDevice, pd3dCommandList,
			5.0f, 5.0f, 5.0f,
			XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f)
		);
		p->SetMesh(0, pMesh);

		p->SetPosition(center);
		p->CreateShaderVariables(pd3dDevice, pd3dCommandList);

		XMFLOAT3 dir = {
			((rand() % 2001) - 1000) / 1000.0f,
			((rand() % 2001) - 1000) / 1000.0f,
			((rand() % 2001) - 1000) / 1000.0f
		};
		XMVECTOR v = XMVector3Normalize(XMLoadFloat3(&dir));
		XMStoreFloat3(&dir, v);

		p->SetMovingDirection(dir);
		p->SetMovingSpeed(150.0f);
		p->SetRotationAxis({ dir.z, dir.y, dir.x });
		p->SetRotationSpeed((rand() % 180) + 90.0f);
		p->SetLifetime(3.0f);
		p->StartExplosion();

		m_vFragments.push_back(p);
	}

	m_fLivedTime = 0.0f;
	m_fLifetime = 3.0f;
}

void CExplosionCubeObject2::Animate(float fTimeElapsed)
{
	if (!m_bActive) return;

	for (auto frag : m_vFragments)
	{
		if (frag->IsExploding())
			frag->Animate(fTimeElapsed);
	}
}

void CExplosionCubeObject2::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	if (!m_bActive) return;

	for (auto frag : m_vFragments)
	{
		if (frag->IsExploding())
			frag->Render(pd3dCommandList, pCamera);
	}
}

void CExplosionCubeObject2::SetPosition(XMFLOAT3 xmf3Position)
{
	m_xmf4x4World._41 = xmf3Position.x;
	m_xmf4x4World._42 = xmf3Position.y;
	m_xmf4x4World._43 = xmf3Position.z;

	// 조각들 위치 갱신
	for (auto frag : m_vFragments)
	{
		frag->SetPosition(xmf3Position);
	}
}