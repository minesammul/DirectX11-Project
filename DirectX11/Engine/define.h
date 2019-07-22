#pragma once
#define DT TimeMgr::GetInstance()->GetDeltaTime()
#define KEY(eType, eState) (eState == KeyMgr::GetInstance()->GetKeyState(eType))
#define KEYHOLD(eType) KEY(eType, KEY_STATE::STATE_HOLD)
#define KEYTAB(eType)  KEY(eType, KEY_STATE::STATE_TAB)
#define KEYAWAY(eType) KEY(eType, KEY_STATE::STATE_AWAY)
#define KEYNONE(eType) KEY(eType, KEY_STATE::STATE_NONE)
#define MOUSEPOS KeyMgr::GetInstance()->GetMousePos()

enum class COMPONENT_TYPE
{
	TRNASFORM,  // 위치정보(위치, 크기, 회전)

	MESHRENDER, // 렌더링

	COLLIDER2D,

	COLLIDER3D,

	ANIMATOR2D,

	ANIMATOR3D,

	END,
};