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
	//创建windows工厂，用来创建windows
	std::unique_ptr<WindowsFactory> fa = std::make_unique<WindowsFactory>();
	//创建windowsinput
	std::shared_ptr<WindowsInputBase> windowInput = std::make_shared<WindowsInput>();
	//获取PCWindows
	mWindows = fa->GetPCWindow(mEngine->GetApp(), windowInput);
	//创建相机输入类型
	std::shared_ptr<Camera> cameraInput = std::make_shared<FirstPersonCamera>();
	//设置相机输入捕获的窗口
	cameraInput->SetCameraWnd(mEngine->MainWnd());
	//设置引擎内部相机输入类型
	mEngine->SetCameraInput(cameraInput);
	//初始化
	mGameLogic->Init();
	mWindows->InitWindows();
	mEngine->Initialize();
	
}

void GameInstance::UpDate()
{
	mTimer.Reset();
	while (mWindows->IsWindowRuning)
	{
		mWindows->Run(mTimer);
	}

}

void GameInstance::Destroy()
{
}
