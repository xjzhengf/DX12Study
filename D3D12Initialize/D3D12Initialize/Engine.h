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
	void RenderTick(GameTimer& gt);
	void Destroy();
	std::shared_ptr<Camera> GetCamera();
	static Engine* GetEngine();
	std::shared_ptr<AssetManager> GetAssetManager();
	void UpdateDrawState(bool state);
	std::shared_ptr<WindowBase> GetWindow();
	bool GetRuningState();
	void SetRuningState(bool state);
protected:

	static Engine* mEngine;
private:
	std::unique_ptr<DX12Render> mRender;
	std::shared_ptr<WindowBase> mWindows;
	std::shared_ptr<AssetManager> mAssetManager;
	std::unique_ptr<SceneManager> mSceneManager;
	std::unique_ptr<TaskManager> mTaskManager;
	bool isRuning;
};



