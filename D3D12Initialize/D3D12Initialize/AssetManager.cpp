#include "stdafx.h"
#include "AssetManager.h"
#include "fstream"

AssetManager* AssetManager::mAssetManager = nullptr;
AssetManager* AssetManager::GetAssetManager()
{
	return mAssetManager;
}

AssetManager::AssetManager()
{
	assert(mAssetManager == nullptr);
	mAssetManager = this;
}

AssetManager::~AssetManager()
{
}

bool AssetManager::LoadMap(const char* MapPath)
{
	Actors.clear();
	std::ifstream inFile(MapPath, std::ios::in);
	std::string buf;
	std::vector<std::string> ActorsPath;
	if (inFile.is_open()) {
		while (getline(inFile,buf))
		{
			ActorsPath.push_back(buf);
		}
	}
	else {
		return false;
	}
	for (std::string& ActorPath : ActorsPath) {
		ReadBinaryFileToActorStruct(ActorPath.c_str());
	}
	return true;
}



void AssetManager::ReadBinaryFileToStaticMeshStruct(const char* TextPath)
{
	std::ifstream inFile(TextPath, std::ios::binary);
	StaticMeshInfo* meshAsset = new StaticMeshInfo;
	if (inFile.is_open()) {
		int flag = 0;
		inFile.read((char*)&flag, sizeof(int));
		int strlen = 0;
		inFile.read((char*)&strlen, sizeof(int32_t));
		meshAsset->StaticMeshName.resize(strlen);
		inFile.read((char*)meshAsset->StaticMeshName.data(), strlen * sizeof(char));

		inFile.read((char*)&meshAsset->NumVertices, sizeof(int32_t));
		inFile.read((char*)&meshAsset->NumLOD, sizeof(int32_t));
		inFile.read((char*)&meshAsset->NumTriangles, sizeof(int32_t));
		inFile.read((char*)&meshAsset->NumIndices, sizeof(int32_t));

		int verticesLen = 0;
		inFile.read((char*)&verticesLen, sizeof(int32_t));
		meshAsset->Vertices.resize(verticesLen);
		inFile.read((char*)meshAsset->Vertices.data(), verticesLen * sizeof(FVector));

		int indicesLen = 0;
		inFile.read((char*)&indicesLen, sizeof(int32_t));
		meshAsset->Indices.resize(indicesLen);
		inFile.read((char*)meshAsset->Indices.data(), indicesLen * sizeof(uint32_t));

		
		int ColorVerticesLen = 0;
		inFile.read((char*)&ColorVerticesLen, sizeof(int32_t));
		meshAsset->ColorVertices.resize(ColorVerticesLen);
		inFile.read((char*)meshAsset->ColorVertices.data(), ColorVerticesLen * sizeof(FColor));
	}
	inFile.close();
	this->MeshAsset.insert({ meshAsset->StaticMeshName,meshAsset });
}

void AssetManager::ReadBinaryFileToActorStruct(const char* TextPathName)
{

	int ComponentLen = 0;
	int Meshlen = 0;
	ActorStruct* actor = new ActorStruct;
	std::ifstream inFile(TextPathName, std::ios::binary);
	if (inFile.is_open()) {
		int flag = 0;
		inFile.read((char*)&flag, sizeof(int));
		int len = 0;
		inFile.read((char*)&len, sizeof(int32_t));
		actor->ActorName.resize(actor->ActorName.size() + len * sizeof(char));
		inFile.read((char*)actor->ActorName.data(), len);

		inFile.read((char*)&ComponentLen, sizeof(int32_t));
		actor->Transform.resize(ComponentLen);
		inFile.read((char*)actor->Transform.data(), ComponentLen * sizeof(FTransform));


		inFile.read((char*)&Meshlen, sizeof(int32_t));
		actor->StaticMeshAssetName.resize(Meshlen);
		for (size_t i = 0; i < Meshlen; i++)
		{
			int strlen = 0;
			inFile.read((char*)&strlen, sizeof(int32_t));
			inFile.read((char*)actor->StaticMeshAssetName[i].data(), strlen);
		}

	}
	inFile.close();
	for (int i = 0; i < actor->StaticMeshAssetName.size(); i++) {
		std::string assetPath;
		assetPath = std::string("StaticMeshInfo\\").append(actor->StaticMeshAssetName[0].c_str()).append(".dat");
		ReadBinaryFileToStaticMeshStruct(assetPath.c_str());
	}
	Actors.insert({ actor->ActorName,actor });
}

StaticMeshInfo* AssetManager::FindAssetByActor(ActorStruct& actor)
{
	//虚幻导出的资源字符串后缀'/0'
	std::string str(actor.StaticMeshAssetName[0].c_str());
	str.resize(str.size() + 1);
	auto iter = MeshAsset.find(str);

	if (iter != MeshAsset.end()) {
		return iter->second;
	}
	return nullptr;
}

void AssetManager::SelectFile()
{
	char* TextPathName = new char;
	int len;
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All(*.*)\0*.*\0Text(*.txt)\0*.TXT\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		len = WideCharToMultiByte(CP_ACP, 0, szFile, -1, NULL, 0, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, szFile, -1, TextPathName, len, NULL, NULL);
		std::ifstream inFile(TextPathName, std::ios::binary);
		if (inFile.is_open()) {
			int flag = 0;
			inFile.read((char*)&flag, sizeof(int));
			inFile.close();
			if (flag) {

			}
			else {
				ReadBinaryFileToStaticMeshStruct(TextPathName);
			}
		}
	}
}

std::unordered_map<std::string, StaticMeshInfo*>& AssetManager::GetMeshAsset()
{
	return MeshAsset;
}

std::unordered_map<std::string, ActorStruct*>& AssetManager::GetActors()
{
	return Actors;
}

