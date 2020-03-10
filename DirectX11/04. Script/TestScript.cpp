#include "stdafx.h"
#include "TestScript.h"

#include <Animator3D.h>
#include "FunctionMgr.h"

CTestScript::CTestScript() : 
	CScript((UINT)SCRIPT_TYPE::TESTSCRIPT),
	m_fSpeed(100.f),
	m_fMul(1.f)
{

}


CTestScript::~CTestScript()
{
}

void CTestScript::ControlCamera()
{
	Vec3 vPos = Transform()->GetLocalPos();

	Vec3 vFront = Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
	Vec3 vRight = Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);

	if (KEYHOLD(KEY_TYPE::KEY_W))
	{
		vPos += (vFront * DT * m_fSpeed * m_fMul);
	}
	if (KEYHOLD(KEY_TYPE::KEY_S))
	{
		vPos += (-vFront * DT * m_fSpeed * m_fMul);
	}
	if (KEYHOLD(KEY_TYPE::KEY_A))
	{
		vPos += (-vRight * DT * m_fSpeed * m_fMul);
	}
	if (KEYHOLD(KEY_TYPE::KEY_D))
	{
		vPos += (vRight * DT * m_fSpeed * m_fMul);
	}

	if (KEYHOLD(KEY_TYPE::KEY_RBTN))
	{
		Vec2 vDragDir = CKeyMgr::GetInst()->GetDragDir();

		Vec3 vRot = Transform()->GetLocalRot();
		vRot.y += DT * vDragDir.x * 1.3f;
		vRot.x -= DT * vDragDir.y * 1.3f;
		Transform()->SetLocalRot(vRot);
	}

	if (KEYHOLD(KEY_TYPE::KEY_LSHIFT))
	{
		m_fMul += DT * 5.f;
	}
	if (KEYAWAY(KEY_TYPE::KEY_LSHIFT))
	{
		m_fMul = 1.f;
	}

	Transform()->SetLocalPos(vPos);
}

void CTestScript::start()
{
	mainCamera = CFunctionMgr::GetInst()->FindObject(L"MainCamera");
	Object()->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	Object()->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DistortionMtrl"));
}

void CTestScript::update()
{
	//ControlCamera();

	Vec3 moveDirection = mainCamera->Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
	Vec3 nowPosition = mainCamera->Transform()->GetLocalPos();
	Vec3 changePosition = nowPosition + moveDirection * 200.f;
	Object()->Transform()->SetLocalPos(changePosition);
}
