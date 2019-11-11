#include "stdafx.h"
#include "ToolCamScript.h"

#include <Engine/KeyMgr.h>


CToolCamScript::CToolCamScript()
	: CScript(0)
	, m_fSpeed(500.f)
	, m_fMul(1.f)
{
}

CToolCamScript::~CToolCamScript()
{
}

void CToolCamScript::update()
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
		vRot.y += DT * XM_PI * 0.5f * vDragDir.x;
		Transform()->SetLocalRot(vRot);

		// �캤�� ȸ��
		Matrix matAxis = XMMatrixRotationAxis(Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT), DT * XM_PI * 0.5f * -vDragDir.y);
		Transform()->AddLocalRot(matAxis);
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
