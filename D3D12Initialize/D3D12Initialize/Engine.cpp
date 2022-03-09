#include "stdafx.h"
#include "Engine.h"
#include "WindowsFactory.h"
#include "LauncherPCWindow.h"
#include "AssetManager.h"
#include "FirstPersonCamera.h"
#include "WindowsInput.h"
#include <thread>
Engine* Engine::mEngine = nullptr;
Engine::Engine()
{
	assert(mEngine == nullptr);
	mEngine = this;
}
Engine::~Engine()
{
	
}
void Engine::Init(HINSTANCE hInstance)
{
	mRender = std::make_unique<DX12Render>(hInstance);
	//创建windows工厂，用来创建windows
	std::unique_ptr<WindowsFactory> fa = std::make_unique<WindowsFactory>();
	//创建windowsinput
	std::shared_ptr<WindowsInputBase> windowInput = std::make_shared<WindowsInput>();
	//获取PCWindows
	mWindows = fa->GetPCWindow(mRender->GetApp(), windowInput);
	//创建相机输入类型
	std::shared_ptr<Camera> cameraInput = std::make_shared<FirstPersonCamera>();
	//设置相机输入捕获的窗口
	cameraInput->SetCameraWnd(mRender->MainWnd());
	//设置引擎内部相机输入类型
	mRender->SetCameraInput(cameraInput);

	//初始化
	mWindows->InitWindows();
	mRender->Initialize();
}

void Engine::Run(GameTimer& gt)
{
	isRuning = true;
	gt.Reset();
//开始主循环
	while (isRuning && mWindows->Run())
	{
		mWindows->CalculateFrameStats(gt);
		Tick(gt);
	}
}

void Engine::Tick(GameTimer& gt)
{
	gt.Tick();
	if (!mRender->GetAppPause()) {
		//CalculateFrameStats(gt);
		mRender->Update(gt);
		mRender->Draw(gt);
	}
	else
	{
		Sleep(100);
	}
}

void Engine::Destroy()
{
	if (mRender != nullptr) {
	    mRender= nullptr;
	}
	if (mWindows != nullptr) {
		mWindows = nullptr;
	}
	if (mEngine != nullptr) {
		delete mEngine;
	}
}

std::shared_ptr<AssetManager> Engine::GetAssetManager()
{
	return mRender->GetAssetManager();
}

void Engine::UpdateDrawState(bool state)
{
	mRender->isUpdateDraw = state;
}

Engine* Engine::GetEngine()
{
	return mEngine;
}
