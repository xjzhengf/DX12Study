#pragma once
#include "WindowsInputBase.h"
class WindowBase
{
public:
	virtual bool InitWindows() =0;
	virtual int Run() = 0;
private:

};

