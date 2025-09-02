#include "Scene.h"
#include "Camera.h"

CScene::CScene()
{

}

ID3D12RootSignature* CScene::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
{
	ID3D12RootSignature* pd3dGraphicsRootSignature = NULL;

	//루트 파라미터를 설정한다.
	D3D12_ROOT_PARAMETER pd3dRootParameters[2];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[0].Constants.Num32BitValues = 16;
	pd3dRootParameters[0].Constants.ShaderRegister = 0;
	pd3dRootParameters[0].Constants.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 1;
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags =
		/* 앱에서 Input Assempler(꼭짓점 버퍼 바인딩 집합을 정의하는 입력 레이아웃 필요)를 선택하고 있습니다. 
		이 플래그를 생략하면 일부 하드웨어에서 하나의 루트 인수 공간이 절약될 수 있습니다. 
		최적화가 미미하지만 Input Assempler가 필요하지 않다면 이 플래그를 생략하십시오. */
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | 
		
		/* 루트 서명에 대한 ** 셰이더 액세스를 거부합니다. */
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

	//루트 시그너쳐를 생성한다. 
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;
	
	ID3DBlob* pd3dSignatureBlob = NULL;
	ID3DBlob* pd3dErrorBlob = NULL;

	::D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		&pd3dSignatureBlob, &pd3dErrorBlob);

	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(),
		pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void**)&pd3dGraphicsRootSignature);

	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CScene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	//그래픽 루트 시그너쳐를 생성한다. 
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);
	
	//지형을 확대할 스케일 벡터이다. x-축과 z-축은 8배, y-축은 2배 확대한다.
	XMFLOAT3 xmf3Scale(8.0f, 2.0f, 8.0f);
	XMFLOAT4 xmf4Color(0.0f, 0.2f, 0.0f, 0.0f);

	//지형을 높이 맵 이미지 파일(HeightMap.raw)을 사용하여 생성한다. 높이 맵의 크기는 가로x세로(257x257)이다. 
#ifdef _WITH_TERRAIN_PARTITION
	/*하나의 격자 메쉬의 크기는 가로x세로(17x17)이다. 
	지형 전체는 가로 방향으로 16개, 세로 방향으로 16의 격자 메쉬를 가진다. 
	지형을 구성하는 격자 메쉬의 개수는 총 256(16x16)개가 된다.*/
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList,
		m_pd3dGraphicsRootSignature, _T("../Assets/Image/Terrain/HeightMap.raw"), 257, 257, 17,
		17, xmf3Scale, xmf4Color);
#else
	//지형을 하나의 격자 메쉬(257x257)로 생성한다. 
	m_pTerrain = new CHeightMapTerrain(pd3dDevice, pd3dCommandList,
		m_pd3dGraphicsRootSignature, _T("./Terrain/HeightMap.raw"), 257, 257, 257,
		257, xmf3Scale, xmf4Color);
