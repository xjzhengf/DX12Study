#include "stdafx.h"
#include "D3DApp.h"
#include "WindowsFactory.h"
#include "LauncherPCWindow.h"

unique_ptr<WindowBase> WindowsFactory::GetPCWindow(D3DApp* theApp,WindowsInputBase *windowsInput)
{
	return make_unique<PCWindows>(theApp,windowsInput);
}
