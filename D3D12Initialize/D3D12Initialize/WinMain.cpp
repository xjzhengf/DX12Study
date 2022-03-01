#include "stdafx.h"
#include "AppDraw.h"
#include "WinMain.h"


LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return PCWindows::GetPcWindows()->MsgProc(hwnd, msg, wParam, lParam);
}

PCWindows* PCWindows::pcWindows = nullptr;
PCWindows::PCWindows(D3DApp* theApp)
{
	this->theApp = theApp->GetApp();
	assert(pcWindows == nullptr);
	pcWindows = this;
}

bool PCWindows::InitWindows()
{
	WNDCLASS wc;
	wc.hInstance = mhAppInst;
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

LRESULT PCWindows::MsgProc(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE) {
			mAppPause = true;
			mTimer.Stop();
		}
		else
		{
			mAppPause = false;
			mTimer.Start();
		}
		return 0;
	case WM_SIZE:
		mClientWidht = LOWORD(lParam);
		mClientHeight = HIWORD(lParam);
		if (theApp->IsHaveDevice())
		{
			if (wParam == SIZE_MINIMIZED) {
				mAppPause = true;
				mMinimized = true;
				mMaximized = false;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				mAppPause = false;
				mMinimized = false;
				mMaximized = true;
				theApp->OnResize();
			}
			else if (wParam == SIZE_RESTORED)
			{
				if (mMinimized)
				{
					mAppPause = false;
					mMinimized = false;
					theApp->OnResize();
				}
				else if (mMaximized) {
					mAppPause = false;
					mMaximized = false;
					theApp->OnResize();
				}
				else if (mResizing)
				{

				}
				else
				{
					theApp->OnResize();
				}
			}
		}
		return 0;
	case WM_ENTERSIZEMOVE:
		mAppPause = true;
		mResizing = true;
		mTimer.Stop();
		return 0;
	case WM_EXITSIZEMOVE:
		mAppPause = false;
		mResizing = false;
		mTimer.Start();
		theApp->OnResize();
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);
		//捕获消息，设置最小窗口大小
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;


	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		theApp->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		theApp->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		theApp->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_KEYDOWN:
		 if ((int)wParam == VK_F2) {
			theApp->Set4xMsaaState(!theApp->Get4xMsaaState());
		}
		else if (wParam == 'A') {
			 theApp->camera.Strafe(-1.0f);
		}
		else if (wParam == 'S') {
			 theApp->camera.Walk(-1.0f);
		}
		else if (wParam == 'D') {
			 theApp->camera.Strafe(1.0f);
		}
		else if (wParam == 'W') {
			 theApp->camera.Walk(1.0f);
		 }
		return 0;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		


		return 0;
	}

	return DefWindowProc(hwd, msg, wParam, lParam);
}

int PCWindows::Run()
{
	MSG msg = { 0 };
	mTimer.Reset();
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mTimer.Tick();
			if (!mAppPause) {
				CalculateFrameStats();
				theApp->Update(mTimer);
				theApp->Draw(mTimer);
			}
			else
			{
				Sleep(100);
			}
		}
	}
	return (int)msg.wParam;
}

void PCWindows::CalculateFrameStats()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;
	if ((mTimer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		wstring fpsStr = to_wstring(fps);
		wstring mspfStr = to_wstring(mspf);

		wstring windowText = mMainWndCaption +
			L"    fps: " + fpsStr +
			L"   mspf: " + mspfStr;

		SetWindowText(mhMainWnd, windowText.c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

