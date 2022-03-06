#include "stdafx.h"
#include "AppDraw.h"



AppDraw::AppDraw(HINSTANCE hInstance) :D3DApp(hInstance)
{
}

AppDraw::~AppDraw()
{
}

bool AppDraw::Initialize()
{


	if (!D3DApp::Initialize())
		return false;


		ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

		BulidRootSignature();
		BulidShadersAndInputLayout();
		mCbvHeap.resize(myStruct.size());
		mObjectCB.resize(myStruct.size());
		for (int i = 0; i < myStruct.size(); i++) {
			BuildStaticMeshData(&myStruct[i],i);
			BulidDescriptorHeaps(i);
			BulidConstantBuffers(i);
		}
		BuildStaticMeshGeometry(meshDataVector);
		BuildPSO();
		ThrowIfFailed(mCommandList->Close());
		ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
		mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
		FlushCommandQueue();
	
	return true;
}

void AppDraw::OnResize()
{
	D3DApp::OnResize();
	camera.SetCameraPos(1000.0f, 1000.0f, 1000.0f);
	camera.SetLens(0.25f * glm::pi<float>(), AspectRatio(), 1.0f, 10000.0f);
	camera.LookAt(camera.GetCameraPos3f(), glm::vec3(0.0f, 0.0f, 0.0f),camera.GetUp());
}

void AppDraw::Update(const GameTimer& gt)
{

}

void AppDraw::Draw(const GameTimer& gt)
{
	ThrowIfFailed(mDirectCmdListAlloc->Reset());
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), mPSO.Get()));

	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);
	mCommandList->OMSetStencilRef(0);
	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());
	
	Time = gt.TotalTime();
	for (size_t i = 0; i < myStruct.size(); i++) {
		camera.UpdateViewMat();
		ObjectConstants objConstants;
		glm::qua<float> q = glm::qua<float>(
			myStruct[i].actorStruct.Transform[0].Rotation.w,
			myStruct[i].actorStruct.Transform[0].Rotation.x,
			myStruct[i].actorStruct.Transform[0].Rotation.y,
			myStruct[i].actorStruct.Transform[0].Rotation.z
			);

		glm::vec3 location = glm::vec3(
			myStruct[i].actorStruct.Transform[0].Location.x,
			myStruct[i].actorStruct.Transform[0].Location.y,
			myStruct[i].actorStruct.Transform[0].Location.z
		);
		glm::vec3 Scale = glm::vec3(
			myStruct[i].actorStruct.Transform[0].Scale3D.x,
			myStruct[i].actorStruct.Transform[0].Scale3D.y,
			myStruct[i].actorStruct.Transform[0].Scale3D.z
		);
		objConstants.Rotation = glm::mat4_cast(q);
		objConstants.Translate = glm::translate(objConstants.Translate, location);
		objConstants.Scale = glm::scale(objConstants.Scale, Scale);
		
		objConstants.Time = Time;
		glm::mat4x4 proj = camera.GetProj4x4();
		glm::mat4x4 view = camera.GetView4x4();

		glm::mat4x4 W = objConstants.Translate *objConstants.Rotation *objConstants.Scale;
		glm::mat4x4 worldViewProj = proj * view * W * mWorld;
		objConstants.WorldViewProj = glm::transpose(worldViewProj);
		mObjectCB[i]->CopyData(0, objConstants);

		ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvHeap[i].Get() };
		mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);
		mCommandList->SetGraphicsRootSignature(mRootSigmature.Get());

		mCommandList->IASetVertexBuffers(0, 1, &mBoxGeo->VertexBufferView());
		mCommandList->IASetIndexBuffer(&mBoxGeo->IndexBufferView());
		mCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		mCommandList->SetGraphicsRootDescriptorTable(0, mCbvHeap[i]->GetGPUDescriptorHandleForHeapStart());
		mCommandList->DrawIndexedInstanced(mBoxGeo->DrawArgs[to_string(i)].IndexCount, 1, 
		(UINT)mBoxGeo->DrawArgs[to_string(i)].StartIndexLocation, (UINT)mBoxGeo->DrawArgs[to_string(i)].BaseVertexLocation, 0);
	}

	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	ThrowIfFailed(mCommandList->Close());

	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);


	ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	FlushCommandQueue();
}

void AppDraw::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;
	SetCapture(mhMainWnd);
}

