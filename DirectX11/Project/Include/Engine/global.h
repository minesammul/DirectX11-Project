#pragma once

#define _XM_NO_INTRINSICS_

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#include <vector>
#include <list>
#include <map>

using namespace std;

#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

#include "define.h"
#include "struct.h"

extern tTransform g_transform;
extern tAnim2D g_anim2d;
extern tGlobalValue g_global;

#include "func.h"