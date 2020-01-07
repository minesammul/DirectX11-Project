#include "stdafx.h"
#include "SSN001CameraScript.h"


CSSN001CameraScript::CSSN001CameraScript():
	CScript((UINT)SCRIPT_TYPE::SSN001CAMERASCRIPT),
	m_fSpeed(100.f),
	m_fMul(1.f)
{
}


CSSN001CameraScript::~CSSN001CameraScript()
{
}

void CSSN001CameraScript::update()
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
		vRot.z = 0.f;

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