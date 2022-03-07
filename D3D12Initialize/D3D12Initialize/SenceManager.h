#pragma once
#include "MeshProperty.h"
class SenceManager
{
public:
	SenceManager();
	~SenceManager();
	void ReadBinaryFileToStaticMeshStruct(const char* TextPath);
	void ReadBinaryFileToActorStruct(const char* TextPathName);
	void SelectFile();
	StaticMeshInfo* GetStaticMeshStruct();
	ActorStruct* GetActorSrtuct();
	StaticMeshData& GetStruct();
private:
	StaticMeshData meshData;

};


