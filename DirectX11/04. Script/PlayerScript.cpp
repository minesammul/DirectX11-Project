#include "stdafx.h"
#include "PlayerScript.h"
#include "BulletScript.h"
#include "HilightScript.h"

CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, m_pBulletPrefab(nullptr)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::start()
{
	m_pBulletPrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"BulletPrefab");
	m_pOriginMtrl = MeshRender()->GetSharedMaterial();
	m_pCloneMtrl = MeshRender()->GetCloneMaterial();	
}

void CPlayerScript::update()
{
	CGameObject* pObj = Object();
	
	Vec3 vPos = pObj->Transform()->GetLocalPos();
	Vec3 vRot = pObj->Transform()->GetLocalRot();
	
	// 키입력으로 삼각형 움직이기
	if (KEYHOLD(KEY_TYPE::KEY_LEFT))
	{
		//g_vWorldPos.x -= 100.f * DT;
		vPos.x -= 400.f * DT;
		//Animator2D()->PlayAnimation();
	}

	if (KEYHOLD(KEY_TYPE::KEY_RIGHT))
	{
		//g_vWorldPos.x += 100.f * DT;
		vPos.x += 400.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_UP))
	{
		vPos.y += 400.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_DOWN))
	{
		vPos.y -= 400.f * DT;
	}

	if (KEYHOLD(KEY_TYPE::KEY_S))
	{
		//vRot.z -= 1.f * DT;
		CHilightScript* pScript = (CHilightScript*)Object()->GetScript<CHilightScript>();
		pScript->EffectOn();
	}

	pObj->Transform()->SetLocalPos(vPos);
	pObj->Transform()->SetLocalRot(vRot);

	// 미사일 쏘기
	if (KEYTAB(KEY_TYPE::KEY_SPACE))
	{
		// CreateBullet();
		const vector<CGameObject*>& vecChild = Object()->GetChild();		
		for (UINT i = 0; i < vecChild.size(); ++i)
		{
			vecChild[i]->Transform()->SetLocalPos(Vec3(200.f, 0.f, 500.f));
			vecChild[i]->Transform()->SetLocalScale(Vec3(50.f, 50.f, 100.f));

			//ClearChild(i);			
			DeleteObject(vecChild[i]);
		}
	}

	if (KEYTAB(KEY_TYPE::KEY_NUM1))
	{	
		MeshRender()->SetMaterial(m_pCloneMtrl);
		int a = 1;
		if (nullptr != m_pCloneMtrl)
			m_pCloneMtrl->SetData(SHADER_PARAM::INT_0, &a);
	}
	if (KEYTAB(KEY_TYPE::KEY_NUM2))
	{
		MeshRender()->SetMaterial(m_pOriginMtrl);
	}	

	CheckAnim();
}

void CPlayerScript::OnEnable()
{
	int a = 0;
}

void CPlayerScript::OnDisable()
{
	int a = 0;
}

void CPlayerScript::CheckAnim()
{
	return;

	if (KEYTAB(KEY_TYPE::KEY_LEFT))
	{
		Animator2D()->PlayAnimation(L"Player_Left_Walk", true);
	}
	if (KEYTAB(KEY_TYPE::KEY_RIGHT))
	{
		Animator2D()->PlayAnimation(L"Player_Right_Walk", true);
	}
	if (KEYTAB(KEY_TYPE::KEY_UP))
	{
		Animator2D()->PlayAnimation(L"Player_Up_Walk", true);
	}
	if (KEYTAB(KEY_TYPE::KEY_DOWN))
	{
		Animator2D()->PlayAnimation(L"Player_Down_Walk", true);
	}

	/*if (KEYAWAY(KEY_TYPE::KEY_UP) || KEYAWAY(KEY_TYPE::KEY_DOWN) || KEYAWAY(KEY_TYPE::KEY_LEFT) || KEYAWAY(KEY_TYPE::KEY_RIGHT))
	{
		Animator2D()->Pause();
	}*/
}

void CPlayerScript::OnCollisionEnter(CCollider2D * _pOther)
{
	//DeleteObject(_pOther->Object());
	//Animator2D()->PlayAnimation(L"Explosion", true);

	
}



void CPlayerScript::OnCollisionExit(CCollider2D * _pOther)
{
	int a = 10;
}

void CPlayerScript::CreateBullet()
{
	Instantiate(m_pBulletPrefab, Transform()->GetLocalPos(), L"Bullet");
}


