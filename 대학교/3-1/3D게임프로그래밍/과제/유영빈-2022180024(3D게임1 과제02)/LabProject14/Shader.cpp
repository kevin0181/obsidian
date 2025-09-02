#include "stdafx.h"
#include "Shader.h"
#include "SceneType.h"

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i])
			m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

//래스터라이저 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return(d3dRasterizerDesc);
}

//깊이-스텐실 검사를 위한 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

//블렌딩 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);
}

//입력 조립기에게 정점 버퍼의 구조를 알려주기 위한 구조체를 반환한다. 
D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;

	return(d3dInputLayoutDesc);
}

//정점 셰이더 바이트 코드를 생성(컴파일)한다. 
D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

//픽셀 셰이더 바이트 코드를 생성(컴파일)한다. 
D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

//셰이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환한다. 
D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(const WCHAR *pszFileName, LPCSTR pszShaderName, 
	LPCSTR pszShaderProfile, ID3DBlob** ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile,
		nCompileFlags, 0, ppd3dShaderBlob, NULL);
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	return(d3dShaderByteCode);
}

//그래픽스 파이프라인 상태 객체를 생성한다. 
void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	ID3DBlob* pd3dVertexShaderBlob = NULL, * pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) 
		delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{

}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{

}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT4X4
	* pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CShader::ReleaseShaderVariables()
{

}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	//파이프라인에 그래픽스 상태 객체를 설정한다. 
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}

void CShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender(pd3dCommandList);
}




//------------------------------------------------------------------------------------------------
//----------------------------------------CPlayerShader-------------------------------------------
//------------------------------------------------------------------------------------------------

CPlayerShader::CPlayerShader()
{
}

CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;

	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}

void CPlayerShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}



//------------------------------------------------------------------------------------------------
//----------------------------------------CObjectsShader------------------------------------------
//------------------------------------------------------------------------------------------------

CObjectsShader::CObjectsShader()
{

}

CObjectsShader::~CObjectsShader()
{

}

D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;

	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CObjectsShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CObjectsShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, void* pContext)
{
	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;
	float fTerrainWidth = pTerrain->GetWidth(), fTerrainLength = pTerrain->GetLength();

	int nObstacleObjects = 10;
	m_nObjects = nObstacleObjects;
	m_ppObjects = new CGameObject * [m_nObjects];

	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 40.0f, 40.0f, 40.0f);

	for (int i = 0; i < nObstacleObjects; i++)
	{
		float x = static_cast<float>(rand() % static_cast<int>(fTerrainWidth));
		float z = static_cast<float>(rand() % static_cast<int>(fTerrainLength));
		float y = pTerrain->GetHeight(x, z) + 6.0f;

		CRotatingObject* pObstacle = new CRotatingObject(1);
		pObstacle->SetMesh(0, pCubeMesh);
		pObstacle->SetPosition(x, y, z);
		pObstacle->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		pObstacle->SetRotationSpeed(180.0f); // 빠르게 회전

		m_ppObjects[i] = pObstacle;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}


void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}

void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

CGameObject* CObjectsShader::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition,
	XMFLOAT4X4& xmf4x4View, float* pfNearHitDistance)
{
	int nIntersected = 0;
	*pfNearHitDistance = FLT_MAX;
	float fHitDistance = FLT_MAX;
	CGameObject* pSelectedObject = NULL;
	for (int j = 0; j < m_nObjects; j++)
	{
		nIntersected = m_ppObjects[j]->PickObjectByRayIntersection(xmf3PickPosition,
			xmf4x4View, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < *pfNearHitDistance))
		{
			*pfNearHitDistance = fHitDistance;
			pSelectedObject = m_ppObjects[j];
		}
	}
	return(pSelectedObject);
}


//------------------------------------------------------------------------------------------------
//----------------------------------------CTerrainShader------------------------------------------
//------------------------------------------------------------------------------------------------


CTerrainShader::CTerrainShader()
{
}
CTerrainShader::~CTerrainShader()
{
}

D3D12_INPUT_LAYOUT_DESC CTerrainShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CTerrainShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CTerrainShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CTerrainShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}



//------------------------------------------------------------------------------------------------
//----------------------------------------CStartSceneShader------------------------------------------
//------------------------------------------------------------------------------------------------

CStartSceneShader::CStartSceneShader()
{

}

CStartSceneShader::~CStartSceneShader()
{

}

