#include "stdafx.h"
#include "DX12Render.h"
#include "LauncherPCWindow.h"
#include "WindowsInputBase.h"

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return PCWindows::GetWindowsInput()->MsgProc(hwnd, msg, wParam, lParam);
}

PCWindows* PCWindows::pcWindows = nullptr;
//初始化塞入app和input
PCWindows::PCWindows(D3DApp* theApp, const std::shared_ptr<WindowsInputBase>& windowsInput)
{
	this->theApp = theApp->GetApp();
	assert(pcWindows == nullptr);
	pcWindows = this;
	mWindowsInput = windowsInput;
}
std::shared_ptr<WindowsInputBase> PCWindows::mWindowsInput = nullptr;
bool PCWindows::InitWindows()
{
	WNDCLASS wc;
	wc.hInstance = theApp->GetAppInst();
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.lpszClassName = L"MainWnd";
	wc.lpszMenuName = 0;

	if (!RegisterClass(&wc)) {
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}
	RECT R = { 0,0,mClientWidht , mClientHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);

	int width = R.right - R.left;
	int heigth = R.bottom - R.top;
	mhMainWnd = CreateWindow(L"MainWnd", mMainWndCaption.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, heigth, 0, 0, mhAppInst, 0);
	if (!mhMainWnd) {
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}
	theApp->SetWindow(mhMainWnd);
	theApp->SetClientHeight(mClientHeight);
	theApp->SetClientWidht(mClientWidht);
	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);
	return true;
}


PCWindows* PCWindows::GetPcWindows()
{
	return pcWindows;
}

std::shared_ptr<WindowsInputBase> PCWindows::GetWindowsInput()
{
	return mWindowsInput;
}


//LRESULT PCWindows::MsgProc(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_ACTIVATE:
//		if (LOWORD(wParam) == WA_INACTIVE) {
//			mAppPause = true;
//			mTimer.Stop();
//		}
//		else
//		{
//			mAppPause = false;
//			mTimer.Start();
//		}
//		return 0;
//	
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//
//	case WM_MENUCHAR:
//		// Don't beep when we alt-enter.
//		return MAKELRESULT(0, MNC_CLOSE);
//		//捕获消息，设置最小窗口大小
//	case WM_GETMINMAXINFO:
//		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
//		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
//		return 0;
//	case WM_LBUTTONDOWN:
//	case WM_MBUTTONDOWN:
//	case WM_RBUTTONDOWN:
//		theApp->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//		return 0;
//	case WM_LBUTTONUP:
//	case WM_MBUTTONUP:
//	case WM_RBUTTONUP:
//		theApp->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//		return 0;
//	case WM_MOUSEMOVE:
//		theApp->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
//		return 0;
//	case WM_MOUSEWHEEL:
//		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
//			theApp->camera.AddCameraSpeed(10);
//		 }
//		else
//		{
//			theApp->camera.AddCameraSpeed(-10);
//		}
//		return 0;
//	case WM_KEYDOWN:
//		 if ((int)wParam == VK_F2) {
//			theApp->Set4xMsaaState(!theApp->Get4xMsaaState());
//		}
//		else if (wParam == 'A') {
//			 theApp->camera.Strafe(-1.0f* (theApp->camera.GetCameraSpeed()));
//		}
//		else if (wParam == 'S') {
//			 theApp->camera.Walk(-1.0f * (theApp->camera.GetCameraSpeed()));
//		}
//		else if (wParam == 'D') {
//			 theApp->camera.Strafe(1.0f * (theApp->camera.GetCameraSpeed()));
//		}
//		else if (wParam == 'W') {
//			 theApp->camera.Walk(1.0f * (theApp->camera.GetCameraSpeed()));
//		 }
//		else if (wParam == 'E') {
//			 theApp->camera.UpDown(1.0f * (theApp->camera.GetCameraSpeed()));
//		 }
//		else if (wParam == 'Q') {
//			 theApp->camera.UpDown(-1.0f * (theApp->camera.GetCameraSpeed()));
//		 }
//		return 0;
//	case WM_KEYUP:
//		if (wParam == VK_ESCAPE)
//		{
//			PostQuitMessage(0);
//		}
//
//		return 0;
//	}
//
//	return DefWindowProc(hwd, msg, wParam, lParam);
//}

bool PCWindows::Run()
{
	bool Quit = false;
	MSG msg = { 0 };


		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) {
				Quit = true;
			}
		}
		/*else
		{
			gt.Tick();
			if (!mAppPause) {
				CalculateFrameStats(gt);
				theApp->Update(gt);
				theApp->Draw(gt);
			}
			else
			{
				Sleep(100);
			}
		}*/
	
	return !Quit;
}

void PCWindows::CalculateFrameStats(const GameTimer& gt)
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if ((gt.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wstring fpsStr = std::to_wstring(fps);
		std::wstring mspfStr = std::to_wstring(mspf);
		std::wstring timeStr = std::to_wstring(gt.TotalTime());

		std::wstring windowText = mMainWndCaption +
			L"    fps: " + fpsStr +
			L"   mspf: " + mspfStr+
			L"   TotalTime: " + timeStr;

		SetWindowText(mhMainWnd, windowText.c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

