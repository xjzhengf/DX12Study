#pragma once
#include "stdafx.h"
#include "MeshProperty.h"

class SceneManager {
public:
	void SetMapActors(const std::unordered_map<std::string, ActorStruct*>& Actors);
	void RemoveActor(const std::string& Name);
	void AddActor( ActorStruct* Actor);
	std::unordered_map<std::string, ActorStruct*>& GetAllActor();
private:
	std::unordered_map<std::string, ActorStruct*> mActors;
};