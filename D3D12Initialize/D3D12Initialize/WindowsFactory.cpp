#include "stdafx.h"
#include "WindowsFactory.h"
#include "LauncherPCWindow.h"

std::shared_ptr<WindowBase> WindowsFactory::GetPCWindow(const std::shared_ptr<WindowsInputBase>& windowsInput)
{
	return std::make_shared<PCWindows>(windowsInput);
}
