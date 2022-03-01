#include "stdafx.h"
#include "AppDraw.h"
#include "WindowsFactory.h"
#include "WinMain.h"
#include "StaticMesh.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

#if defined(Debug) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		char* Path = "StaticMeshInfo\\ZLStaticMesh.dat";
		char* TablePath = "StaticMeshInfo\\SM_TableRound.dat";
		std::unique_ptr<StaticMesh> staticMesh = std::make_unique<StaticMesh>();
		std::unique_ptr<StaticMesh> TableMesh = std::make_unique<StaticMesh>();
		//staticMesh->SelectFile();
		staticMesh->ReadBinaryFileToStaticMeshStruct(Path);
		TableMesh->ReadBinaryFileToStaticMeshStruct(TablePath);
		AppDraw theApp(hInstance);
		unique_ptr<WindowsFactory> fa = make_unique<WindowsFactory>();
		unique_ptr<WindowBase>myWindows =  fa->GetPCWindow(&theApp);

		if (!myWindows->InitWindows()) {
			return 0;
		}
		theApp.BuildStaticMeshStruct(staticMesh->GetStruct());
		theApp.BuildStaticMeshStruct(TableMesh->GetStruct());
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