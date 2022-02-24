#include "stdafx.h"
#include "D3DApp.h"
#include "WindowsFactory.h"
#include "WinMain.h"
unique_ptr<WindowBase> WindowsFactory::GetPCWindow(D3DApp* theApp)
{
	return make_unique<PCWindows>(theApp);
}
