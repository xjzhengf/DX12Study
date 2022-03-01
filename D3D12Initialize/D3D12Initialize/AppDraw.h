#pragma once
#include "stdafx.h"
#include "D3DUtil.h"
#include "D3DApp.h"
#include "UploadBuffer.h"
#include "MathHelper.h"
#include "StaticMesh.h"
using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

struct Vertex
{
	glm::vec3 Pos;
	XMFLOAT4 Color;
	glm::vec3 Normal;
};
struct ObjectConstants {
	//XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
	glm::mat4x4 WorldViewProj = glm::identity<glm::mat4x4>();
};


class AppDraw : public D3DApp {
public:
	AppDraw(HINSTANCE hInstance);
	AppDraw(const AppDraw& sm) = delete;
	AppDraw& operator=(const AppDraw& sm) = delete;
	~AppDraw();

	virtual bool Initialize() override;
	void BuildStaticMeshStruct(StaticMeshInfo* staticMeshInfo);
private:
	virtual void OnResize() override;
	virtual void Update(const GameTimer& gt) override;
	virtual void Draw(const GameTimer& gt) override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y) override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y) override;
	virtual void OnMouseUp(WPARAM btnState, int x, int y) override;


	void BulidDescriptorHeaps();
	void BulidConstantBuffers();
	void BulidRootSignature();
	void BulidShadersAndInputLayout();
	void BuildStaticMeshGeometry();
	void BuildPSO();

private:
	ComPtr<ID3D12RootSignature> mRootSigmature = nullptr;
	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;
	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

	ComPtr<ID3DBlob> mvsByteCode = nullptr;
	ComPtr<ID3DBlob> mpsByteCode = nullptr;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
	ComPtr<ID3D12PipelineState> mPSO = nullptr;

	glm::mat4x4 mWorld = glm::identity<glm::mat4x4>();





	POINT mLastMousePos;
	StaticMeshInfo* myStruct;


};