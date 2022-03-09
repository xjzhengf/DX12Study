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
	void Update();
	void Destroy();
	void LoadMap(const std::string& PathName);
	static GameLogic* GetG0ameLogic();
	
protected:
	static GameLogic* mGameLogic;
};