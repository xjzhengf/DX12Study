#pragma once
#include "stdafx.h"
#include "DX12Render.h"
#include "WindowBase.h"
class Engine
{
public:
	Engine();
	~Engine();
	void Init(HINSTANCE hInstance);
	void Run(GameTimer& gt);
	void Tick(GameTimer& gt);
	void Destroy();
	static Engine* GetEngine();
	std::shared_ptr<AssetManager> GetAssetManager();
	void UpdateDrawState(bool state);
protected:

	static Engine* mEngine;
private:
	std::unique_ptr<DX12Render> mRender;
	std::unique_ptr<WindowBase> mWindows;

	bool isRuning;
};