D3D12_INPUT_LAYOUT_DESC CStartSceneShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;

	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CStartSceneShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CStartSceneShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CStartSceneShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CStartSceneShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{

	//구 메쉬를 생성한다.
	CSphereMeshDiffused* pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 70.0f, 20, 20, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	m_nObjects = 61;
	m_ppObjects = new COrbitingObject * [m_nObjects];

	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	COrbitingObject* pStaticObject = new COrbitingObject(1);
	pStaticObject->SetMesh(0, pCubeMesh);
	pStaticObject->SetPosition(-400.0f, 300.0f, 0.0f);
	m_ppObjects[0] = pStaticObject;

	CCubeMeshDiffused* pCubeMesh2 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(0.9f, 0.5f, 0.0f, 1.0f)
	);
	COrbitingObject* pStaticObject2 = new COrbitingObject(1);  
	pStaticObject2->SetMesh(0, pCubeMesh2);
	pStaticObject2->SetPosition(-370.0f, 250.0f, 0.0f);  
	m_ppObjects[1] = pStaticObject2;

	COrbitingObject* pStaticObject3 = new COrbitingObject(1);  
	pStaticObject3->SetMesh(0, pCubeMesh);
	pStaticObject3->SetPosition(-400.0f, 200.0f, 0.0f);  
	m_ppObjects[2] = pStaticObject3;

	COrbitingObject* pStaticObject4 = new COrbitingObject(1);  
	pStaticObject4->SetMesh(0, pCubeMesh2);
	pStaticObject4->SetPosition(-370.0f, 150.0f, 0.0f);  
	m_ppObjects[3] = pStaticObject4;

	COrbitingObject* pStaticObject5 = new COrbitingObject(1);  
	pStaticObject5->SetMesh(0, pCubeMesh);
	pStaticObject5->SetPosition(-400.0f, 100.0f, 0.0f);  
	m_ppObjects[4] = pStaticObject5;

	CCubeMeshDiffused* pCubeMesh3 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 200.0f, 30.0f,
		XMFLOAT4(0.5f, 0.1f, 1.0f, 1.0f)
	);
	COrbitingObject* pStaticObject6 = new COrbitingObject(1);  
	pStaticObject6->SetMesh(0, pCubeMesh3);
	pStaticObject6->SetPosition(-300.0f, 200.0f, 0.0f);  
	m_ppObjects[5] = pStaticObject6;

	pCubeMesh3 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 80.0f, 30.0f,
		XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f)
	);
	COrbitingObject* pStaticObject7 = new COrbitingObject(1);  
	pStaticObject7->SetMesh(0, pCubeMesh3);
	pStaticObject7->SetPosition(-250.0f, 250.0f, 0.0f);  
	pStaticObject7->Rotate(0.0f, 0.0f, 50.0f);
	m_ppObjects[6] = pStaticObject7;

	COrbitingObject* pStaticObject8 = new COrbitingObject(1);  
	pStaticObject8->SetMesh(0, pCubeMesh3);
	pStaticObject8->SetPosition(-230.0f, 200.0f, 0.0f);  
	m_ppObjects[7] = pStaticObject8;

	COrbitingObject* pStaticObject9 = new COrbitingObject(1);  
	pStaticObject9->SetMesh(0, pCubeMesh3);
	pStaticObject9->SetPosition(-250.0f, 140.0f, 0.0f);  
	pStaticObject9->Rotate(0.0f, 0.0f, -50.0f);
	m_ppObjects[8] = pStaticObject9;


	CCubeMeshDiffused* pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.5f, 1.0f, 0.0f, 1.0f)
	);

	COrbitingObject* pStaticObject10 = new COrbitingObject(1);  
	pStaticObject10->SetMesh(0, pCubeMesh4);
	pStaticObject10->SetPosition(-150.0f, 300.0f, 0.0f);  
	m_ppObjects[9] = pStaticObject10;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(0.5f, 1.0f, 0.0f, 1.0f)
	);
	COrbitingObject* pStaticObject11 = new COrbitingObject(1);  
	pStaticObject11->SetMesh(0, pCubeMesh4);
	pStaticObject11->SetPosition(-100.0f, 250.0f, 0.0f);  
	m_ppObjects[10] = pStaticObject11;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		80.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);
	COrbitingObject* pStaticObject12 = new COrbitingObject(1);  
	pStaticObject12->SetMesh(0, pCubeMesh4);
	pStaticObject12->SetPosition(-50.0f, 250.0f, 0.0f);  
	m_ppObjects[11] = pStaticObject12;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.5f, 1.0f)
	);
	COrbitingObject* pStaticObject13 = new COrbitingObject(1);  
	pStaticObject13->SetMesh(0, pCubeMesh4);
	pStaticObject13->SetPosition(0.0f, 250.0f, 0.0f);  
	m_ppObjects[12] = pStaticObject13;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.5f, 1.0f)
	);
	COrbitingObject* p14 = new COrbitingObject(1);  
	p14->SetMesh(0, pCubeMesh4);
	p14->SetPosition(50.0f, 250.0f, 0.0f);  
	m_ppObjects[13] = p14;

	COrbitingObject* p15 = new COrbitingObject(1);
	p15->SetMesh(0, pSphereMesh);
	p15->SetPosition(180.0f, 250.0f, 0.0f);
	m_ppObjects[14] = p15;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.5f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p16 = new COrbitingObject(1);
	p16->SetMesh(0, pCubeMesh4);
	p16->SetPosition(280.0f, 250.0f, 0.0f);
	m_ppObjects[15] = p16;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 100.0f, 100.0f,
		XMFLOAT4(0.0f, 1.0, 1.0f, 1.0f)
	);
	COrbitingObject* p17 = new COrbitingObject(1);
	p17->SetMesh(0, pCubeMesh4);
	p17->SetPosition(200.0f, 120.0f, 0.0f);
	m_ppObjects[16] = p17;

	//-----이름----

	pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 70.0f, 20, 20, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	COrbitingObject* p18 = new COrbitingObject(1);
	p18->SetMesh(0, pSphereMesh);
	p18->SetPosition(-300.0f, 0.0f, 0.0f);
	m_ppObjects[17] = p18;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0, 1.0f, 1.0f)
	);
	COrbitingObject* p19 = new COrbitingObject(1);
	p19->SetMesh(0, pCubeMesh4);
	p19->SetPosition(-300.0f, -100.0f, 0.0f);
	m_ppObjects[18] = p19;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(0.0f, 0.5, 1.0f, 1.0f)
	);
	COrbitingObject* p20 = new COrbitingObject(1);
	p20->SetMesh(0, pCubeMesh4);
	p20->SetPosition(-330.0f, -150.0f, 0.0f);
	m_ppObjects[19] = p20;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(0.0f, 0.5, 1.0f, 1.0f)
	);
	COrbitingObject* p21 = new COrbitingObject(1);
	p21->SetMesh(0, pCubeMesh4);
	p21->SetPosition(-270.0f, -150.0f, 0.0f);
	m_ppObjects[20] = p21;


	pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 70.0f, 20, 20, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	COrbitingObject* p22 = new COrbitingObject(1);
	p22->SetMesh(0, pSphereMesh);
	p22->SetPosition(-150.0f, 0.0f, 0.0f);
	m_ppObjects[21] = p22;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p23 = new COrbitingObject(1);
	p23->SetMesh(0, pCubeMesh4);
	p23->SetPosition(-100.0f, 20.0f, 0.0f);
	m_ppObjects[22] = p23;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p24 = new COrbitingObject(1);
	p24->SetMesh(0, pCubeMesh4);
	p24->SetPosition(-100.0f, -30.0f, 0.0f);
	m_ppObjects[23] = p24;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p25 = new COrbitingObject(1);
	p25->SetMesh(0, pCubeMesh4);
	p25->SetPosition(-50.0f, 0.0f, 0.0f);
	m_ppObjects[24] = p25;

	pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 70.0f, 20, 20, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	COrbitingObject* p26 = new COrbitingObject(1);
	p26->SetMesh(0, pSphereMesh);
	p26->SetPosition(-100.0f, -120.0f, 0.0f);
	m_ppObjects[25] = p26;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 100.0f, 100.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p27 = new COrbitingObject(1);
	p27->SetMesh(0, pCubeMesh4);
	p27->SetPosition(50.0f, 0.0f, 0.0f);
	m_ppObjects[26] = p27;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 40.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p28 = new COrbitingObject(1);
	p28->SetMesh(0, pCubeMesh4);
	p28->SetPosition(15.0f, 70.0f, 0.0f);
	m_ppObjects[27] = p28;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 40.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p29 = new COrbitingObject(1);
	p29->SetMesh(0, pCubeMesh4);
	p29->SetPosition(90.0f, 70.0f, 0.0f);
	m_ppObjects[28] = p29;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		50.0f, 50.0f, 110.0f,
		XMFLOAT4(0.0f, 0.125f, 0.3f, 1.0f)
	);
	COrbitingObject* p30 = new COrbitingObject(1);
	p30->SetMesh(0, pCubeMesh4);
	p30->SetPosition(50.0f, 0.0f, 0.0f);
	m_ppObjects[29] = p30;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p31 = new COrbitingObject(1);
	p31->SetMesh(0, pCubeMesh4);
	p31->SetPosition(150.0f, 0.0f, 0.0f);
	m_ppObjects[30] = p31;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p32 = new COrbitingObject(1);
	p32->SetMesh(0, pCubeMesh4);
	p32->SetPosition(50.0f, -120.0f, 0.0f);
	m_ppObjects[31] = p32;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p33 = new COrbitingObject(1);
	p33->SetMesh(0, pCubeMesh4);
	p33->SetPosition(90.0f, -160.0f, 0.0f);
	m_ppObjects[32] = p33;

	// ---프--
	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p34 = new COrbitingObject(1);
	p34->SetMesh(0, pCubeMesh4);
	p34->SetPosition(400.0f, 300.0f, 0.0f);
	m_ppObjects[33] = p34;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 80.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p35 = new COrbitingObject(1);
	p35->SetMesh(0, pCubeMesh4);
	p35->SetPosition(380.0f, 250.0f, 0.0f);
	m_ppObjects[34] = p35;

	COrbitingObject* p36 = new COrbitingObject(1);
	p36->SetMesh(0, pCubeMesh4);
	p36->SetPosition(420.0f, 250.0f, 0.0f);
	m_ppObjects[35] = p36;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p37 = new COrbitingObject(1);
	p37->SetMesh(0, pCubeMesh4);
	p37->SetPosition(400.0f, 200.0f, 0.0f);
	m_ppObjects[36] = p37;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		200.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p38 = new COrbitingObject(1);
	p38->SetMesh(0, pCubeMesh4);
	p38->SetPosition(400.0f, 150.0f, 0.0f);
	m_ppObjects[37] = p38;

	//로
	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p39 = new COrbitingObject(1);
	p39->SetMesh(0, pCubeMesh4);
	p39->SetPosition(600.0f, 300.0f, 0.0f);
	m_ppObjects[38] = p39;

	COrbitingObject* p40 = new COrbitingObject(1);
	p40->SetMesh(0, pCubeMesh4);
	p40->SetPosition(600.0f, 250.0f, 0.0f);
	m_ppObjects[39] = p40;

	COrbitingObject* p41 = new COrbitingObject(1);
	p41->SetMesh(0, pCubeMesh4);
	p41->SetPosition(600.0f, 200.0f, 0.0f);
	m_ppObjects[40] = p41;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 50.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p42 = new COrbitingObject(1);
	p42->SetMesh(0, pCubeMesh4);
	p42->SetPosition(650.0f, 270.0f, 0.0f);
	m_ppObjects[41] = p42;

	COrbitingObject* p43 = new COrbitingObject(1);
	p43->SetMesh(0, pCubeMesh4);
	p43->SetPosition(550.0f, 230.0f, 0.0f);
	m_ppObjects[42] = p43;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 50.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p44 = new COrbitingObject(1);
	p44->SetMesh(0, pCubeMesh4);
	p44->SetPosition(600.0f, 150.0f, 0.0f);
	m_ppObjects[43] = p44;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p45 = new COrbitingObject(1);
	p45->SetMesh(0, pCubeMesh4);
	p45->SetPosition(600.0f, 120.0f, 0.0f);
	m_ppObjects[44] = p45;


	//그
	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p46 = new COrbitingObject(1);
	p46->SetMesh(0, pCubeMesh4);
	p46->SetPosition(770.0f, 300.0f, 0.0f);
	m_ppObjects[45] = p46;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p47 = new COrbitingObject(1);
	p47->SetMesh(0, pCubeMesh4);
	p47->SetPosition(800.0f, 250.0f, 0.0f);
	m_ppObjects[46] = p47;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p48 = new COrbitingObject(1);
	p48->SetMesh(0, pCubeMesh4);
	p48->SetPosition(770.0f, 150.0f, 0.0f);
	m_ppObjects[47] = p48;

	//래
	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.5, 0.5f, 1.0f, 1.0f)
	);
	COrbitingObject* p49 = new COrbitingObject(1);
	p49->SetMesh(0, pCubeMesh4);
	p49->SetPosition(950.0f, 300.0f, 0.0f);
	m_ppObjects[48] = p49;

	COrbitingObject* p50 = new COrbitingObject(1);
	p50->SetMesh(0, pCubeMesh4);
	p50->SetPosition(950.0f, 250.0f, 0.0f);
	m_ppObjects[49] = p50;

	COrbitingObject* p51 = new COrbitingObject(1);
	p51->SetMesh(0, pCubeMesh4);
	p51->SetPosition(950.0f, 200.0f, 0.0f);
	m_ppObjects[50] = p51;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 50.0f, 30.0f,
		XMFLOAT4(0.5, 0.5f, 1.0f, 1.0f)
	);
	COrbitingObject* p52 = new COrbitingObject(1);
	p52->SetMesh(0, pCubeMesh4);
	p52->SetPosition(1000.0f, 270.0f, 0.0f);
	m_ppObjects[51] = p52;

	COrbitingObject* p53 = new COrbitingObject(1);
	p53->SetMesh(0, pCubeMesh4);
	p53->SetPosition(900.0f, 230.0f, 0.0f);
	m_ppObjects[52] = p53;

	// ㅐ
	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0, 0.5f, 1.0f, 1.0f)
	);
	COrbitingObject* p54 = new COrbitingObject(1);
	p54->SetMesh(0, pCubeMesh4);
	p54->SetPosition(1050.0f, 250.0f, 0.0f);
	m_ppObjects[53] = p54;

	COrbitingObject* p55 = new COrbitingObject(1);
	p55->SetMesh(0, pCubeMesh4);
	p55->SetPosition(1120.0f, 250.0f, 0.0f);
	m_ppObjects[54] = p55;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		50.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0, 0.5f, 1.0f, 1.0f)
	);
	COrbitingObject* p56 = new COrbitingObject(1);
	p56->SetMesh(0, pCubeMesh4);
	p56->SetPosition(1070.0f, 250.0f, 0.0f);
	m_ppObjects[55] = p56;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 100.0f, 100.0f,
		XMFLOAT4(0.0, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p57 = new COrbitingObject(1);
	p57->SetMesh(0, pCubeMesh4);
	p57->SetPosition(1250.0f, 250.0f, 0.0f);
	m_ppObjects[56] = p57;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0, 0.0f, 0.0f, 1.0f)
	);
	COrbitingObject* p58 = new COrbitingObject(1);
	p58->SetMesh(0, pCubeMesh4);
	p58->SetPosition(1380.0f, 250.0f, 0.0f);
	m_ppObjects[57] = p58;

	pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 70.0f, 20, 20, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	COrbitingObject* p59 = new COrbitingObject(1);
	p59->SetMesh(0, pSphereMesh);
	p59->SetPosition(1330.0f, 100.0f, 0.0f);
	m_ppObjects[58] = p59;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 180.0f, 30.0f,
		XMFLOAT4(1.0, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p60 = new COrbitingObject(1);
	p60->SetMesh(0, pCubeMesh4);
	p60->SetPosition(1500.0f, 250.0f, 0.0f);
	m_ppObjects[59] = p60;

	pCubeMesh4 = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 80.0f, 30.0f,
		XMFLOAT4(1.0, 1.0f, 1.0f, 1.0f)
	);
	COrbitingObject* p61 = new COrbitingObject(1);
	p61->SetMesh(0, pCubeMesh4);
	p61->Rotate(0.0f, 0.0f, -40.0f);
	p61->SetPosition(1470.0f, 300.0f, 0.0f);
	m_ppObjects[60] = p61;

	const int nExplosionFragments = 1000;
	m_nExplosionObjects = nExplosionFragments;
	m_ppExplosionObjects = new CExplosionCubeObject * [nExplosionFragments];

	XMFLOAT3 explosionCenter = XMFLOAT3(500.0f, 300.0f, 0.0f);
	float fragmentSize = 10.0f;
	float fragmentSpeed = 100.0f;

	for (int i = 0; i < nExplosionFragments; ++i)
	{
		CExplosionCubeObject* pFragment = new CExplosionCubeObject(1);

		CCubeMeshDiffused* pMesh = new CCubeMeshDiffused(
			pd3dDevice, pd3dCommandList,
			fragmentSize, fragmentSize, fragmentSize,
			XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
		);
		pFragment->SetMesh(0, pMesh);
		pFragment->SetPosition(explosionCenter);

		XMFLOAT3 vDir = XMFLOAT3(
			((rand() % 2001) - 1000) / 1000.0f,
			((rand() % 2001) - 1000) / 1000.0f,
			((rand() % 2001) - 1000) / 1000.0f
		);
		XMVECTOR v = XMVector3Normalize(XMLoadFloat3(&vDir));
		XMStoreFloat3(&vDir, v);

		pFragment->Move(vDir, fragmentSpeed);
		pFragment->SetRotationAxis(XMFLOAT3(vDir.z, vDir.y, vDir.x));
		pFragment->SetRotationSpeed((rand() % 180) + 90.0f);
		pFragment->SetMovingDirection(vDir);
		pFragment->SetMovingSpeed(150.0f);
		pFragment->SetLifetime(3.0f);

		m_ppExplosionObjects[i] = pFragment;

		CreateShaderVariables(pd3dDevice, pd3dCommandList);
	}
}

void CStartSceneShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}

	if (m_ppExplosionObjects)
	{
		for (int i = 0; i < m_nExplosionObjects; ++i)
			delete m_ppExplosionObjects[i];
		delete[] m_ppExplosionObjects;
		m_ppExplosionObjects = nullptr;
	}
}

void CStartSceneShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}

	for (int i = 0; i < m_nExplosionObjects; ++i)
	{
		m_ppExplosionObjects[i]->Animate(fTimeElapsed);
	}
}

void CStartSceneShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CStartSceneShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{

	CShader::Render(pd3dCommandList, pCamera);

	if (rend_s) {
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j])
			{
				m_ppObjects[j]->Render(pd3dCommandList, pCamera);
			}
		}
	}

	for (int i = 0; i < m_nExplosionObjects; ++i)
	{
		m_ppExplosionObjects[i]->Render(pd3dCommandList, pCamera);
	}
}

CGameObject* CStartSceneShader::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition,
	XMFLOAT4X4& xmf4x4View, float* pfNearHitDistance)
{
	int nIntersected = 0;
	*pfNearHitDistance = FLT_MAX;
	float fHitDistance = FLT_MAX;
	CGameObject* pSelectedObject = NULL;
	for (int j = 0; j < m_nObjects; j++)
	{
		nIntersected = m_ppObjects[j]->PickObjectByRayIntersection(xmf3PickPosition,
			xmf4x4View, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < *pfNearHitDistance))
		{
			rend_s = false;
			for (int i = 0; i < m_nExplosionObjects; ++i)
			{
				m_ppExplosionObjects[i]->StartExplosion();
			}
		}
	}
	return(pSelectedObject);
}


