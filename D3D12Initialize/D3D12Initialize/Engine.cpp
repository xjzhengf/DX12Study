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
	//初始化窗口
	std::unique_ptr<WindowsFactory> fa = std::make_unique<WindowsFactory>();
	//获取PCWindows
	mWindows = fa->GetWindows();
	mWindows->InitWindows();
	//初始化Render
	mRender = std::make_unique<DX12Render>();
	//创建相机输入类型
	std::shared_ptr<Camera> cameraInput = std::make_shared<FirstPersonCamera>();
	//设置引擎内部相机输入类型
	mRender->SetCameraInput(cameraInput);

	//初始化资源管理和场景管理
	mAssetManager = std::make_shared<AssetManager>();
	mSceneManager = std::make_unique<SceneManager>();

	//初始化Render
	mRender->Initialize();
	//创建任务管理系统
	mTaskManager = std::make_unique<TaskManager>(GetModuleHandle(0));
}

void Engine::Run(GameTimer& gt)
{

//开始主循环
	while (isRuning && mWindows->Run())
	{
		RenderTick(gt);
		isRuning = false;
	}
}

void Engine::RenderTick(GameTimer& gt)
{
	mWindows->CalculateFrameStats(gt);
	gt.Tick();
	TaskTick(gt);
	if (!mRender->GetAppPause()) {
		mRender->Update(gt);
		mRender->Draw(gt);
	}
	else
	{
		Sleep(100);
	}
}

void Engine::TaskTick(GameTimer& gt)
{

	if (!mTaskManager->EventKey.empty()) {
		for (auto&& Key : mTaskManager->EventKey) {
			if (mRender->camera->CameraMove("", Key, 0))
				mTaskManager->UnRegisterKey(Key);
		}
		mTaskManager->ClearImplKey();
	}
	if (!mTaskManager->EventMouseKeyMap.empty())
	{
		for (auto&& MouseKey : mTaskManager->EventMouseKeyMap) {
			mRender->camera->CameraMove(MouseKey.first, NULL, MouseKey.second);
		}
		mTaskManager->EventMouseKeyMap.clear();

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
		 mEngine=nullptr;
	}
	if (mTaskManager != nullptr) {
		mTaskManager = nullptr;
	}
	if (mSceneManager != nullptr) {
		mSceneManager = nullptr;
	}
	if (mAssetManager != nullptr) {
		mAssetManager = nullptr;
	}
	
}

std::shared_ptr<AssetManager> Engine::GetAssetManager()
{
	return mAssetManager;
}

void Engine::UpdateDrawState(bool state)
{
	mRender->isUpdateDraw = state;
}

std::shared_ptr<WindowBase> Engine::GetWindow()
{
	return mWindows;
}

bool Engine::GetRuningState()
{
	return isRuning;
}

void Engine::SetRuningState(bool state)
{
	isRuning = state;
}

Engine* Engine::GetEngine()
{
	return mEngine;
}
