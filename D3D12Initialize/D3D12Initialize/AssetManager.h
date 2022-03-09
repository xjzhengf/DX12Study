#pragma once
#include "MeshProperty.h"
class AssetManager
{
public:
	static AssetManager* GetAssetManager();

	AssetManager();
	AssetManager(const AssetManager& am) = delete;
	AssetManager& operator=(const AssetManager& am) = delete;
	~AssetManager();
	void LoadMap(const char* MapPath);
	void ReadBinaryFileToStaticMeshStruct(const char* TextPath);
	void ReadBinaryFileToActorStruct(const char* TextPathName);
	StaticMeshInfo* FindAssetByActor(ActorStruct& actor);

	void SelectFile();
	std::unordered_map<std::string, StaticMeshInfo*>& GetMeshAsset();
	std::unordered_map<std::string, ActorStruct*>& GetActors();
protected:
	static AssetManager* mAssetManager;
private:
	std::unordered_map<std::string, ActorStruct*> Actors;
	std::unordered_map<std::string, StaticMeshInfo*> MeshAsset;
	
};


