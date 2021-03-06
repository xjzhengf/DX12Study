#include "stdafx.h"
#include "GameLogic.h"
#include "AssetManager.h"
#include "TaskManager.h"

GameLogic* GameLogic::mGameLogic = nullptr;
GameLogic::GameLogic()
{
	assert(mGameLogic == nullptr);
	mGameLogic=this;
}

GameLogic::~GameLogic()
{
	if (mGameLogic != nullptr) {
		mGameLogic = nullptr;
	}
}

void GameLogic::Init()
{
	LoadMap("StaticMeshInfo\\Map\\ThirdPersonMap.txt");
}

void GameLogic::Update()
{
	ProcessMouse();
	ProcessKey();
}

void GameLogic::Destroy()
{
}

GameLogic* GameLogic::GetGameLogic()
{
	return mGameLogic;
}

bool GameLogic::LoadMap(const std::string& PathName)
{
	std::shared_ptr<SceneManager> sceneManager = Engine::GetEngine()->GetSceneManager();
	if (sceneManager->LoadMap(PathName.c_str())) {
		//更新绘制模型
		Engine::GetEngine()->UpdateDrawState(true);
		return true;
	}
	return false;
}

void GameLogic::ProcessKey()
{
	if (!TaskManager::GetTaskManager()->EventKey.empty()) {
		for (auto&& Key : TaskManager::GetTaskManager()->EventKey) {

			if (SceneManager::GetSceneManager()->GetCamera()->CameraMove("", Key, 0)) {
				TaskManager::GetTaskManager()->UnRegisterKey(Key);
			}
#ifdef _WIN32 
			if (Key == VK_ESCAPE) {
				Engine::GetEngine()->SetRuningState(false);
			}
			//暂时有bug
			/*if (Key == VK_TAB)
			{
				if (LoadMap("StaticMeshInfo\\Map\\ThirdPersonMap2.txt"))
					TaskManager::GetTaskManager()->UnRegisterKey(Key);
			}*/
#else
			
#endif
		}
		TaskManager::GetTaskManager()->ClearImplKey();
	}
}

void GameLogic::ProcessMouse()
{
	if (!TaskManager::GetTaskManager()->EventMouseKeyMap.empty())
	{
		for (auto&& MouseKey : TaskManager::GetTaskManager()->EventMouseKeyMap) {
			SceneManager::GetSceneManager()->GetCamera()->CameraMove(MouseKey.first, NULL, MouseKey.second);
		}
		TaskManager::GetTaskManager()->EventMouseKeyMap.clear();

	}
}
