#pragma once
#include "stdafx.h"
#include "MeshProperty.h"

class SceneManager {
public:
	static SceneManager* GetSceneManager();

	SceneManager();
	SceneManager(const SceneManager& sm) = delete;
	SceneManager& operator=(const SceneManager& sm) = delete;
	void SetMapActors(const std::unordered_map<std::string, ActorStruct*>& Actors);
	void RemoveActor(const std::string& Name);
	void AddActor( ActorStruct* Actor);
	std::unordered_map<std::string, ActorStruct*>& GetAllActor();
protected:
	static SceneManager* mSceneManager;
private:
	std::unordered_map<std::string, ActorStruct*> mActors;
};