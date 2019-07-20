#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#include "define.h"
#include "struct.h"


#include <WrapCriticalSection.h>

#ifdef _DEBUG
#pragma comment(lib, "CoreLib_Debug.lib")
#else
#pragma comment(lib, "CoreLib.lib")
#endif