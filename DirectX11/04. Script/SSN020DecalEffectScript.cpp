#include "stdafx.h"
#include "SSN020DecalEffectScript.h"
#include "FunctionMgr.h"
#include <Light3D.h>


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

	mPointLight = CFunctionMgr::GetInst()->FindObject(L"PointLight1");
	mLightRange = 500.f;
}

void CSSN020DecalEffectScript::update()
{
	if (mAlphaValue >= 0.f)
	{
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &mAlphaValue);
		mAlphaValue -= CTimeMgr::GetInst()->GetDeltaTime() *0.5f;

		mPointLight->Light3D()->SetLightDiffuse(Vec3(mAlphaValue, mAlphaValue, mAlphaValue));
	}
	else
	{
		mAlphaValue = 0.f;
		mLightRange = 0.f;
	}

}

void CSSN020DecalEffectScript::OnDecalEffect(Vec3 position)
{
	Object()->Transform()->SetLocalPos(position);
	mAlphaValue = 1.f;

	mLightRange = 3000.f;

	mPointLight->Transform()->SetLocalPos(position);
	mPointLight->Light3D()->SetLightRange(mLightRange);
	mPointLight->Light3D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
	mPointLight->Light3D()->SetLightSpecular(Vec3(0.0f, 0.0f, 0.0f));
	mPointLight->Light3D()->SetLightAmbient(Vec3(0.0f, 0.0f, 0.0f));
}
