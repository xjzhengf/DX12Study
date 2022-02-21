#pragma once
class MyWindows {
public:
	MyWindows(D3DApp* theApp);
	bool InitWindows();

	static MyWindows* GetPcWindows();

	virtual LRESULT MsgProc(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam);

	int Run();

	void CalculateFrameStats();
protected:
	GameTimer mTimer;

	static MyWindows* pcWindows;
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