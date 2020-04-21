#include "stdafx.h"
#include "SSN020DecalEffectScript.h"


CSSN020DecalEffectScript::CSSN020DecalEffectScript() :
	CScript((UINT)SCRIPT_TYPE::SSN020DECALEFFECTSCRIPT)
{
}


CSSN020DecalEffectScript::~CSSN020DecalEffectScript()
{
}

void CSSN020DecalEffectScript::start()
{
	CResPtr<CTexture> texture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Particle\\ThunderParticle.png");
	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &texture);
	mAlphaValue = 0.f;
}

void CSSN020DecalEffectScript::update()
{
	if (mAlphaValue >= 0.f)
	{
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &mAlphaValue);
		mAlphaValue -= CTimeMgr::GetInst()->GetDeltaTime() *0.5f;
	}
	else
	{
		mAlphaValue = 0.f;
	}

}

void CSSN020DecalEffectScript::OnDecalEffect(Vec3 position)
{
	Object()->Transform()->SetLocalPos(position);
	mAlphaValue = 1.f;
}
