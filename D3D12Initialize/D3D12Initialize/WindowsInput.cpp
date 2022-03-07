#include "stdafx.h"
#include "WindowsInput.h"



WindowsInput::WindowsInput()
{
	theApp->SetCameraInput(cameraInput.get());
}

LRESULT WindowsInput::MsgProc(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
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
	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			cameraInput->AddCameraSpeed(10.0f);
		}
		else
		{
			cameraInput->AddCameraSpeed(-10.0f);
		}
		return 0;
	case WM_KEYDOWN:
		if ((int)wParam == VK_F2) {
			theApp->Set4xMsaaState(!theApp->Get4xMsaaState());
		}
		else if (wParam == 'A') {
			cameraInput->Strafe(-1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'S') {
			cameraInput->Walk(-1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'D') {
			cameraInput->Strafe(1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'W') {
			cameraInput->Walk(1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'E') {
			cameraInput->UpDown(1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'Q') {
			cameraInput->UpDown(-1.0f * (cameraInput->GetCameraSpeed()));
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
