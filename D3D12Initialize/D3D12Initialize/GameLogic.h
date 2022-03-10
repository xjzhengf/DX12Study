#pragma once
#include "stdafx.h"
#include "Engine.h"
class GameLogic {
public:
	GameLogic();
	GameLogic(const GameLogic& GL) = delete;
	GameLogic& operator=(const GameLogic& GL) = delete;
	~GameLogic();
	void Init();
	bool Update();
	void Destroy();
	bool LoadMap(const std::string& PathName);
};