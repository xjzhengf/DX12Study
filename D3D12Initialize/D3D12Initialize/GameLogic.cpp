#include "stdafx.h"
#include "GameLogic.h"
#include "AssetManager.h"
GameLogic* GameLogic::mGameLogic = nullptr;
GameLogic::GameLogic()
{
	assert(mGameLogic == nullptr);
	mGameLogic = this;
}

GameLogic::~GameLogic()
{

}

void GameLogic::Init()
{
	LoadMap("StaticMeshInfo\\Map\\ThirdPersonMap.txt");
}

void GameLogic::Update()
{
}

void GameLogic::Destroy()
{
	if (mGameLogic != nullptr) {
		 mGameLogic = nullptr;
	}
}

void GameLogic::LoadMap(const std::string& PathName)
{
	std::shared_ptr<AssetManager> assetManager = Engine::GetEngine()->GetAssetManager();
	assetManager->LoadMap(PathName.c_str());
	//¸üÐÂ»æÖÆ×´Ì¬
	Engine::GetEngine()->UpdateDrawState(true);
}

GameLogic* GameLogic::GetG0ameLogic()
{
	return mGameLogic;
}
