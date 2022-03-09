#pragma once
#include "stdafx.h"
#include "WindowBase.h"
#include "WindowsInputBase.h"
class WindowsFactory
{
public:

	std::shared_ptr<WindowBase> GetPCWindow( const std::shared_ptr<WindowsInputBase>& windowsInput);
private:

};