void AppDraw::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0) {
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));
		//mTheta += dx;
		//mPhi += dy;
		//mPhi = MathHelper::Clamp(mPhi, 0.1f, MathHelper::Pi - 0.1f);
		
		camera.RotateY(dx);
		camera.Pitch(dy);
	}
	else if ((btnState & MK_RBUTTON) != 0) {
		//相机旋转
		/*	float dx = 0.005f * static_cast<float>(x - mLastMousePos.x);
			float dy = 0.005f * static_cast<float>(y - mLastMousePos.y);
			camera.RotateLook(dx);*/
		//相机移动
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));
		camera.RotateY(dx);
		camera.Pitch(dy);
	}
	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void AppDraw::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}


void AppDraw::BuildStaticMeshStruct(StaticMeshData& meshData)
{
	myStruct.push_back(std::move(meshData)) ;
}

void AppDraw::BulidDescriptorHeaps(int index)
{
	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 1;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&cbvHeapDesc, IID_PPV_ARGS(&mCbvHeap[index])));
}

void AppDraw::BulidConstantBuffers(int index)
{
	mObjectCB[index] =std::make_unique<UploadBuffer<ObjectConstants>>(md3dDevice.Get(), 1, true);
	UINT objecBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	D3D12_GPU_VIRTUAL_ADDRESS cbAddress = mObjectCB[index]->Resource()->GetGPUVirtualAddress();
	int boxCBufIndex = 0;
	cbAddress += boxCBufIndex * objecBByteSize;

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = cbAddress;
	cbvDesc.SizeInBytes = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	md3dDevice->CreateConstantBufferView(&cbvDesc, mCbvHeap[index]->GetCPUDescriptorHandleForHeapStart());


}

void AppDraw::BulidRootSignature()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[1];

	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);

	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());
	if (errorBlob != nullptr) {
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);
	ThrowIfFailed(md3dDevice->CreateRootSignature(0, serializedRootSig->GetBufferPointer(), serializedRootSig->GetBufferSize(), IID_PPV_ARGS(&mRootSigmature)));
}

void AppDraw::BulidShadersAndInputLayout()
{
	HRESULT hr = S_OK;

	mvsByteCode = d3dUtil::CompileShader(L"Shaders\\color.hlsl", nullptr, "VS", "vs_5_0");
	mpsByteCode = d3dUtil::CompileShader(L"Shaders\\color.hlsl", nullptr, "PS", "ps_5_0");

	mInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
}

void AppDraw::BuildStaticMeshGeometry(std::vector<MeshData> meshData)
{
    //将模型数据数组里的数据合并为一个大数据
	size_t totalVertexSize = 0;
	size_t totalIndexSize = 0;
	std::vector<size_t> vertexOffset(myStruct.size());
	std::vector<size_t> indexOffset(myStruct.size());
	for (size_t i = 0; i < meshData.size(); i++) {
		if (i == 0) {
			vertexOffset[i] = 0;
			indexOffset[i] = 0;
		}
		else
		{
			vertexOffset[i] = meshData[i - 1].vertices.size() + vertexOffset[i - 1];
			indexOffset[i] = meshData[i - 1].indices.size() + indexOffset[i - 1];
		}
	}


	
	std::vector<Vertex> vertices(totalVertexSize);
	std::vector<uint32_t> indices(totalIndexSize);
	for (size_t i = 0; i < meshData.size(); i++) {

		
		for (size_t k =0 ; k<meshData[i].vertices.size();k++)
		{
			vertices.push_back(meshData[i].vertices[k]);
		}
		for (size_t k = 0; k < meshData[i].indices.size(); k++)
		{
			indices.push_back(meshData[i].indices[k]);
		}
	}




	const UINT vbByteSize = (UINT)vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(uint32_t);

	mBoxGeo = std::make_unique<MeshGeometry>();
	mBoxGeo->Name = "AppDraw";
	ThrowIfFailed(D3DCreateBlob(vbByteSize, &mBoxGeo->VertexBufferCPU));
	CopyMemory(mBoxGeo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &mBoxGeo->IndexBufferCPU));
	CopyMemory(mBoxGeo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	mBoxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(), mCommandList.Get(), vertices.data(), vbByteSize, mBoxGeo->VertexBufferUploader);
	mBoxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(md3dDevice.Get(), mCommandList.Get(), indices.data(), ibByteSize, mBoxGeo->IndexBufferUploader);

	mBoxGeo->VertexByteStride = sizeof(Vertex);
	mBoxGeo->VertexBufferByteSize = vbByteSize;
	mBoxGeo->IndexFormat = DXGI_FORMAT_R32_UINT;
	mBoxGeo->IndexBufferByteSize = ibByteSize;


	for (int i = 0; i < meshData.size(); i++) {
		totalVertexSize += meshData[i].vertices.size();
		totalIndexSize += meshData[i].indices.size();
		SubmeshGeometry submesh;
		submesh.IndexCount = (UINT)meshData[i].indices.size();
		submesh.StartIndexLocation = indexOffset[i];
		submesh.BaseVertexLocation = vertexOffset[i];
		std::string name = to_string(i);
		mBoxGeo->DrawArgs[name] = submesh;
	}


}

