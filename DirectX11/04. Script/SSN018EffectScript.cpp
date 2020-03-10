#include "stdafx.h"
#include "SSN018EffectScript.h"


CSSN018EffectScript::CSSN018EffectScript():
	CScript((UINT)SCRIPT_TYPE::SSN018EFFECTSCRIPT)
{
}


CSSN018EffectScript::~CSSN018EffectScript()
{
}

void CSSN018EffectScript::UpEffectValue()
{
	if (mIsUp == true)
	{
		mEffectValue += CTimeMgr::GetInst()->GetDeltaTime() * mValueSpeed;
		if (mEffectValue >= 1.0f)
		{
			mEffectValue = 1.0f;
			mIsUp = false;
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &mEffectValue);
	}

}

void CSSN018EffectScript::DownEffectValue()
{
	if (mIsDown == true)
	{
		mEffectValue -= CTimeMgr::GetInst()->GetDeltaTime() * mValueSpeed;
		if (mEffectValue <= 0.0f)
		{
			mEffectValue = 0.0f;
			mIsDown = false;
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &mEffectValue);
	}
}

void CSSN018EffectScript::start()
{
	
	mEffectValue = 0.f;
	mIsUp = false;
	mIsDown = false;
	mValueSpeed = 1.f;

	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &mEffectValue);
}

void CSSN018EffectScript::update()
{
	UpEffectValue();
	DownEffectValue();
}

void CSSN018EffectScript::OperaterEffect(EFFECT_KIND effectKind, EFFECT_OPERATER_KIND effectOperaterKind, float valueSpeed)
{
	if (effectKind == EFFECT_KIND::THUNDER_EFFECT)
	{
		CResPtr<CTexture> texture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Particle\\ThunderParticle.png");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_4, &texture);
	}

	
	if (effectOperaterKind == EFFECT_OPERATER_KIND::UP)
	{
		mIsUp = true;
		mIsDown = false;
	}
	else if (effectOperaterKind == EFFECT_OPERATER_KIND::DOWN)
	{
		mIsDown = true;
		mIsUp = false;
	}


	mValueSpeed = valueSpeed;
}
