#include "stdafx.h"
#include "D3DApp.h"
#include "WindowsFactory.h"
#include "LauncherPCWindow.h"

std::unique_ptr<WindowBase> WindowsFactory::GetPCWindow(D3DApp* theApp,const std::shared_ptr<WindowsInputBase>& windowsInput)
{
	return std::make_unique<PCWindows>(theApp,windowsInput);
}
