#include "stdafx.h"
#include "AppDraw.h"
#include "WindowsFactory.h"
#include "LauncherPCWindow.h"
#include "SenceManger.h"
#include "WindowsInput.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

#if defined(Debug) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		std::vector<std::string> PathVector;
		std::string Path;
		Path= "StaticMeshInfo\\Actor\\Wall10.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\Wall11.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\Bump_StaticMesh.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\CubeMesh_5.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\Floor_1.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\LeftArm_StaticMesh.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\Linear_Stair_StaticMesh.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\Ramp_StaticMesh.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\RightArm_StaticMesh.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\StaticMeshActor_1.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\StaticMeshActor_3.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\Wall7_4.dat";
		PathVector.push_back(Path);
		Path = "StaticMeshInfo\\Actor\\Wall9.dat";
		PathVector.push_back(Path);


		AppDraw theApp(hInstance);
		unique_ptr<WindowsFactory> fa = make_unique<WindowsFactory>();
		shared_ptr<WindowsInputBase> windowInput = make_shared<WindowsInput>();
		
		unique_ptr<WindowBase>myWindows =  fa->GetPCWindow(&theApp, windowInput.get());
		std::shared_ptr<StaticMesh> staticMesh = std::make_shared<StaticMesh>();
		for (int i =0;i<PathVector.size();i++)
		{
			staticMesh->ReadBinaryFileToActorStruct(PathVector[i].c_str());
			theApp.BuildStaticMeshStruct(staticMesh->GetStruct());
		}

		if (!myWindows->InitWindows()) {
			return 0;
		}
		if (!theApp.Initialize()) {
			return 0;
		}

		return myWindows->Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}