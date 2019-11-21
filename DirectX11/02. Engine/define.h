#pragma once

#define SINGLE(T) public: static T* GetInst() \
{\
	static T mgr;\
	return &mgr;\
}\
private:\
T();\
~T();

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define SAFE_RELEASE(p) if(nullptr != p ) p->Release();
#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;

#define CLONE(type) type* Clone() { return new type(*this); }
#define CLONE_DISABLE(type) private: type* Clone(){return nullptr;}

#define DT CTimeMgr::GetInst()->GetDeltaTime()
#define KEY(eType, eState) (eState == CKeyMgr::GetInst()->GetKeyState(eType))
#define KEYHOLD(eType) KEY(eType, KEY_STATE::STATE_HOLD)
#define KEYTAB(eType)  KEY(eType, KEY_STATE::STATE_TAB)
#define KEYAWAY(eType) KEY(eType, KEY_STATE::STATE_AWAY)
#define KEYNONE(eType) KEY(eType, KEY_STATE::STATE_NONE)
#define MOUSEPOS CKeyMgr::GetInst()->GetMousePos()

#define MAX_LAYER 32
#define MAX_CAM 32

enum class COMPONENT_TYPE
{
	TRANSFORM,  // ��ġ����(��ġ, ũ��, ȸ��)

	MESHRENDER, // ������

	CAMERA,		// ī�޶�

	LIGHT2D,

	LIGHT3D,	// 3D ����ü

	COLLIDER2D, // 2���� �浹ü

	COLLIDER3D, 

	ANIMATOR2D,

	ANIMATOR3D,		

	END,

	SCRIPT,		// �뺻, ����, 
};

enum class RES_TYPE
{
	MATERIAL,
	PREFAB,
	MESH,
	SHADER,
	TEXTURE,	
	SOUND,		
	END
};

enum class SAMPLER_TYPE
{
	DEFAULT,
	END
};

enum class BLEND_TYPE
{
	DEFAULT,
	ALPHABLEND,
	END,
};

enum class RS_TYPE
{
	CULL_BACK,  // CULL_CCW
	CULL_FRONT, // CULL_CW
	CULL_NONE,  // CULL_NONE
	WIREFRAME,  // CULL_NONE
	END,
};

enum class COLLIDER2D_TYPE
{
	RECT,
	CIRCLE,
	END,
};

enum class SHADER_TYPE
{
	VERTEX_SHADER	= 0x01,
	HULL_SHADER		= 0x02,
	DOMAIN_SHADER	= 0x04,
	GEOMETRY_SHADER = 0x08,
	COMPUTE_SHADER	= 0x10,
	PIXEL_SHADER	= 0x20,
	END,
};

enum class SHADER_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,
	INT_END,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,
	FLOAT_END,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,
	VEC2_END,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,
	VEC4_END,

	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,
	MAT_END,

	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_END,


	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	ADD_CHILD,
	CLEAR_PARANT,
	CLEAR_CHILD,
	ENABLE,
	DISABLE,
	CHANGE_LAYER,
	END,
};

enum class DIR_TYPE
{
	DIR_RIGHT,
	DIR_UP,
	DIR_FRONT,
	END,
};

enum class LIGHT_TYPE
{
	DIRECTIONAL,
	POINT,
	SPOT,
	END,
};

enum class RT_TYPE
{
	SWAPCHAIN,

	DIFFUSE,
	NORMAL,
	POSITION,

	LIGHT,
	SPECULAR,

	SHADOWMAP,

	POSTEFFECT_1,
	POSTEFFECT_2,

	END,
};

enum class MRT_TYPE
{
	SWAPCHAIN, // (SWAPCHAIN), DepthTex
	DEFERRED, // (DIFFUSE, NORMAL, POSIION)  X
	LIGHT,    // (LIGHT, SPECULAR)  X
	SHADOWMAP, // (SHADOWMAP) DepthTex
	POSTEFFECT, // (POSTEFFECT_1, POSTEFFECT_2) X
	END,
};