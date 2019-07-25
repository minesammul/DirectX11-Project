#pragma once
#define DT TimeMgr::GetInstance()->GetDeltaTime()
#define KEY(eType, eState) (eState == KeyMgr::GetInstance()->GetKeyState(eType))
#define KEYHOLD(eType) KEY(eType, KEY_STATE::STATE_HOLD)
#define KEYTAB(eType)  KEY(eType, KEY_STATE::STATE_TAB)
#define KEYAWAY(eType) KEY(eType, KEY_STATE::STATE_AWAY)
#define KEYNONE(eType) KEY(eType, KEY_STATE::STATE_NONE)
#define MOUSEPOS KeyMgr::GetInstance()->GetMousePos()
#define MAX_LAYER 32

enum class EComponentType
{
	TRANSFORM,  
	MESHRENDER,
	COLLIDER2D,
	COLLIDER3D,
	ANIMATOR2D,
	ANIMATOR3D,
	SCRIPT,
	CAMERA,
	END,
};

enum class EResourceType
{
	MESH,
	SHADER,
	TEXTURE,
	MATERIAL,
	SOUND,
	END
};