#include "stdafx.h"
#include "TaskManager.h"

TaskManager* TaskManager::mTaskManager = nullptr;
TaskManager::TaskManager(HINSTANCE hInstance)
{
	assert(mTaskManager == nullptr);
	mTaskManager = this;
}

TaskManager* TaskManager::GetTaskManager()
{
	return mTaskManager;
}

void TaskManager::RunInput(const std::string& FuncName)
{
	isInput = true;
	for (const auto& EventPair : EventMapInString)
	{
		auto& Event = EventPair.second;
		if (Event) {
			Event(FuncName);
		}
	}
	for (const auto& Name : PrepareRemove) {
		EventMapInString.erase(Name);
	}
	isInput = false;
}

void TaskManager::Register(const std::string& Name, CallBackInString Callback)
{
	EventMapInString.insert({Name,Callback});
}

void TaskManager::RegisterMouse(const std::string& Name, LPARAM lParam)
{
	EventMapInMouse.insert({ Name,lParam });
}




void TaskManager::RegisterKey(const std::string& Name)
{
	PrepareKey.insert(Name);
}



void TaskManager::UnRegister(const std::string& Name)
{
	if (isInput) {
		PrepareRemove.push_back(Name);
	}
	else
	{
		EventMapInString.erase(Name);
	}
}
