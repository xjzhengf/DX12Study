#include "stdafx.h"
#include "GameLogic.h"
#include "AssetManager.h"
#include "TaskManager.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{

}

void GameLogic::Init()
{
	LoadMap("StaticMeshInfo\\Map\\ThirdPersonMap.txt");
}

bool GameLogic::Update()
{
	if (!TaskManager::GetTaskManager()->EventKey.empty()) {
		for (auto&& Key : TaskManager::GetTaskManager()->EventKey) {
#ifdef _WIN32 
			if (Key == VK_ESCAPE) {
				return false;
			}
			if (Key == VK_TAB)
			{
				if (LoadMap("StaticMeshInfo\\Map\\ThirdPersonMap2.txt"))
				TaskManager::GetTaskManager()->UnRegisterKey(Key);
			}
			TaskManager::GetTaskManager()->ClearImplKey();
#else
			return true;
#endif
		}
	}
	Engine::GetEngine()->SetRuningState(true);
	return true;
}

void GameLogic::Destroy()
{
}

bool GameLogic::LoadMap(const std::string& PathName)
{
	std::shared_ptr<AssetManager> assetManager = Engine::GetEngine()->GetAssetManager();
	if (assetManager->LoadMap(PathName.c_str())) {
		//更新绘制模型
		SceneManager::GetSceneManager()->SetMapActors(AssetManager::GetAssetManager()->GetActors());
	}
	return false;
}
