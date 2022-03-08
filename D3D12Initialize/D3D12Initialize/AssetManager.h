#pragma once
#include "MeshProperty.h"
class AssetManager
{
public:
	AssetManager();
	~AssetManager();
	void LoadMap(const char* MapPath);
	void ReadBinaryFileToStaticMeshStruct(const char* TextPath);
	void ReadBinaryFileToActorStruct(const char* TextPathName);
	StaticMeshInfo* FindAssetByActor(ActorStruct& actor);

	void SelectFile();
	std::unordered_map<std::string, StaticMeshInfo*>& GetMeshAsset();
	std::unordered_map<std::string, ActorStruct*>& GetActors();
private:
	std::unordered_map<std::string, ActorStruct*> Actors;
	std::unordered_map<std::string, StaticMeshInfo*> MeshAsset;
	
};


