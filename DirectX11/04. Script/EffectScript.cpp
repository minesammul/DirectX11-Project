#include "stdafx.h"
#include "EffectScript.h"


CEffectScript::CEffectScript() : 
	CScript((UINT)SCRIPT_TYPE::EFFECTSCRIPT)
{
}


CEffectScript::~CEffectScript()
{
}

void CEffectScript::start()
{
	////임시코드 나중에 Effect는 전부 추가할 수 있도록 한다.
	//CGameObject* newEffect = new CGameObject;
	//CTransform* transform = new CTransform;
	//CAnimator2D* animator2D = new CAnimator2D;
	//CMeshRender* meshrender = new CMeshRender;
	//
	//transform->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	//transform->SetLocalScale(Vec3(100.f, 100.f, 1.f));
	//transform->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	//meshrender->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//meshrender->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));

	//animator2D->AddAnimation(L"Swing Effect", L"Texture\\Effect\\Item Effect\\SwingFX\\", 0.1f);
	//animator2D->PlayAnimation(L"Swing Effect", true);

	//newEffect->AddComponent(transform);
	//newEffect->AddComponent(meshrender);
	//newEffect->AddComponent(animator2D);

	////CSceneMgr::GetInst()->GetCurScene()->AddObject(L"Default", newEffect);

	//CResPtr<CPrefab> pPrefab = new CPrefab(newEffect);
	//CResMgr::GetInst()->AddRes<CPrefab>(L"Swing Effect Prefab", pPrefab);
	//pPrefab->Save();
}
