#include "stdafx.h"
#include "Engine.h"
#include "WindowsFactory.h"
#include "LauncherPCWindow.h"
#include "AssetManager.h"
#include "FirstPersonCamera.h"
#include "WindowsInput.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

#if defined(Debug) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		Engine theApp(hInstance);

		std::unique_ptr<WindowsFactory> fa = std::make_unique<WindowsFactory>();
		std::shared_ptr<WindowsInputBase> windowInput = std::make_shared<WindowsInput>();
		std::unique_ptr<WindowBase>myWindows =  fa->GetPCWindow(&theApp, windowInput.get());
		std::shared_ptr<Camera> cameraInput = std::make_shared<FirstPersonCamera>();
		cameraInput->SetCameraWnd(theApp.MainWnd());
		theApp.SetCameraInput(cameraInput.get());
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