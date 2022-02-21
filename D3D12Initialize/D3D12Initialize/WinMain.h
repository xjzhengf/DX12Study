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
	   bool mAppPause = false;         //�Ƿ���ͣ
	   bool mMinimized = false;        //��С��
	   bool mMaximized = false;        //���
	   bool mResizing = false;         //������С�Ƿ��϶�
	   bool mFullscreenState = false;  //����ȫ��
	   std::wstring mMainWndCaption = L"My Windows App";
	   int mClientWidht = 800;
	   int mClientHeight = 600;
};