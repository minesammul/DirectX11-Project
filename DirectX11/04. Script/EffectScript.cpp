#include "stdafx.h"
#include "EffectScript.h"


CEffectScript::CEffectScript() : 
	CScript((UINT)SCRIPT_TYPE::EFFECTSCRIPT)
{
	isDestory = false;
}


CEffectScript::~CEffectScript()
{
}

void CEffectScript::start()
{
	if (Object()->Animator2D()->GetCurAnim()->IsPlay() == false)
	{
		Object()->Animator2D()->GetCurAnim()->Play();
	}
}

void CEffectScript::update()
{
	if (isDestory == false)
	{
		Object()->Transform()->SetLocalRot(rotate);

		if (Object()->Animator2D()->GetCurAnim()->IsFinish())
		{
			isDestory = true;
			DeleteObject(Object());
		}
	}
}
