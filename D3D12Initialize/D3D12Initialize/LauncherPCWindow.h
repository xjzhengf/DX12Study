#pragma once
#include "stdafx.h"
#include "WindowBase.h"
class PCWindows :public WindowBase{
public:
	PCWindows(D3DApp* theApp, WindowsInputBase* windowsInput);
	virtual bool InitWindows() override;

	static PCWindows* GetPcWindows();
	static WindowsInputBase* GetWindowsInput();
	
	//virtual LRESULT MsgProc(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual int Run() override;

	void CalculateFrameStats();
protected:
	GameTimer mTimer;
	static WindowsInputBase* mWindowsInput;
	static PCWindows* pcWindows;
private:	
	   HINSTANCE mhAppInst = nullptr;
	   HWND mhMainWnd = nullptr;
	   bool mAppPause = false;         //是否暂停
	   bool mMinimized = false;        //最小化
	   bool mMaximized = false;        //最大化
	   bool mResizing = false;         //调整大小是否被拖动
	   bool mFullscreenState = false;  //开启全屏
	   std::wstring mMainWndCaption = L"My Windows App";
	   int mClientWidht = 800;
	   int mClientHeight = 600;
	   D3DApp* theApp;
	
};