#endif

	m_nShaders = 1;
	m_pShaders = new CObjectsShader[m_nShaders];
	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList, m_pTerrain);

	for (int i = 0; i < 30; i++)
	{
		CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(
			pd3dDevice, pd3dCommandList,
			10.0f, 10.0f, 10.0f,
			XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)
		);

		CBulletObject* pBulletObject = new CBulletObject(1);
		pBulletObject->SetMesh(0, pCubeMesh);
		pBulletObject->SetPosition(0.0f, -0.0f, 0.0f);
		pBulletObject->CreateShaderVariables(pd3dDevice, pd3dCommandList);
		pBulletObject->SetActive(false);

		m_vBulletObjects.push_back(pBulletObject);
	}

	// 적 탱크 총알
	for (int i = 0; i < 50; i++)
	{
		CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(
			pd3dDevice, pd3dCommandList,
			10.0f, 10.0f, 10.0f,
			XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)
		);

		CBulletObject* pBulletObject = new CBulletObject(1);
		pBulletObject->SetMesh(0, pCubeMesh);
		pBulletObject->SetPosition(0.0f, -0.0f, 0.0f);
		pBulletObject->CreateShaderVariables(pd3dDevice, pd3dCommandList);
		pBulletObject->SetActive(false);

		m_vEnemyBulletObjects.push_back(pBulletObject);
	}

	for (int i = 0; i < 20; i++) {
		CEnarmyTankPlayer* pTank = new CEnarmyTankPlayer(pd3dDevice, pd3dCommandList,
			GetGraphicsRootSignature(), GetTerrain(), this, 2);
		m_vEnemyTankPlayers.push_back(pTank);
	}

	for (int i = 0; i < 30; ++i)
	{
		CExplosionCubeObject2* pExplosion = new CExplosionCubeObject2();
		pExplosion->SetActive(false);
		pExplosion->CreateFragments(100, pd3dDevice, pd3dCommandList);
		m_vExplosions2.push_back(pExplosion);
	}

	CCubeMeshDiffused* pShieldMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		5.0f, 5.0f, 5.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CGameObject* pShieldObject = new CGameObject(1);
	pShieldObject->SetMesh(0, pShieldMesh);
	pShieldObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_ppShield = new CGameObject*;
	*m_ppShield = pShieldObject;

	// win obj
	CCubeMeshDiffused* pMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		0.1f, 1.0f, 0.1f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CGameObject* p2 = new CGameObject(1);
	p2->SetMesh(0, pMesh);
	p2->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p2);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-5.0f, 2.0f, 0.0f));

	CGameObject* p3 = new CGameObject(1);
	p3->SetMesh(0, pMesh);
	p3->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p3->Rotate(0.0f, 0.0f, 45.0f);
	m_vWinObjects.push_back(p3);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-5.4f, 2.8f, 0.0f));

	CGameObject* p4 = new CGameObject(1);
	p4->SetMesh(0, pMesh);
	p4->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p4->Rotate(0.0f, 0.0f, -45.0f);
	m_vWinObjects.push_back(p4);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-4.8f, 2.8f, 0.0f));

	CGameObject* p5 = new CGameObject(1);
	p5->SetMesh(0, pMesh);
	p5->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p5);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-4.0f, 2.3f, 0.0f));

	CGameObject* p6 = new CGameObject(1);
	p6->SetMesh(0, pMesh);
	p6->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p6->Rotate(0.0f, 0.0f, 90.0f);
	m_vWinObjects.push_back(p6);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-3.6f, 2.8f, 0.0f));

	CGameObject* p7 = new CGameObject(1);
	p7->SetMesh(0, pMesh);
	p7->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p7->Rotate(0.0f, 0.0f, 90.0f);
	m_vWinObjects.push_back(p7);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-3.6f, 1.8f, 0.0f));

	CGameObject* p8 = new CGameObject(1);
	p8->SetMesh(0, pMesh);
	p8->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p8);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-3.2f, 2.3f, 0.0f));

	CGameObject* p9 = new CGameObject(1);
	p9->SetMesh(0, pMesh);
	p9->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p9);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-2.5f, 2.3f, 0.0f));

	CGameObject* p10 = new CGameObject(1);
	p10->SetMesh(0, pMesh);
	p10->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p10);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-1.7f, 2.3f, 0.0f));

	CGameObject* p11 = new CGameObject(1);
	p11->SetMesh(0, pMesh);
	p11->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p11->Rotate(0.0f, 0.0f, 90.0f);
	m_vWinObjects.push_back(p11);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(-2.1f, 1.8f, 0.0f));

	CGameObject* p12 = new CGameObject(1);
	p12->SetMesh(0, pMesh);
	p12->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p12->Rotate(0.0f, 0.0f, 30.0f);
	m_vWinObjects.push_back(p12);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(1.0f, 2.3f, 0.0f));

	CGameObject* p13 = new CGameObject(1);
	p13->SetMesh(0, pMesh);
	p13->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p13->Rotate(0.0f, 0.0f, -30.0f);
	m_vWinObjects.push_back(p13);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(1.5f, 2.3f, 0.0f));

	CGameObject* p14 = new CGameObject(1);
	p14->SetMesh(0, pMesh);
	p14->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p14->Rotate(0.0f, 0.0f, 30.0f);
	m_vWinObjects.push_back(p14);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(2.0f, 2.3f, 0.0f));

	CGameObject* p15 = new CGameObject(1);
	p15->SetMesh(0, pMesh);
	p15->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p15->Rotate(0.0f, 0.0f, -30.0f);
	m_vWinObjects.push_back(p15);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(2.5f, 2.3f, 0.0f));

	CGameObject* p16 = new CGameObject(1);
	p16->SetMesh(0, pMesh);
	p16->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p16);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(3.0f, 2.3f, 0.0f));


	CCubeMeshDiffused* pMeshPoint = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList,
		0.1f, 0.1f, 0.1f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CGameObject* p17 = new CGameObject(1);
	p17->SetMesh(0, pMeshPoint);
	p17->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p17);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(3.0f, 3.0f, 0.0f));

	CGameObject* p18 = new CGameObject(1);
	p18->SetMesh(0, pMesh);
	p18->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p18);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(3.5f, 2.3f, 0.0f));

	CGameObject* p19 = new CGameObject(1);
	p19->SetMesh(0, pMesh);
	p19->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p19);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(4.3f, 2.3f, 0.0f));

	CGameObject* p20 = new CGameObject(1);
	p20->SetMesh(0, pMesh);
	p20->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	p20->Rotate(0.0f, 0.0f, 90.0f);
	m_vWinObjects.push_back(p20);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(3.9f, 2.8f, 0.0f));

	CGameObject* p21 = new CGameObject(1);
	p21->SetMesh(0, pMesh);
	p21->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p21);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(4.8f, 2.5f, 0.0f));

	CGameObject* p22 = new CGameObject(1);
	p22->SetMesh(0, pMeshPoint);
	p22->CreateShaderVariables(pd3dDevice, pd3dCommandList);
	m_vWinObjects.push_back(p22);
	m_vWinObjectLocalOffsets.push_back(XMFLOAT3(4.8f, 1.8f, 0.0f));
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].ReleaseShaderVariables();
		m_pShaders[i].ReleaseObjects();
	}
	if (m_pShaders) delete[] m_pShaders;
	if (m_pTerrain) delete m_pTerrain;

	for (CBulletObject* pBullet : m_vBulletObjects)
	{
		if (pBullet) delete pBullet;
	}
	m_vBulletObjects.clear();

	for (CBulletObject* pEBullet : m_vEnemyBulletObjects) {
		if (pEBullet) delete pEBullet;
	}
	m_vEnemyBulletObjects.clear();

	for(CEnarmyTankPlayer* pTank : m_vEnemyTankPlayers)
	{
		if (pTank) delete pTank;
	}
	m_vEnemyTankPlayers.clear();

	for (CExplosionCubeObject2* exp : m_vExplosions2) {
		if (exp) delete exp;
	}
	m_vExplosions2.clear();

	if (m_ppShield)
	{
		if (*m_ppShield) delete* m_ppShield;
		delete m_ppShield;
		m_ppShield = nullptr;
	}
	
	for (CGameObject* winMesh : m_vWinObjects) {
		if (winMesh) delete winMesh;
	}
	m_vWinObjects.clear();
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
	lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam,
	LPARAM lParam)
{
	return(false);
}

