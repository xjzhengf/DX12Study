#include "stdafx.h"
#include "StaticMesh.h"
#include "fstream"
#include <windows.h>  
#include <commdlg.h>  

StaticMesh::StaticMesh()
{
}

StaticMesh::~StaticMesh()
{
}



void StaticMesh::ReadBinaryFileToStaticMeshStruct(char* TextPath)
{
	std::ifstream inFile(TextPath, std::ios::binary);
	if (inFile.is_open()) {
		int flag = 0;
		inFile.read((char*)&flag, sizeof(int));
		int strlen = 0;
		inFile.read((char*)&strlen, sizeof(int32_t));
		myStruct.StaticMeshName.resize(strlen);
		inFile.read((char*)myStruct.StaticMeshName.data(), strlen * sizeof(char));

		inFile.read((char*)&myStruct.NumVertices, sizeof(int32_t));
		inFile.read((char*)&myStruct.NumLOD, sizeof(int32_t));
		inFile.read((char*)&myStruct.NumTriangles, sizeof(int32_t));
		inFile.read((char*)&myStruct.NumIndices, sizeof(int32_t));

		int verticesLen = 0;
		inFile.read((char*)&verticesLen, sizeof(int32_t));
		myStruct.Vertices.resize(verticesLen);
		inFile.read((char*)myStruct.Vertices.data(), verticesLen * sizeof(FVector));

		int indicesLen = 0;
		inFile.read((char*)&indicesLen, sizeof(int32_t));
		myStruct.Indices.resize(indicesLen);
		inFile.read((char*)myStruct.Indices.data(), indicesLen * sizeof(uint32_t));

		
		int ColorVerticesLen = 0;
		inFile.read((char*)&ColorVerticesLen, sizeof(int32_t));
		myStruct.ColorVertices.resize(ColorVerticesLen);
		inFile.read((char*)myStruct.ColorVertices.data(), ColorVerticesLen * sizeof(FColor));
	}
	inFile.close();
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

StaticMeshInfo* StaticMesh::GetStruct()
{
	return &myStruct;
}
