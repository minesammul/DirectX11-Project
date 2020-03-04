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
	CResPtr<CTexture> skyBoxTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Skybox\\Sky01.png");
	Object()->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, &skyBoxTexture);
}
