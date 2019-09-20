#include "stdafx.h"
#include "BulletScript.h"

CBulletScript::CBulletScript()
	: CScript((UINT)SCRIPT_TYPE::BULLETSCRIPT)
	, m_fSpeed(200.f)	
{
}

CBulletScript::~CBulletScript()
{
}

void CBulletScript::update()
{
	Vec3 vPos = Transform()->GetLocalPos();

	vPos.y += m_fSpeed * DT;

	Transform()->SetLocalPos(vPos);
}