void AppDraw::BuildStaticMeshData(StaticMeshData* myStruct, int index)
{
	MeshData meshData;
	meshData.indices = myStruct->StaticMeshStruct.Indices;

	meshData.indices.resize(myStruct->StaticMeshStruct.Indices.size());
	size_t VerticesLen = myStruct->StaticMeshStruct.Vertices.size();
	meshData.vertices.resize(VerticesLen);
	for (int i = 0; i < VerticesLen; i++) {
		meshData.vertices[i].Pos.x = myStruct->StaticMeshStruct.Vertices[i].x ;
		meshData.vertices[i].Pos.y = myStruct->StaticMeshStruct.Vertices[i].y ;
		meshData.vertices[i].Pos.z = myStruct->StaticMeshStruct.Vertices[i].z ;

	}

	for (size_t i = 0; i < (myStruct->StaticMeshStruct.Indices.size()) / 3; i++) {
		UINT i0 = meshData.indices[i * 3 + 0];
		UINT i1 = meshData.indices[i * 3 + 1];
		UINT i2 = meshData.indices[i * 3 + 2];

		Vertex v0 = meshData.vertices[i0];
		Vertex v1 = meshData.vertices[i1];
		Vertex v2 = meshData.vertices[i2];

		glm::vec3 e0 = v1.Pos - v0.Pos;
		glm::vec3 e1 = v2.Pos - v0.Pos;
		glm::vec3 faceNormal = glm::cross(e0, e1);

		meshData.vertices[i0].Normal += faceNormal;
		meshData.vertices[i1].Normal += faceNormal;
		meshData.vertices[i2].Normal += faceNormal;
	}
	
	for (UINT i = 0 ;i<VerticesLen;i++)
	{
		meshData.vertices[i].Normal = glm::normalize(meshData.vertices[i].Normal);
	}
	meshDataVector.push_back(std::move(meshData));
}

void AppDraw::BuildPSO()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

	psoDesc.InputLayout = { mInputLayout.data(),(UINT)mInputLayout.size() };
	psoDesc.pRootSignature = mRootSigmature.Get();
	psoDesc.VS = {
		reinterpret_cast<BYTE*>(mvsByteCode->GetBufferPointer()),
		mvsByteCode->GetBufferSize()
	};
	psoDesc.PS = {
		reinterpret_cast<BYTE*>(mpsByteCode->GetBufferPointer()),
		mpsByteCode->GetBufferSize()
	};


	D3D12_DEPTH_STENCIL_DESC stencilDesc;
	//反面
	stencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	stencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	stencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_EQUAL;
	stencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_INCR;
	stencilDesc.DepthEnable = true;
	stencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	stencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	//正面
	stencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	stencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	stencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	stencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_INCR;
	stencilDesc.StencilEnable = true;
	stencilDesc.StencilReadMask = 0xff;
	stencilDesc.StencilWriteMask = 0xff;
	

	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.RasterizerState.FrontCounterClockwise = TRUE;
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	//psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	//psoDesc.DepthStencilState.StencilEnable = TRUE;
	//psoDesc.DepthStencilState.StencilReadMask = 1;
	//psoDesc.DepthStencilState.StencilWriteMask = 1;
	psoDesc.DepthStencilState = stencilDesc;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = mBackBufferFormat;
	psoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	psoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = mDepthStencilFormat;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSO)));
}

