#pragma once
#include "stdafx.h"
#include "WindowBase.h"
class WindowsFactory
{
public:

	unique_ptr<WindowBase> GetPCWindow(D3DApp* theApp);
private:

};

