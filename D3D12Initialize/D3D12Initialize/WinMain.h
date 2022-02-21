#pragma once
class MyWindows {
public:
	MyWindows();
	bool InitWindows();
protected:
	GameTimer mTimer;
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
};