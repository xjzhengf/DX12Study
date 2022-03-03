#pragma once

#include "MeshProperty.h"

struct StaticMeshInfo
{
	std::string StaticMeshName;
	int32_t NumVertices;
	int32_t NumLOD;
	int32_t NumTriangles;
	int32_t NumIndices;
	std::vector<FVector> Vertices;
	std::vector<uint32_t> Indices;
	std::vector<FColor> ColorVertices;
};

struct ActorStruct {
	std::string ActorName;
	std::vector<FTransform> Transform;
	std::vector <std::string> StaticMeshAssetName;
};

struct StaticMeshData
{
	ActorStruct actorStruct;
	StaticMeshInfo StaticMeshStruct;
};

class StaticMesh
{
public:
	StaticMesh();
	~StaticMesh();
	void ReadBinaryFileToStaticMeshStruct(const char* TextPath);
	void ReadBinaryFileToActorStruct(const char* TextPathName);
	void SelectFile();
	StaticMeshInfo* GetStaticMeshStruct();
	ActorStruct* GetActorSrtuct();
	StaticMeshData& GetStruct();
private:
	StaticMeshData meshData;

};


