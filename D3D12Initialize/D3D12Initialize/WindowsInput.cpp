#include "stdafx.h"
#include "WindowsInput.h"
#include "TaskManager.h"


WindowsInput::WindowsInput()
{
	
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
		//������Ϣ��������С���ڴ�С
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		TaskManager::GetTaskManager()->RegisterMouse("RBUTTONDOWN", lParam);
		//cameraInput->OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		
		TaskManager::GetTaskManager()->RegisterMouse("RBUTTONUP", lParam);
		//cameraInput->OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		TaskManager::GetTaskManager()->RegisterMouse("MOUSEMOVE", lParam);
		if ((wParam & MK_LBUTTON) != 0) {
			TaskManager::GetTaskManager()->RegisterMouse("LBUTMOUSEMOVE", lParam);
		}
		if ((wParam & MK_RBUTTON) != 0) {
			TaskManager::GetTaskManager()->RegisterMouse("RBUTMOUSEMOVE", lParam);
		}
		//cameraInput->OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEWHEEL:
		
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			//cameraInput->AddCameraSpeed(10.0f);
			TaskManager::GetTaskManager()->RegisterKey("MOUSEWHEEL_UP");
		}
		else
		{
			TaskManager::GetTaskManager()->RegisterKey("MOUSEWHEEL_DOWN");
			//cameraInput->AddCameraSpeed(-10.0f);
		}
		return 0;
	case WM_KEYDOWN:
	
		//if ((int)wParam == VK_F2) {
		//	theApp->Set4xMsaaState(!theApp->Get4xMsaaState());
		//}
		if (wParam == 'A') {
			TaskManager::GetTaskManager()->RegisterKey("KEYDOWN_A");
		//cameraInput->Strafe(-1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'S') {
		    TaskManager::GetTaskManager()->RegisterKey("KEYDOWN_S");
		//cameraInput->Walk(-1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'D') {
			TaskManager::GetTaskManager()->RegisterKey("KEYDOWN_D");
		//cameraInput->Strafe(1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'W') {
			TaskManager::GetTaskManager()->RegisterKey("KEYDOWN_W");
		//cameraInput->Walk(1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'E') {
			TaskManager::GetTaskManager()->RegisterKey("KEYDOWN_E");
		//cameraInput->UpDown(1.0f * (cameraInput->GetCameraSpeed()));
		}
		else if (wParam == 'Q') {
			TaskManager::GetTaskManager()->RegisterKey("KEYDOWN_Q");
		//cameraInput->UpDown(-1.0f * (cameraInput->GetCameraSpeed()));
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