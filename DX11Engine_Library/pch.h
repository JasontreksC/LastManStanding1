#pragma once
#include <iostream>
#include <windows.h>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <math.h>
#include <wrl.h>
#include <algorithm>
#include <cmath>
#include <fstream>



#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")


#include <d2d1.h>
#include <dwrite.h>
#include <d2d1helper.h>
#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")

#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#if _DEBUG
#pragma comment(lib, "DirectXTK_D.lib")
#else
#pragma comment(lib, "DirectXTK_R.lib")
#endif

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_errors.h"
#pragma comment(lib, "fmod_vc.lib")


using namespace std;
using namespace DirectX;
using Microsoft::WRL::ComPtr;

#define SINGLETON(type)\
public:\
static type* GetInst()\
{\
	static type mgr;\
	return &mgr;\
}

#define WINDOW_MAIN \
int WINAPI WinMain( \
HINSTANCE hInstance, \
HINSTANCE hPrevInstance, \
LPSTR pCmdLine, \
int nCmdShow)