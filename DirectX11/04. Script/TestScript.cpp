#include "stdafx.h"
#include "TestScript.h"
#include <Animator3D.h>

CTestScript::CTestScript() : 
	CScript((UINT)SCRIPT_TYPE::TESTSCRIPT)
{
	aniIndex = 2;
}


CTestScript::~CTestScript()
{
}

void CTestScript::update()
{
	CResPtr<CTexture> pSkyBoxTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\Sky01.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pSkyBoxTex);

	//int maxAniCount = 25;
	//if (KEYTAB(KEY_TYPE::KEY_NUM0))
	//{
	//	int nowAniIndex = aniIndex % maxAniCount;
	//	nowAniIndex -= 1;
	//	for (int index = 0; index < Object()->GetChild().size(); index++)
	//	{
	//		Object()->GetChild()[index]->Animator3D()->SetClipTime(nowAniIndex, 0.f);
	//		Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(nowAniIndex);
	//	}

	//	aniIndex++;
	//}
	//else if (KEYTAB(KEY_TYPE::KEY_D))
	//{
	//	for (int index = 0; index < Object()->GetChild().size(); index++)
	//	{
	//		Object()->GetChild()[index]->Animator3D()->SetClipTime(2, 0.f);
	//		Object()->GetChild()[index]->Animator3D()->SetCurAnimClip(2);
	//	}
	//}
}