bool CScene::ProcessInput()
{
	return(false);
}
void CScene::AnimateObjects(float fTimeElapsed)
{
	if (m_pPlayer->IsActive())
	{
		if (CheckPlayerObstacleCollision())
		{
			XMFLOAT3 zero = XMFLOAT3(0.0f, 0.0f, 0.0f);
			m_pPlayer->SetVelocity(zero);
		}
	}

	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].AnimateObjects(fTimeElapsed);
	}

	for (CBulletObject* pBullet : m_vBulletObjects)
	{
		if (pBullet && pBullet->IsActive())
			pBullet->Animate(fTimeElapsed);
	}

	for (CBulletObject* pEBullet : m_vEnemyBulletObjects) {
		if (pEBullet && pEBullet->IsActive())
			pEBullet->Animate(fTimeElapsed);
	}

	for (CGameObject* winMesh : m_vWinObjects) {
		if (winMesh)
			winMesh->Animate(fTimeElapsed);
	}

	for (CEnarmyTankPlayer* pTank : m_vEnemyTankPlayers)
	{
		if (pTank && pTank->IsActive())
			pTank->Animate(fTimeElapsed);
	}

	for (CEnarmyTankPlayer* pETank : m_vEnemyTankPlayers)
	{
		if (pETank->IsActive())
		{
			pETank->Update(fTimeElapsed);
		}
	}

	for (CExplosionCubeObject2* pExplosion : m_vExplosions2)
	{
		if (pExplosion && pExplosion->IsActive())
			pExplosion->Animate(fTimeElapsed);
	}

	if (m_ppShield && *m_ppShield && m_pPlayer && m_pPlayer->IsActive())
	{
		XMFLOAT3 playerPos = m_pPlayer->GetPosition();

		XMFLOAT3 shieldPos = XMFLOAT3(playerPos.x, playerPos.y + 15.0f, playerPos.z);

		(*m_ppShield)->SetPosition(shieldPos);
	}

	CheckBulletEnemyCollisions();
	CheckEnemyBulletPlayerCollisions();

	// 리스폰
	if (!m_pPlayer->IsActive())
	{
		if (!m_bPlayerDead)
		{
			m_bPlayerDead = true;
			m_fPlayerRespawnTimer = 0.0f;
		}
		else
		{
			m_fPlayerRespawnTimer += fTimeElapsed;
			if (m_fPlayerRespawnTimer >= 3.0f)
			{
				// 초기 위치로 리셋
				XMFLOAT3 spawnPos = XMFLOAT3(m_pTerrain->GetWidth() * 0.5f,
					m_pTerrain->GetHeight(m_pTerrain->GetWidth() * 0.5f, m_pTerrain->GetLength() * 0.5f) + 100.0f,
					m_pTerrain->GetLength() * 0.5f);
				m_pPlayer->SetPosition(spawnPos);
				m_pPlayer->SetActive(true);
				m_bPlayerDead = false;
			}
		}
	}
	// win
	if (winStatus && m_pPlayer && m_pPlayer->GetCamera())
	{
		CCamera* pCamera = m_pPlayer->GetCamera();
		XMFLOAT3 camPos = pCamera->GetPosition();
		XMFLOAT3 camLook = pCamera->GetLookVector();

		XMFLOAT3 basePos = Vector3::Add(camPos, Vector3::ScalarProduct(camLook, 10.0f, false));

		XMFLOAT3 xAxis = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMFLOAT3 yAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
		XMFLOAT3 zAxis = XMFLOAT3(0.0f, 0.0f, 1.0f);

		for (size_t i = 0; i < m_vWinObjects.size(); ++i)
		{
			CGameObject* pObj = m_vWinObjects[i];
			if (!pObj) continue;

			XMFLOAT3 localOffset = m_vWinObjectLocalOffsets[i];

			XMFLOAT3 rightOffset = Vector3::ScalarProduct(xAxis, localOffset.x, false);
			XMFLOAT3 upOffset = Vector3::ScalarProduct(yAxis, localOffset.y, false);
			XMFLOAT3 lookOffset = Vector3::ScalarProduct(zAxis, localOffset.z, false);

			XMFLOAT3 finalPos = Vector3::Add(basePos, rightOffset);
			finalPos = Vector3::Add(finalPos, upOffset);
			finalPos = Vector3::Add(finalPos, lookOffset);

			XMFLOAT4X4 world = pObj->m_xmf4x4World;

			// 위치만 갱신
			world._41 = finalPos.x;
			world._42 = finalPos.y;
			world._43 = finalPos.z;

			pObj->SetWorldMatrix(world);
		}
	}

	// 모든 적 탱크가 죽었는지 검사해서 winStatus 설정
	if (!winStatus)
	{
		bool bAllDead = true;
		for (CEnarmyTankPlayer* pTank : m_vEnemyTankPlayers)
		{
			if (pTank && pTank->IsActive())
			{
				bAllDead = false;
				break;
			}
		}
		if (bAllDead)
		{
			winStatus = true;
		}
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
	if (m_pTerrain) m_pTerrain->ReleaseUploadBuffers();
	for (CBulletObject* pBullet : m_vBulletObjects)
	{
		if (pBullet) pBullet->ReleaseUploadBuffers();
	}

	for (CBulletObject* pEBullet : m_vEnemyBulletObjects)
	{
		if (pEBullet) pEBullet->ReleaseUploadBuffers();
	}

	for (CGameObject* winMesh : m_vWinObjects) {
		if (winMesh) winMesh->ReleaseUploadBuffers();
	}

	for(CEnarmyTankPlayer* pTank : m_vEnemyTankPlayers)
	{
		if (pTank) pTank->ReleaseUploadBuffers();
	}

	for (CExplosionCubeObject2* exp : m_vExplosions2) {
		if (exp) exp->ReleaseUploadBuffers();
	}

	if (m_ppShield && *m_ppShield)
		(*m_ppShield)->ReleaseUploadBuffers();

}