//------------------------------------------------------------------------------------------------
//----------------------------------------CMenuSceneShader------------------------------------------
//------------------------------------------------------------------------------------------------

CMenuSceneShader::CMenuSceneShader()
{

}

CMenuSceneShader::~CMenuSceneShader()
{

}

D3D12_INPUT_LAYOUT_DESC CMenuSceneShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;

	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CMenuSceneShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CMenuSceneShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CMenuSceneShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CMenuSceneShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	m_nObjects = 74;
	m_ppObjects = new CMenuSceneObject * [m_nObjects];

	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p1 = new CMenuSceneObject(1);
	p1->objectName = "Tutorial";
	p1->SetMesh(0, pCubeMesh);
	p1->SetPosition(-400.0f, 300.0f, 0.0f);
	m_ppObjects[0] = p1;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p2 = new CMenuSceneObject(1);
	p2->objectName = "Tutorial";
	p2->SetMesh(0, pCubeMesh);
	p2->SetPosition(-400.0f, 240.0f, 0.0f);
	m_ppObjects[1] = p2;

	CMenuSceneObject* p3 = new CMenuSceneObject(1);
	p3->objectName = "Tutorial";
	p3->SetMesh(0, pCubeMesh);
	p3->SetPosition(-300.0f, 240.0f, 0.0f);
	m_ppObjects[2] = p3;

	CMenuSceneObject* p4 = new CMenuSceneObject(1);
	p4->objectName = "Tutorial";
	p4->SetMesh(0, pCubeMesh);
	p4->SetPosition(-220.0f, 240.0f, 0.0f);
	m_ppObjects[3] = p4;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p5 = new CMenuSceneObject(1);
	p5->objectName = "Tutorial";
	p5->SetMesh(0, pCubeMesh);
	p5->SetPosition(-260.0f, 180.0f, 0.0f);
	m_ppObjects[4] = p5;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p6 = new CMenuSceneObject(1);
	p6->objectName = "Tutorial";
	p6->SetMesh(0, pCubeMesh);
	p6->SetPosition(-120.0f, 300.0f, 0.0f);
	m_ppObjects[5] = p6;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p7 = new CMenuSceneObject(1);
	p7->objectName = "Tutorial";
	p7->SetMesh(0, pCubeMesh);
	p7->SetPosition(-120.0f, 240.0f, 0.0f);
	m_ppObjects[6] = p7;

	CSphereMeshDiffused* pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 70.0f, 20, 20, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	CMenuSceneObject* p8 = new CMenuSceneObject(1);
	p8->objectName = "Tutorial";
	p8->SetMesh(0, pSphereMesh);
	p8->SetPosition(10.0f, 240.0f, 0.0f);
	m_ppObjects[7] = p8;

	CMenuSceneObject* p9 = new CMenuSceneObject(1);
	p9->objectName = "Tutorial";
	p9->SetMesh(0, pCubeMesh);
	p9->SetPosition(120.0f, 240.0f, 0.0f);
	m_ppObjects[8] = p9;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 90.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p10 = new CMenuSceneObject(1);
	p10->objectName = "Tutorial";
	p10->SetMesh(0, pCubeMesh);
	p10->SetPosition(155.0f, 270.0f, 0.0f);
	p10->Rotate(0.0f, 0.0f, -70.0f);
	m_ppObjects[9] = p10;

	pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 20.0f, 20, 20, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	CMenuSceneObject* p11 = new CMenuSceneObject(1);
	p11->objectName = "Tutorial";
	p11->SetMesh(0, pSphereMesh);
	p11->SetPosition(250.0f, 300.0f, 0.0f);
	m_ppObjects[10] = p11;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p12 = new CMenuSceneObject(1);
	p12->objectName = "Tutorial";
	p12->SetMesh(0, pCubeMesh);
	p12->SetPosition(250.0f, 215.0f, 0.0f);
	m_ppObjects[11] = p12;

	pSphereMesh = new CSphereMeshDiffused(pd3dDevice, pd3dCommandList, 70.0f, 20, 20, XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	CMenuSceneObject* p13 = new CMenuSceneObject(1);
	p13->objectName = "Tutorial";
	p13->SetMesh(0, pSphereMesh);
	p13->SetPosition(380.0f, 240.0f, 0.0f);
	m_ppObjects[12] = p13;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 100.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p14 = new CMenuSceneObject(1);
	p14->objectName = "Tutorial";
	p14->SetMesh(0, pCubeMesh);
	p14->SetPosition(420.0f, 215.0f, 0.0f);
	p14->Rotate(0.0f, 0.0f, 70.0f);
	m_ppObjects[13] = p14;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p15 = new CMenuSceneObject(1);
	p15->objectName = "Tutorial";
	p15->SetMesh(0, pCubeMesh);
	p15->SetPosition(520.0f, 240.0f, 0.0f);
	m_ppObjects[14] = p15;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);


	// L
	CMenuSceneObject* p16 = new CMenuSceneObject(1);
	p16->objectName = "Level-1";
	p16->SetMesh(0, pCubeMesh);
	p16->SetPosition(720.0f, 240.0f, 0.0f);
	m_ppObjects[15] = p16;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p17 = new CMenuSceneObject(1);
	p17->objectName = "Level-1";
	p17->SetMesh(0, pCubeMesh);
	p17->SetPosition(780.0f, 180.0f, 0.0f);
	m_ppObjects[16] = p17;

	// e

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p18 = new CMenuSceneObject(1);
	p18->objectName = "Level-1";
	p18->SetMesh(0, pCubeMesh);
	p18->SetPosition(950.0f, 300.0f, 0.0f);
	m_ppObjects[17] = p18;

	CMenuSceneObject* p19 = new CMenuSceneObject(1);
	p19->objectName = "Level-1";
	p19->SetMesh(0, pCubeMesh);
	p19->SetPosition(950.0f, 240.0f, 0.0f);
	m_ppObjects[18] = p19;

	CMenuSceneObject* p20 = new CMenuSceneObject(1);
	p20->objectName = "Level-1";
	p20->SetMesh(0, pCubeMesh);
	p20->SetPosition(950.0f, 180.0f, 0.0f);
	m_ppObjects[19] = p20;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p21 = new CMenuSceneObject(1);
	p21->objectName = "Level-1";
	p21->SetMesh(0, pCubeMesh);
	p21->SetPosition(890.0f, 240.0f, 0.0f);
	m_ppObjects[20] = p21;

	//v
	CMenuSceneObject* p22 = new CMenuSceneObject(1);
	p22->objectName = "Level-1";
	p22->SetMesh(0, pCubeMesh);
	p22->SetPosition(1100.0f, 240.0f, 0.0f);
	p22->Rotate(0.0f, 0.0f, 20.0f);
	m_ppObjects[21] = p22;

	CMenuSceneObject* p23 = new CMenuSceneObject(1);
	p23->objectName = "Level-1";
	p23->SetMesh(0, pCubeMesh);
	p23->SetPosition(1150.0f, 240.0f, 0.0f);
	p23->Rotate(0.0f, 0.0f, -20.0f);
	m_ppObjects[22] = p23;

	// e

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p24 = new CMenuSceneObject(1);
	p24->objectName = "Level-1";
	p24->SetMesh(0, pCubeMesh);
	p24->SetPosition(1290.0f, 300.0f, 0.0f);
	m_ppObjects[23] = p24;

	CMenuSceneObject* p25 = new CMenuSceneObject(1);
	p25->objectName = "Level-1";
	p25->SetMesh(0, pCubeMesh);
	p25->SetPosition(1290.0f, 240.0f, 0.0f);
	m_ppObjects[24] = p25;

	CMenuSceneObject* p26 = new CMenuSceneObject(1);
	p26->objectName = "Level-1";
	p26->SetMesh(0, pCubeMesh);
	p26->SetPosition(1290.0f, 180.0f, 0.0f);
	m_ppObjects[25] = p26;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p27 = new CMenuSceneObject(1);
	p27->objectName = "Level-1";
	p27->SetMesh(0, pCubeMesh);
	p27->SetPosition(1230.0f, 240.0f, 0.0f);
	m_ppObjects[26] = p27;


	// L
	CMenuSceneObject* p28 = new CMenuSceneObject(1);
	p28->objectName = "Level-1";
	p28->SetMesh(0, pCubeMesh);
	p28->SetPosition(1430.0f, 240.0f, 0.0f);
	m_ppObjects[27] = p28;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p29 = new CMenuSceneObject(1);
	p29->objectName = "Level-1";
	p29->SetMesh(0, pCubeMesh);
	p29->SetPosition(1490.0f, 180.0f, 0.0f);
	m_ppObjects[28] = p29;

	// -
	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p30 = new CMenuSceneObject(1);
	p30->objectName = "Level-1";
	p30->SetMesh(0, pCubeMesh);
	p30->SetPosition(1600.0f, 240.0f, 0.0f);
	m_ppObjects[29] = p30;

	// 1
	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p31 = new CMenuSceneObject(1);
	p31->objectName = "Level-1";
	p31->SetMesh(0, pCubeMesh);
	p31->SetPosition(1700.0f, 240.0f, 0.0f);
	m_ppObjects[30] = p31;

	// L
	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p32 = new CMenuSceneObject(1);
	p32->objectName = "Level-2";
	p32->SetMesh(0, pCubeMesh);
	p32->SetPosition(1920.0f, 240.0f, 0.0f);
	m_ppObjects[31] = p32;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p33 = new CMenuSceneObject(1);
	p33->objectName = "Level-2";
	p33->SetMesh(0, pCubeMesh);
	p33->SetPosition(1980.0f, 180.0f, 0.0f);
	m_ppObjects[32] = p33;

	// e

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p34 = new CMenuSceneObject(1);
	p34->objectName = "Level-2";
	p34->SetMesh(0, pCubeMesh);
	p34->SetPosition(2150.0f, 300.0f, 0.0f);
	m_ppObjects[33] = p34;

	CMenuSceneObject* p35 = new CMenuSceneObject(1);
	p35->objectName = "Level-2";
	p35->SetMesh(0, pCubeMesh);
	p35->SetPosition(2150.0f, 240.0f, 0.0f);
	m_ppObjects[34] = p35;

	CMenuSceneObject* p36 = new CMenuSceneObject(1);
	p36->objectName = "Level-2";
	p36->SetMesh(0, pCubeMesh);
	p36->SetPosition(2150.0f, 180.0f, 0.0f);
	m_ppObjects[35] = p36;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p37 = new CMenuSceneObject(1);
	p37->objectName = "Level-2";
	p37->SetMesh(0, pCubeMesh);
	p37->SetPosition(2090.0f, 240.0f, 0.0f);
	m_ppObjects[36] = p37;

	//v
	CMenuSceneObject* p38 = new CMenuSceneObject(1);
	p38->objectName = "Level-2";
	p38->SetMesh(0, pCubeMesh);
	p38->SetPosition(2300.0f, 240.0f, 0.0f);
	p38->Rotate(0.0f, 0.0f, 20.0f);
	m_ppObjects[37] = p38;

	CMenuSceneObject* p39 = new CMenuSceneObject(1);
	p39->objectName = "Level-2";
	p39->SetMesh(0, pCubeMesh);
	p39->SetPosition(2350.0f, 240.0f, 0.0f);
	p39->Rotate(0.0f, 0.0f, -20.0f);
	m_ppObjects[38] = p39;

	// e

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p40 = new CMenuSceneObject(1);
	p40->objectName = "Level-2";
	p40->SetMesh(0, pCubeMesh);
	p40->SetPosition(2490.0f, 300.0f, 0.0f);
	m_ppObjects[39] = p40;

	CMenuSceneObject* p41 = new CMenuSceneObject(1);
	p41->objectName = "Level-2";
	p41->SetMesh(0, pCubeMesh);
	p41->SetPosition(2490.0f, 240.0f, 0.0f);
	m_ppObjects[40] = p41;

	CMenuSceneObject* p42 = new CMenuSceneObject(1);
	p42->objectName = "Level-2";
	p42->SetMesh(0, pCubeMesh);
	p42->SetPosition(2490.0f, 180.0f, 0.0f);
	m_ppObjects[41] = p42;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p43 = new CMenuSceneObject(1);
	p43->objectName = "Level-2";
	p43->SetMesh(0, pCubeMesh);
	p43->SetPosition(2430.0f, 240.0f, 0.0f);
	m_ppObjects[42] = p43;


	// L
	CMenuSceneObject* p44 = new CMenuSceneObject(1);
	p44->objectName = "Level-2";
	p44->SetMesh(0, pCubeMesh);
	p44->SetPosition(2630.0f, 240.0f, 0.0f);
	m_ppObjects[43] = p44;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p45 = new CMenuSceneObject(1);
	p45->objectName = "Level-2";
	p45->SetMesh(0, pCubeMesh);
	p45->SetPosition(2690.0f, 180.0f, 0.0f);
	m_ppObjects[44] = p45;

	// -
	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p46 = new CMenuSceneObject(1);
	p46->objectName = "Level-2";
	p46->SetMesh(0, pCubeMesh);
	p46->SetPosition(2800.0f, 240.0f, 0.0f);
	m_ppObjects[45] = p46;

	//2
	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p47 = new CMenuSceneObject(1);
	p47->objectName = "Level-2";
	p47->SetMesh(0, pCubeMesh);
	p47->SetPosition(2950.0f, 300.0f, 0.0f);
	p47->Rotate(0.0f, 0.0f, 20.0f);
	m_ppObjects[46] = p47;

	CMenuSceneObject* p48 = new CMenuSceneObject(1);
	p48->objectName = "Level-2";
	p48->SetMesh(0, pCubeMesh);
	p48->SetPosition(3030.0f, 300.0f, 0.0f);
	p48->Rotate(0.0f, 0.0f, -20.0f);
	m_ppObjects[47] = p48;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 180.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);
	CMenuSceneObject* p49 = new CMenuSceneObject(1);
	p49->objectName = "Level-2";
	p49->SetMesh(0, pCubeMesh);
	p49->SetPosition(3010.0f, 225.0f, 0.0f);
	p49->Rotate(0.0f, 0.0f, -45.0f);
	m_ppObjects[48] = p49;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)
	);
	CMenuSceneObject* p50 = new CMenuSceneObject(1);
	p50->objectName = "Level-2";
	p50->SetMesh(0, pCubeMesh);
	p50->SetPosition(3000.0f, 180.0f, 0.0f);
	m_ppObjects[49] = p50;

	//s
	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);
	CMenuSceneObject* p51 = new CMenuSceneObject(1);
	p51->objectName = "Start";
	p51->SetMesh(0, pCubeMesh);
	p51->SetPosition(3300.0f, 300.0f, 0.0f);
	m_ppObjects[50] = p51;

	CMenuSceneObject* p52 = new CMenuSceneObject(1);
	p52->objectName = "Start";
	p52->SetMesh(0, pCubeMesh);
	p52->SetPosition(3300.0f, 240.0f, 0.0f);
	m_ppObjects[51] = p52;

	CMenuSceneObject* p53 = new CMenuSceneObject(1);
	p53->objectName = "Start";
	p53->SetMesh(0, pCubeMesh);
	p53->SetPosition(3300.0f, 180.0f, 0.0f);
	m_ppObjects[52] = p53;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 60.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p54 = new CMenuSceneObject(1);
	p54->objectName = "Start";
	p54->SetMesh(0, pCubeMesh);
	p54->SetPosition(3240.0f, 260.0f, 0.0f);
	m_ppObjects[53] = p54;

	CMenuSceneObject* p55 = new CMenuSceneObject(1);
	p55->objectName = "Start";
	p55->SetMesh(0, pCubeMesh);
	p55->SetPosition(3360.0f, 220.0f, 0.0f);
	m_ppObjects[54] = p55;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p56 = new CMenuSceneObject(1);
	p56->objectName = "Start";
	p56->SetMesh(0, pCubeMesh);
	p56->SetPosition(3480.0f, 300.0f, 0.0f);
	m_ppObjects[55] = p56;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p57 = new CMenuSceneObject(1);
	p57->objectName = "Start";
	p57->SetMesh(0, pCubeMesh);
	p57->SetPosition(3480.0f, 240.0f, 0.0f);
	m_ppObjects[56] = p57;

	//A
	CMenuSceneObject* p58 = new CMenuSceneObject(1);
	p58->objectName = "Start";
	p58->SetMesh(0, pCubeMesh);
	p58->SetPosition(3620.0f, 240.0f, 0.0f);
	p58->Rotate(0.0f, 0.0f, -20.0f);
	m_ppObjects[57] = p58;

	CMenuSceneObject* p59 = new CMenuSceneObject(1);
	p59->objectName = "Start";
	p59->SetMesh(0, pCubeMesh);
	p59->SetPosition(3670.0f, 240.0f, 0.0f);
	p59->Rotate(0.0f, 0.0f, 20.0f);
	m_ppObjects[58] = p59;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		50.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p60 = new CMenuSceneObject(1);
	p60->objectName = "Start";
	p60->SetMesh(0, pCubeMesh);
	p60->SetPosition(3650.0f, 220.0f, 0.0f);
	m_ppObjects[59] = p60;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p61 = new CMenuSceneObject(1);
	p61->objectName = "Start";
	p61->SetMesh(0, pCubeMesh);
	p61->SetPosition(3780.0f, 240.0f, 0.0f);
	m_ppObjects[60] = p61;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 80.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p62 = new CMenuSceneObject(1);
	p62->objectName = "Start";
	p62->SetMesh(0, pCubeMesh);
	p62->SetPosition(3810.0f, 280.0f, 0.0f);
	p62->Rotate(0.0f, 0.0f, -70.0f);
	m_ppObjects[61] = p62;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p63 = new CMenuSceneObject(1);
	p63->objectName = "Start";
	p63->SetMesh(0, pCubeMesh);
	p63->SetPosition(3970.0f, 300.0f, 0.0f);
	m_ppObjects[62] = p63;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
	);

	CMenuSceneObject* p64 = new CMenuSceneObject(1);
	p64->objectName = "Start";
	p64->SetMesh(0, pCubeMesh);
	p64->SetPosition(3970.0f, 240.0f, 0.0f);
	m_ppObjects[63] = p64;
	
	//E
	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		150.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p65 = new CMenuSceneObject(1);
	p65->objectName = "End";
	p65->SetMesh(0, pCubeMesh);
	p65->SetPosition(4200.0f, 300.0f, 0.0f);
	m_ppObjects[64] = p65;

	CMenuSceneObject* p66 = new CMenuSceneObject(1);
	p66->objectName = "End";
	p66->SetMesh(0, pCubeMesh);
	p66->SetPosition(4200.0f, 240.0f, 0.0f);
	m_ppObjects[65] = p66;

	CMenuSceneObject* p67 = new CMenuSceneObject(1);
	p67->objectName = "End";
	p67->SetMesh(0, pCubeMesh);
	p67->SetPosition(4200.0f, 180.0f, 0.0f);
	m_ppObjects[66] = p67;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p68 = new CMenuSceneObject(1);
	p68->objectName = "End";
	p68->SetMesh(0, pCubeMesh);
	p68->SetPosition(4140.0f, 240.0f, 0.0f);
	m_ppObjects[67] = p68;

	CMenuSceneObject* p69 = new CMenuSceneObject(1);
	p69->objectName = "End";
	p69->SetMesh(0, pCubeMesh);
	p69->SetPosition(4340.0f, 240.0f, 0.0f);
	m_ppObjects[68] = p69;

	CMenuSceneObject* p70 = new CMenuSceneObject(1);
	p70->objectName = "End";
	p70->SetMesh(0, pCubeMesh);
	p70->SetPosition(4460.0f, 240.0f, 0.0f);
	m_ppObjects[69] = p70;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p71 = new CMenuSceneObject(1);
	p71->objectName = "End";
	p71->SetMesh(0, pCubeMesh);
	p71->SetPosition(4400.0f, 300.0f, 0.0f);
	m_ppObjects[70] = p71;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		30.0f, 150.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p72 = new CMenuSceneObject(1);
	p72->objectName = "End";
	p72->SetMesh(0, pCubeMesh);
	p72->SetPosition(4550.0f, 240.0f, 0.0f);
	m_ppObjects[71] = p72;

	pCubeMesh = new CCubeMeshDiffused(
		pd3dDevice, pd3dCommandList,
		100.0f, 30.0f, 30.0f,
		XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)
	);

	CMenuSceneObject* p73 = new CMenuSceneObject(1);
	p73->objectName = "End";
	p73->SetMesh(0, pCubeMesh);
	p73->SetPosition(4600.0f, 270.0f, 0.0f);
	p73->Rotate(0.0f, 0.0f, -40.0f);
	m_ppObjects[72] = p73;

	CMenuSceneObject* p74 = new CMenuSceneObject(1);
	p74->objectName = "End";
	p74->SetMesh(0, pCubeMesh);
	p74->SetPosition(4600.0f, 210.0f, 0.0f);
	p74->Rotate(0.0f, 0.0f, 40.0f);
	m_ppObjects[73] = p74;

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
	
}

void CMenuSceneShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}

void CMenuSceneShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}

void CMenuSceneShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CMenuSceneShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{

	CShader::Render(pd3dCommandList, pCamera);

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

CGameObject* CMenuSceneShader::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition,
	XMFLOAT4X4& xmf4x4View, float* pfNearHitDistance)
{
	int nIntersected = 0;
	*pfNearHitDistance = FLT_MAX;
	float fHitDistance = FLT_MAX;
	CGameObject* pSelectedObject = NULL;
	for (int j = 0; j < m_nObjects; j++)
	{
		nIntersected = m_ppObjects[j]->PickObjectByRayIntersection(xmf3PickPosition,
			xmf4x4View, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < *pfNearHitDistance))
		{
			if(m_ppObjects[j]->objectName == "Start") {
				m_CurrentScene = SceneType::Level_1;
			} else if(m_ppObjects[j]->objectName == "End") {
				exit(0);
			}
			else if (m_ppObjects[j]->objectName == "Level-1") {
				m_CurrentScene = SceneType::Level_1;
			}
			else if (m_ppObjects[j]->objectName == "Level-2") {
				m_CurrentScene = SceneType::Level_2;
			}
			else if (m_ppObjects[j]->objectName == "Tutorial") {
				m_CurrentScene = SceneType::NN;
			}

		}
	}
	return(pSelectedObject);
}



