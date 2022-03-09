#include "stdafx.h"
#include "SceneManager.h"
SceneManager* SceneManager::mSceneManager = nullptr;
SceneManager* SceneManager::GetSceneManager()
{
	return mSceneManager;
}

SceneManager::SceneManager()
{
	assert(mSceneManager == nullptr);
	mSceneManager = this;
}

void SceneManager::SetMapActors(const std::unordered_map<std::string, ActorStruct*>& ActorMap)
{
	for (auto&& Actor : ActorMap) {
		mActors.insert({ Actor.first,Actor.second });
	}
}

void SceneManager::RemoveActor(const std::string& Name)
{
	mActors.erase(Name);
}

void SceneManager::AddActor(ActorStruct* Actor)
{
	mActors.insert({ Actor->ActorName,Actor });
}

std::unordered_map<std::string, ActorStruct*>& SceneManager::GetAllActor()
{
	return mActors;
}