ID3D12RootSignature* CScene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}

void CScene::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);

	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);

	if (m_pTerrain) 
		m_pTerrain->Render(pd3dCommandList, pCamera);
	

	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].Render(pd3dCommandList, pCamera);
	}

	for (CBulletObject* pBullet : m_vBulletObjects)
	{
		if (pBullet && pBullet->IsActive())
			pBullet->Render(pd3dCommandList, pCamera);
	}

	for (CBulletObject* pEBullet : m_vEnemyBulletObjects)
	{
		if (pEBullet && pEBullet->IsActive())
			pEBullet->Render(pd3dCommandList, pCamera);
	}

	for (CEnarmyTankPlayer* pTank : m_vEnemyTankPlayers)
	{
		if (pTank && pTank->IsActive())
			pTank->Render(pd3dCommandList, pCamera);
	}

	for (CExplosionCubeObject2* pExplosion : m_vExplosions2)
	{
		if (pExplosion && pExplosion->IsActive())
			pExplosion->Render(pd3dCommandList, pCamera);
	}

	if (shield_active) {
		if (m_ppShield && *m_ppShield)
			(*m_ppShield)->Render(pd3dCommandList, pCamera);
	}

	for (CGameObject* winMesh : m_vWinObjects)
	{
		if (winMesh)
			winMesh->Render(pd3dCommandList, pCamera);
	}
}

