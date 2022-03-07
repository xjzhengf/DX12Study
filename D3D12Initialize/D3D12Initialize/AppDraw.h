#pragma once
#include "stdafx.h"
#include "D3DUtil.h"
#include "D3DApp.h"
#include "UploadBuffer.h"
#include "MathHelper.h"
#include "MeshProperty.h"
using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;



struct Vertex
{
	glm::vec3 Pos;
	XMFLOAT4 Color;
	glm::vec3 Normal;
};
struct MeshData
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	
};
struct ObjectConstants {
	//XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
	glm::mat4x4 WorldViewProj = glm::identity<glm::mat4x4>();
	glm::mat4x4 Rotation = glm::identity<glm::mat4x4>();
	glm::mat4x4 Scale = glm::identity<glm::mat4x4>();
	glm::mat4x4 Translate = glm::identity<glm::mat4x4>();
	float Time = 0.0f;
};

class AppDraw : public D3DApp {
public:
	AppDraw(HINSTANCE hInstance);
	AppDraw(const AppDraw& sm) = delete;
	AppDraw& operator=(const AppDraw& sm) = delete;
	~AppDraw();

	virtual bool Initialize() override;
	void BuildStaticMeshStruct(StaticMeshData& staticMeshInfo);
private:
	virtual void OnResize() override;
	virtual void Update(const GameTimer& gt) override;
	virtual void Draw(const GameTimer& gt) override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y) override;
	virtual void OnMouseMove(WPARAM btnState, int x, int y) override;
	virtual void OnMouseUp(WPARAM btnState, int x, int y) override;


	void BulidDescriptorHeaps(int index);
	void BulidConstantBuffers(int index);
	void BulidRootSignature();
	void BulidShadersAndInputLayout();
	void BuildStaticMeshGeometry(std::vector<MeshData> meshData);
	void BuildStaticMeshData(StaticMeshData* myStruct,int index);
	void BuildPSO();

private:
	ComPtr<ID3D12RootSignature> mRootSigmature = nullptr;
	std::vector < ComPtr<ID3D12DescriptorHeap>> mCbvHeap ;
	std::vector<std::unique_ptr<UploadBuffer<ObjectConstants>>> mObjectCB ;
	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

	ComPtr<ID3DBlob> mvsByteCode = nullptr;
	ComPtr<ID3DBlob> mpsByteCode = nullptr;
	
	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
	ComPtr<ID3D12PipelineState> mPSO = nullptr;

	glm::mat4x4 mWorld = glm::identity<glm::mat4x4>();

	POINT mLastMousePos;
	std::vector<StaticMeshData> myStruct;
	std::vector<MeshData> meshDataVector;
	float Time;

};