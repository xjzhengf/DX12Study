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



class StaticMesh
{
public:
	StaticMesh();
	~StaticMesh();
	void ReadBinaryFileToStaticMeshStruct(char* TextPath);
	void SelectFile();
	StaticMeshInfo* GetStruct();
private:
	StaticMeshInfo myStruct;
};