CGameObject* CScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera
	* pCamera)
{
	if (!pCamera) return(NULL);

	XMFLOAT4X4 xmf4x4View = pCamera->GetViewMatrix();
	XMFLOAT4X4 xmf4x4Projection = pCamera->GetProjectionMatrix();
	D3D12_VIEWPORT d3dViewport = pCamera->GetViewport();
	XMFLOAT3 xmf3PickPosition;

	xmf3PickPosition.x = (((2.0f * xClient) / d3dViewport.Width) - 1) /
		xmf4x4Projection._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / d3dViewport.Height) - 1) /
		xmf4x4Projection._22;
	xmf3PickPosition.z = 1.0f;
	int nIntersected = 0;
	float fHitDistance = FLT_MAX, fNearestHitDistance = FLT_MAX;
	CGameObject* pIntersectedObject = NULL, * pNearestObject = NULL;

	m_pTargetTank = nullptr; // 이전 타겟 초기화

	for (CEnarmyTankPlayer* pTank : m_vEnemyTankPlayers)
	{
		if (pTank && pTank->IsActive())
		{
			float fTankHitDistance = FLT_MAX;
			int result = pTank->PickObjectByRayIntersection(xmf3PickPosition, xmf4x4View, &fTankHitDistance);
			if (result && fTankHitDistance < fNearestHitDistance)
			{
				fNearestHitDistance = fTankHitDistance;
				m_pTargetTank = pTank;
			}
		}
	}

	return(pNearestObject);
}

void CScene::fire(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	XMFLOAT3 xmf3FirePos = pCamera->GetPosition();

	XMFLOAT3 xmf3Start = {
		xmf3FirePos.x + pCamera->GetLookVector().x * 100.0f,
		xmf3FirePos.y + pCamera->GetLookVector().y * 100.0f,
		xmf3FirePos.z + pCamera->GetLookVector().z * 100.0f
	};
	xmf3Start.y += 20.0f; // 고정 Y축 보정

	XMFLOAT3 xmf3Look;

	if (m_pTargetTank && m_pTargetTank->IsActive())
	{
		XMFLOAT3 targetPos = m_pTargetTank->GetPosition();
		xmf3Look = Vector3::Normalize(Vector3::Subtract(targetPos, xmf3Start));
	}
	else
	{
		xmf3Look = pCamera->GetLookVector();
		xmf3Look.y = 0.0f;
		xmf3Look = Vector3::Normalize(xmf3Look);
	}

	for (CBulletObject* pBullet : m_vBulletObjects)
	{
		if (!pBullet->IsActive())
		{
			pBullet->SetPosition(xmf3Start);
			pBullet->m_xmf3Direction = xmf3Look;
			pBullet->m_fSpeed = 800.0f;
			pBullet->SetActive(true);
			break;
		}
	}
}