//------------------------------------------------------------------------------------------------
//----------------------------------------CLevel1SceneShader------------------------------------------
//------------------------------------------------------------------------------------------------

CLevel1SceneShader::CLevel1SceneShader()
{

}

CLevel1SceneShader::~CLevel1SceneShader()
{

}

D3D12_INPUT_LAYOUT_DESC CLevel1SceneShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;

	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CLevel1SceneShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CLevel1SceneShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CLevel1SceneShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CLevel1SceneShader::CreateRailPath()
{
	m_vRailPath.clear();
	m_vRailAngles.clear();

	XMFLOAT3 position = XMFLOAT3(0.0f, 0.0f, -85.0f);
	float angle = 0.0f; // 진행 방향
	float angleStep = XM_PI / 90.0f;
	float segmentLength = 10.0f;

	int straightCount = 100;
	int leftTurnCount = 80;
	int rightTurnCount = 80;
	int ascendCount = 130;
	int descendCount = 130;

	// 1. 직선 구간
	for (int i = 0; i < straightCount; ++i)
	{
		float dx = cosf(angle) * segmentLength;
		float dz = sinf(angle) * segmentLength;
		XMFLOAT3 dir(dx, 0.0f, dz);

		position = Vector3::Add(position, dir);
		m_vRailPath.push_back(position);
		m_vRailAngles.push_back(angle);
	}

	// 2. 좌회전 구간
	for (int i = 0; i < leftTurnCount; ++i)
	{
		angle += angleStep;
		float dx = cosf(angle) * segmentLength;
		float dz = sinf(angle) * segmentLength;
		XMFLOAT3 dir(dx, 0.0f, dz);

		position = Vector3::Add(position, dir);
		m_vRailPath.push_back(position);
		m_vRailAngles.push_back(angle);
	}

	// 3. 우회전 구간
	for (int i = 0; i < rightTurnCount; ++i)
	{
		angle -= angleStep;
		float dx = cosf(angle) * segmentLength;
		float dz = sinf(angle) * segmentLength;
		XMFLOAT3 dir(dx, 0.0f, dz);

		position = Vector3::Add(position, dir);
		m_vRailPath.push_back(position);
		m_vRailAngles.push_back(angle);
	}

	// 4. 오르막 구간 (y축으로 올라감)
	for (int i = 0; i < ascendCount; ++i)
	{
		float dx = cosf(angle) * segmentLength;
		float dz = sinf(angle) * segmentLength;
		float dy = 3.5f;

		XMFLOAT3 dir(dx, dy, dz);
		position = Vector3::Add(position, dir);
		m_vRailPath.push_back(position);
		m_vRailAngles.push_back(angle);
	}

	// 5. 내리막 구간 (y축으로 내려감)
	for (int i = 0; i < descendCount; ++i)
	{
		float dx = cosf(angle) * segmentLength;
		float dz = sinf(angle) * segmentLength;
		float dy = -3.5f;

		XMFLOAT3 dir(dx, dy, dz);
		position = Vector3::Add(position, dir);
		m_vRailPath.push_back(position);
		m_vRailAngles.push_back(angle);
	}

	for (int i = 0; i < straightCount; ++i)
	{
		float dx = cosf(angle) * segmentLength;
		float dz = sinf(angle) * segmentLength;
		XMFLOAT3 dir(dx, 0.0f, dz);

		position = Vector3::Add(position, dir);
		m_vRailPath.push_back(position);
		m_vRailAngles.push_back(angle);
	}
}


