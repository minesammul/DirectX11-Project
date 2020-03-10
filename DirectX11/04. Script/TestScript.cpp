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
	CResPtr<CTexture> texture = CResMgr::GetInst()->FindRes<CTexture>(L"Texture\\Particle\\ThunderParticle.png");
	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_4, &texture);

	effectValue = 0.f;
	isUp = true;
	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &effectValue);
}

void CTestScript::update()
{
	//ControlCamera();

	if (isUp == true)
	{
		effectValue += CTimeMgr::GetInst()->GetDeltaTime();
		if (effectValue >= 1.0f)
		{
			effectValue = 1.0f;
			isUp = false;
		}
	}
	else
	{
		effectValue -= CTimeMgr::GetInst()->GetDeltaTime();
		if (effectValue <= 0.0f)
		{
			effectValue = 0.0f;
			isUp = true;
		}
	}

	Object()->MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::FLOAT_0, &effectValue);
}