void CScene::CheckBulletEnemyCollisions()
{
	float bulletRadius = 5.0f; // 총알 반지름
	float tankRadius = 20.0f;  // 탱크 반지름

	for (CBulletObject* pBullet : m_vBulletObjects)
	{
		if (!pBullet->IsActive()) continue;

		XMFLOAT3 bulletPos = pBullet->GetPosition();

		for (CEnarmyTankPlayer* pTank : m_vEnemyTankPlayers)
		{
			if (!pTank->IsActive()) continue;

			XMFLOAT3 tankPos = pTank->GetPosition();

			if (CheckCollision(bulletPos, bulletRadius, tankPos, tankRadius))
			{
				pBullet->SetActive(false);
				pTank->SetActive(false);

				CreateExplosionAt(tankPos);
			}
		}
	}
}

void CScene::CreateExplosionAt(XMFLOAT3 position)
{
	for (CExplosionCubeObject2* pExplosion : m_vExplosions2)
	{
		if (!pExplosion->IsActive())
		{
			pExplosion->SetPosition(position);
			pExplosion->SetActive(true);
			break;
		}
	}
}

bool CheckCollision(const XMFLOAT3& pos1, float radius1, const XMFLOAT3& pos2, float radius2)
{
	float dx = pos1.x - pos2.x;
	float dy = pos1.y - pos2.y;
	float dz = pos1.z - pos2.z;
	float distSq = dx * dx + dy * dy + dz * dz;
	float radiusSum = radius1 + radius2;
	return distSq <= (radiusSum * radiusSum);
}

void CScene::FireEnemyBullet(CEnarmyTankPlayer* pTank)
{
	XMFLOAT3 firePos = pTank->GetPosition();
	XMFLOAT3 dir = pTank->GetLookVector();

	XMFLOAT3 fireStart = {
		firePos.x + dir.x * 50.0f,
		firePos.y + dir.y * 50.0f + 20.0f,
		firePos.z + dir.z * 50.0f
	};

	for (CBulletObject* pBullet : m_vEnemyBulletObjects)
	{
		if (!pBullet->IsActive())
		{
			pBullet->SetPosition(fireStart);
			pBullet->m_xmf3Direction = Vector3::Normalize(dir);
			pBullet->m_fSpeed = 600.0f;
			pBullet->SetActive(true);
			break;
		}
	}
}

void CScene::CheckEnemyBulletPlayerCollisions()
{
	if (!m_pPlayer || !m_pPlayer->IsActive()) return;

	XMFLOAT3 playerPos = m_pPlayer->GetPosition();
	float playerRadius = 20.0f;
	float bulletRadius = 5.0f;

	for (CBulletObject* pBullet : m_vEnemyBulletObjects)
	{
		if (!pBullet->IsActive()) continue;

		XMFLOAT3 bulletPos = pBullet->GetPosition();

		if (CheckCollision(bulletPos, bulletRadius, playerPos, playerRadius))
		{
			pBullet->SetActive(false);

			if (shield_active)
			{
				OutputDebugStringW(L"실드로 방어됨\n");
				shield_active = false;
			}
			else
			{
				OutputDebugStringW(L"플레이어 피격됨\n");
				m_pPlayer->SetActive(false);
				CreateExplosionAt(playerPos);
			}
		}
	}
}

bool CScene::CheckPlayerObstacleCollision()
{
	if (!m_pPlayer || !m_pPlayer->IsActive()) return false;

	XMFLOAT3 playerPos = m_pPlayer->GetPosition();
	const float playerRadius = 22.0f;

	CObjectsShader* pObjectShader = dynamic_cast<CObjectsShader*>(&m_pShaders[0]);
	if (!pObjectShader) return false;

	for (int i = 0; i < pObjectShader->GetObjectCount(); ++i)
	{
		CGameObject* pObj = pObjectShader->GetObject(i);
		if (!pObj) continue;

		XMFLOAT3 objPos = pObj->GetPosition();
		const float objRadius = 12.0f;

		if (CheckCollision(playerPos, playerRadius, objPos, objRadius))
		{
			return true;
		}
	}
	return false;
}
