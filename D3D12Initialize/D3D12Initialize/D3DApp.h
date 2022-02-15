#pragma once
#if defined(DEBUG)||defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "GamerTimer.h"
#include "D3DUtil.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"D3D12.lib")
#pragma comment(lib,"dxgi.lib")

class D3DApp {
protected:
	D3DApp(HINSTANCE hInstance);
};
