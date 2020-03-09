#include "stdafx.h"
#include "SSN012SkyBoxScript.h"


CSSN012SkyBoxScript::CSSN012SkyBoxScript() :
	CScript((UINT)SCRIPT_TYPE::SSN012SKYBOXSCRIPT)
{
}


CSSN012SkyBoxScript::~CSSN012SkyBoxScript()
{
}


void CSSN012SkyBoxScript::BlendTexture()
{
	if (mIsBlendStart == true)
	{
		float value = CTimeMgr::GetInst()->GetDeltaTime() * mBlendSpeed;

		mBlendRatio.x -= value;
		mBlendRatio.y += value;

		if (mBlendRatio.x <= 0.f || mBlendRatio.y >= 1.f)
		{
			mBlendRatio.x = 1.f;
			mBlendRatio.y = 0.f;

			mBeforeTexture = mAfterTexture;
			Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &mBeforeTexture);

			mIsBlendStart = false;
		}

		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::VEC2_1, &mBlendRatio);
	}

}

void CSSN012SkyBoxScript::MoveUV()
{
	mUV.x += CTimeMgr::GetInst()->GetDeltaTime() * mUVSpeed;
	if (mUV.x >= 1.f)
	{
		mUV.x = mUV.x - 1.f;
	}

	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::VEC2_0, &mUV);
}

void CSSN012SkyBoxScript::start()
{
	mUV = Vec2(0.f, 0.f);
	mUVSpeed = 0.01f;

	mBlendRatio = Vec2(1.f, 0.f);
	mIsBlendStart = false;
	mBlendSpeed = 0.1f;

	mBeforeTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\AllSky_Overcast4_Low.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &mBeforeTexture);

	mAfterTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\Epic_GloriousPink_EquiRect.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, &mAfterTexture);

	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::VEC2_0, &mUV);
	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::VEC2_1, &mBlendRatio);
}

void CSSN012SkyBoxScript::update()
{
	MoveUV();
	BlendTexture();
}

void CSSN012SkyBoxScript::StartBlendSky(CResPtr<CTexture> blendTexture, float blendSpeed)
{
	mIsBlendStart = true;
	mBlendSpeed = blendSpeed;

	mAfterTexture = blendTexture;
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_1, &mAfterTexture);
}
