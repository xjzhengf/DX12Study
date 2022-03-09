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
	//����windows��������������windows
	std::unique_ptr<WindowsFactory> fa = std::make_unique<WindowsFactory>();
	//����windowsinput
	std::shared_ptr<WindowsInputBase> windowInput = std::make_shared<WindowsInput>();
	//��ȡPCWindows
	mWindows = fa->GetPCWindow(mEngine->GetApp(), windowInput);
	//���������������
	std::shared_ptr<Camera> cameraInput = std::make_shared<FirstPersonCamera>();
	//����������벶��Ĵ���
	cameraInput->SetCameraWnd(mEngine->MainWnd());
	//���������ڲ������������
	mEngine->SetCameraInput(cameraInput);
	//��ʼ��
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
