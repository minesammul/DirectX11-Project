#include "stdafx.h"
#include "SSN012SkyBoxScript.h"


CSSN012SkyBoxScript::CSSN012SkyBoxScript() : 
	CScript((UINT)SCRIPT_TYPE::SSN012SKYBOXSCRIPT)
{
}


CSSN012SkyBoxScript::~CSSN012SkyBoxScript()
{
}

void CSSN012SkyBoxScript::start()
{
	mUV = Vec2(0.f, 0.f);

	CResPtr<CTexture> skyBoxTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\AllSky_Overcast4_Low.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &skyBoxTexture);
}

void CSSN012SkyBoxScript::update()
{
	mUV.x += CTimeMgr::GetInst()->GetDeltaTime() * 0.01f;
	if (mUV.x >= 1.f)
	{
		mUV.x = 0.f;
	}

	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::VEC2_0, &mUV);
}
