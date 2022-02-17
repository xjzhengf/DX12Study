#include "AppDraw.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

#if defined(Debug) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		char* Path = "D:\\UEWorkSpace\\GameTest\\StaticMeshInfo\\MaterialSphere.dat";
		std::unique_ptr<StaticMesh> staticMesh = std::make_unique<StaticMesh>();
		//staticMesh->SelectFile();
		staticMesh->ReadBinaryFileToStaticMeshStruct(Path);
		AppDraw theApp(hInstance);
		theApp.BuildStaticMeshStruct(staticMesh->GetStruct());
		if (!theApp.Initialize()) {
			return 0;
		}
	
		return theApp.Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}