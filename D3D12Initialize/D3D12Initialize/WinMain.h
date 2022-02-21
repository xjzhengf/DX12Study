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
	   bool mAppPause = false;         //�Ƿ���ͣ
	   bool mMinimized = false;        //��С��
	   bool mMaximized = false;        //���
	   bool mResizing = false;         //������С�Ƿ��϶�
	   bool mFullscreenState = false;  //����ȫ��
	   std::wstring mMainWndCaption = L"My Windows App";
	   int mClientWidht = 800;
	   int mClientHeight = 600;

	   D3DApp* theApp;
};