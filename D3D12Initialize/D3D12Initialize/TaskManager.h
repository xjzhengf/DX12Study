#pragma once
#include "stdafx.h"


class TaskManager
{
public:
	std::unordered_map<std::string, CallBackType> EventMap;
	std::vector<std::string> PrepareRemove;
	std::set<std::string> PrepareKey; 
	TaskManager(HINSTANCE hInstance);
	TaskManager(const TaskManager& sm) = delete;
	TaskManager& operator=(const TaskManager& sm) = delete;
	static TaskManager* GetTaskManager();

	void RunInput(const std::string& FuncName);
	void Register(const std::string& Name, CallBackType Callback);
	void RegisterKey(const std::string& Name);
	void UnRegister(const std::string& Name);
private:
	bool isInput = false;
protected:
	static TaskManager* mTaskManager;
};

