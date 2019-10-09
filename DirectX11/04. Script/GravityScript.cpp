#include "stdafx.h"
#include "GravityScript.h"


CGravityScript::CGravityScript():
	CScript((UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
{
	nowGravityValue = GRAVITY_VALUE;
}


CGravityScript::~CGravityScript()
{
}

void CGravityScript::update()
{
	nowGravityValue += GRAVITY_VALUE;

	Vec3 objectPosition = Object()->Transform()->GetLocalPos();
	objectPosition.y -= nowGravityValue * DT;
	Object()->Transform()->SetLocalPos(objectPosition);
}
