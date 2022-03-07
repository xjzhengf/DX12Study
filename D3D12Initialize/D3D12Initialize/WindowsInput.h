#pragma once
#include "stdafx.h"
#include "WindowsInputBase.h"
#include "D3DApp.h"
#include "CameraInput.h"
class WindowsInput : public WindowsInputBase{
public:
	WindowsInput();
	LRESULT MsgProc(HWND hwd, UINT msg, WPARAM wParam, LPARAM lParam) override;
private:
	D3DApp* theApp = D3DApp::GetApp();
	shared_ptr<Camera> cameraInput = make_shared<CameraMove>();
};