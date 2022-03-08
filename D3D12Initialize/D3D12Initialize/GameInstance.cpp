#include "stdafx.h"
#include "GameInstance.h"
#include "WindowsFactory.h"
#include "LauncherPCWindow.h"
#include "AssetManager.h"
#include "FirstPersonCamera.h"
#include "WindowsInput.h"
void GameInstance::Init(HINSTANCE hInstance)
{
	mEngine = std::make_unique<Engine>(hInstance);
	mGameLogic = std::make_unique<GameLogic>();

	std::unique_ptr<WindowsFactory> fa = std::make_unique<WindowsFactory>();
	std::unique_ptr<WindowsInputBase> windowInput = std::make_unique<WindowsInput>();
	mWindows = fa->GetPCWindow(mEngine->GetApp(), windowInput.get());
	std::shared_ptr<Camera> cameraInput = std::make_shared<FirstPersonCamera>();
	cameraInput->SetCameraWnd(mEngine->MainWnd());
	mEngine->SetCameraInput(cameraInput.get());
	mGameLogic->Init();

	mWindows->InitWindows();
	mEngine->Initialize();

}

void GameInstance::UpDate()
{
	mWindows->Run();
}

void GameInstance::Destroy()
{
}
