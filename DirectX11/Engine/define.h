#pragma once
#define DT TimeMgr::GetInstance()->GetDeltaTime()
#define KEY(eType, eState) (eState == KeyMgr::GetInstance()->GetKeyState(eType))
#define KEYHOLD(eType) KEY(eType, KEY_STATE::STATE_HOLD)
#define KEYTAB(eType)  KEY(eType, KEY_STATE::STATE_TAB)
#define KEYAWAY(eType) KEY(eType, KEY_STATE::STATE_AWAY)
#define KEYNONE(eType) KEY(eType, KEY_STATE::STATE_NONE)
#define MOUSEPOS KeyMgr::GetInstance()->GetMousePos()
#define MAX_LAYER 32
#define CLONE(type) type* Clone() { return new type(*this); }
#define CLONE_DISABLE(type) private: type* Clone(){return nullptr;}

enum class EComponentType
{
	TRANSFORM,  
	MESHRENDER,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	CAMERA,
	END,
	SCRIPT,
};

enum class EResourceType
{
	MESH,
	SHADER,
	TEXTURE,
	MATERIAL,
	SOUND,
	PREFAB,
	END
};