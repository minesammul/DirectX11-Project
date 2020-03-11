#include "stdafx.h"
#include "SSN017InOutsideScript.h"


CSSN017InOutsideScript::CSSN017InOutsideScript():
	CScript((UINT)SCRIPT_TYPE::SSN017INOUTSIDESCRIPT)
{
}


CSSN017InOutsideScript::~CSSN017InOutsideScript()
{
}

void CSSN017InOutsideScript::start()
{
	if (Object()->GetName().find(L"ToInside") != wstring::npos)
	{
		Object()->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"UIMtrl"));

		float alpha = 0.6f;
		CResPtr<CTexture> texture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\UI\\Inside.png");
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &alpha);
		Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, &texture);
	}
}

void CSSN017InOutsideScript::OffInOutMesh()
{
	Object()->Active(false);
}