void CLevel1SceneShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	CreateRailPath();

	m_nObjects = static_cast<UINT>(m_vRailPath.size());
	m_ppObjects = new CGameObject * [m_nObjects];

	int straightCount = 100;
	int leftTurnCount = 80;
	int rightTurnCount = 80;
	int ascendCount = 130;
	int descendCount = 130;

	for (int i = 0; i < m_nObjects; ++i)
	{
		CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(
			pd3dDevice, pd3dCommandList,
			10.0f, 1.0f, 10.0f,
			XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)
		);

		CGameObject* pRail = new CGameObject(1);
		pRail->SetMesh(0, pCubeMesh);

		float yaw = m_vRailAngles[i];
		XMMATRIX mtxRotateY = XMMatrixRotationY(yaw);
		XMMATRIX mtxRotateX = XMMatrixIdentity();

		// 오르막 구간에 x축 회전 추가
		if (i >= straightCount + leftTurnCount + rightTurnCount &&
			i < straightCount + leftTurnCount + rightTurnCount + ascendCount)
		{
			mtxRotateX = XMMatrixRotationZ(XMConvertToRadians(20.0f));
		}
		// 내리막 구간에 x축 회전 추가
		else if (i >= straightCount + leftTurnCount + rightTurnCount + ascendCount &&
			i < straightCount + leftTurnCount + rightTurnCount + ascendCount + descendCount)
		{
			mtxRotateX = XMMatrixRotationZ(XMConvertToRadians(-20.0f));
		}

		XMMATRIX mtxTranslate = XMMatrixTranslation(
			m_vRailPath[i].x, m_vRailPath[i].y, m_vRailPath[i].z
		);

		XMMATRIX mtxWorld = mtxRotateX * mtxRotateY * mtxTranslate;
		XMFLOAT4X4 xmf4x4World;
		XMStoreFloat4x4(&xmf4x4World, mtxWorld);
		pRail->SetWorldMatrix(xmf4x4World);

		m_ppObjects[i] = pRail;
	}


	CreateShaderVariables(pd3dDevice, pd3dCommandList);

}

void CLevel1SceneShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}

void CLevel1SceneShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
	}
}

void CLevel1SceneShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CLevel1SceneShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{

	CShader::Render(pd3dCommandList, pCamera);

	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j])
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}
