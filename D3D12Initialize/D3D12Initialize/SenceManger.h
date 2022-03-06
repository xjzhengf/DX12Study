#pragma once

#include "MeshProperty.h"



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


