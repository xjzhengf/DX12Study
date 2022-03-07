#pragma once
#include "stdafx.h"


class TaskManager
{
public:
	std::unordered_map<std::string, CallBackInString> EventMapInString;
	std::map<std::string, LPARAM> EventMapInMouse;

	std::vector<std::string> PrepareRemove;
	std::set<std::string> PrepareKey; 
	TaskManager(HINSTANCE hInstance);
	TaskManager(const TaskManager& tm) = delete;
	TaskManager& operator=(const TaskManager& tm) = delete;
	static TaskManager* GetTaskManager();

	void RunInput(const std::string& FuncName);
	void Register(const std::string& Name, CallBackInString Callback);
	void RegisterMouse(const std::string& Name, LPARAM lParam);
	void RegisterKey(const std::string& Name);
	void UnRegister(const std::string& Name);
private:
	bool isInput = false;
protected:
	static TaskManager* mTaskManager;
};

