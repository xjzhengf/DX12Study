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
	//��ʼ������
	std::unique_ptr<WindowsFactory> fa = std::make_unique<WindowsFactory>();
	//����windowsinput
	std::shared_ptr<WindowsInputBase> windowInput = std::make_shared<WindowsInput>();
	//��ȡPCWindows
	mWindows = fa->GetPCWindow(windowInput);
	mWindows->InitWindows();


	//��ʼ��Render
	mRender = std::make_unique<DX12Render>();
	//���������������
	std::shared_ptr<Camera> cameraInput = std::make_shared<FirstPersonCamera>();
	//���������ڲ������������
	mRender->SetCameraInput(cameraInput);

	mAssetManager = std::make_shared<AssetManager>();
	mSceneManager = std::make_unique<SceneManager>();

	//��ʼ��Render
	mRender->Initialize();
	//�����������ϵͳ
	mTaskManager = std::make_unique<TaskManager>(GetModuleHandle(0));
}

void Engine::Run(GameTimer& gt)
{
	isRuning = true;
	gt.Reset();
//��ʼ��ѭ��
	while (isRuning && mWindows->Run())
	{
		mWindows->CalculateFrameStats(gt);
		RenderTick(gt);
		TaskTick(gt);
	}
}

void Engine::RenderTick(GameTimer& gt)
{
	gt.Tick();
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
	if (!mTaskManager->PrepareKey.empty()) {
		for (auto& Key : mTaskManager->PrepareKey) {
			mRender->camera->CameraMove(Key, NULL);
		}
		mTaskManager->PrepareKey.clear();
	}
	if (!mTaskManager->EventMapInMouse.empty()) {
		for (auto&& MouseKey : mTaskManager->EventMapInMouse) {
			mRender->camera->CameraMove(MouseKey.first, MouseKey.second);
		}
		mTaskManager->EventMapInMouse.clear();
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
		//delete mEngine;
		 mEngine=nullptr;
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

Engine* Engine::GetEngine()
{
	return mEngine;
}
