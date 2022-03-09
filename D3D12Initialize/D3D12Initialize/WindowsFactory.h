#pragma once
#include "stdafx.h"
#include "WindowBase.h"
#include "WindowsInputBase.h"
class WindowsFactory
{
public:

	std::unique_ptr<WindowBase> GetPCWindow(D3DApp* theApp, const std::shared_ptr<WindowsInputBase>& windowsInput);
private:

};

