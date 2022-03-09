#pragma once
#include "GameTimer.h"
class WindowBase
{
public:
	virtual bool InitWindows() =0;
	virtual int Run(GameTimer& gt) = 0;
	bool IsWindowRuning = true;
};

