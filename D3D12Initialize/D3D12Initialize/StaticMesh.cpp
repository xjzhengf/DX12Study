#include "stdafx.h"
#include "StaticMesh.h"
#include "fstream"


StaticMesh::StaticMesh()
{
}

StaticMesh::~StaticMesh()
{
}



void StaticMesh::ReadBinaryFileToStaticMeshStruct(const char* TextPath)
{
	std::ifstream inFile(TextPath, std::ios::binary);
	if (inFile.is_open()) {
		int flag = 0;
		inFile.read((char*)&flag, sizeof(int));
		int strlen = 0;
		inFile.read((char*)&strlen, sizeof(int32_t));
		meshData.StaticMeshStruct.StaticMeshName.resize(strlen);
		inFile.read((char*)meshData.StaticMeshStruct.StaticMeshName.data(), strlen * sizeof(char));

		inFile.read((char*)&meshData.StaticMeshStruct.NumVertices, sizeof(int32_t));
		inFile.read((char*)&meshData.StaticMeshStruct.NumLOD, sizeof(int32_t));
		inFile.read((char*)&meshData.StaticMeshStruct.NumTriangles, sizeof(int32_t));
		inFile.read((char*)&meshData.StaticMeshStruct.NumIndices, sizeof(int32_t));

		int verticesLen = 0;
		inFile.read((char*)&verticesLen, sizeof(int32_t));
		meshData.StaticMeshStruct.Vertices.resize(verticesLen);
		inFile.read((char*)meshData.StaticMeshStruct.Vertices.data(), verticesLen * sizeof(FVector));

		int indicesLen = 0;
		inFile.read((char*)&indicesLen, sizeof(int32_t));
		meshData.StaticMeshStruct.Indices.resize(indicesLen);
		inFile.read((char*)meshData.StaticMeshStruct.Indices.data(), indicesLen * sizeof(uint32_t));

		
		int ColorVerticesLen = 0;
		inFile.read((char*)&ColorVerticesLen, sizeof(int32_t));
		meshData.StaticMeshStruct.ColorVertices.resize(ColorVerticesLen);
		inFile.read((char*)meshData.StaticMeshStruct.ColorVertices.data(), ColorVerticesLen * sizeof(FColor));
	}
	inFile.close();

}

void StaticMesh::ReadBinaryFileToActorStruct(const char* TextPathName)
{

	int ComponentLen = 0;
	int Meshlen = 0;
	std::ifstream inFile(TextPathName, std::ios::binary);
	if (inFile.is_open()) {
		int flag = 0;
		inFile.read((char*)&flag, sizeof(int));
		int len = 0;
		inFile.read((char*)&len, sizeof(int32_t));
		meshData.actorStruct.ActorName.resize(meshData.actorStruct.ActorName.size() + len * sizeof(char));
		inFile.read((char*)meshData.actorStruct.ActorName.data(), len);

		inFile.read((char*)&ComponentLen, sizeof(int32_t));
		meshData.actorStruct.Transform.resize(ComponentLen);
		inFile.read((char*)meshData.actorStruct.Transform.data(), ComponentLen * sizeof(FTransform));


		inFile.read((char*)&Meshlen, sizeof(int32_t));
		meshData.actorStruct.StaticMeshAssetName.resize(Meshlen);
		for (size_t i = 0; i < Meshlen; i++)
		{
			int strlen = 0;
			inFile.read((char*)&strlen, sizeof(int32_t));
			inFile.read((char*)meshData.actorStruct.StaticMeshAssetName[i].data(), strlen);
		}

	}
	inFile.close();
	for (int i = 0; i < meshData.actorStruct.StaticMeshAssetName.size(); i++) {
		std::string assetPath;
		assetPath = std::string("StaticMeshInfo\\").append(meshData.actorStruct.StaticMeshAssetName[0].c_str()).append(".dat");
		ReadBinaryFileToStaticMeshStruct(assetPath.c_str());
	}

}

void StaticMesh::SelectFile()
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

StaticMeshInfo* StaticMesh::GetStaticMeshStruct()
{
	return &meshData.StaticMeshStruct;
}

ActorStruct* StaticMesh::GetActorSrtuct()
{
	return &meshData.actorStruct;
}

StaticMeshData& StaticMesh::GetStruct()
{
	return meshData;
}
