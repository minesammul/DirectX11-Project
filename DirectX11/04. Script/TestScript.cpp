#include "stdafx.h"
#include "TestScript.h"


CTestScript::CTestScript() : 
	CScript((UINT)SCRIPT_TYPE::TESTSCRIPT)
{
}


CTestScript::~CTestScript()
{
}

void CTestScript::update()
{
	CResPtr<CTexture> pSkyBoxTex = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\Sky01.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &pSkyBoxTex);
}
