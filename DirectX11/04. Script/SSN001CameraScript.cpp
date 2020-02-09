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
	{
		vector<CGameObject*> findObject;
		CSceneMgr::GetInst()->FindGameObject(L"MainCameraArm", findObject);
		Vec3 vPos = findObject[0]->Transform()->GetWorldPos();

		Transform()->SetLocalPos(vPos);
	}

	{
		vector<CGameObject*> findArm;
		CSceneMgr::GetInst()->FindGameObject(L"MainCameraArm", findArm);

		vector<CGameObject*> findBody;
		CSceneMgr::GetInst()->FindGameObject(L"MainCameraBody", findBody);

		Vec3 mainCameraBodyPosition = findBody[0]->Transform()->GetWorldPos();
		Vec3 cameraLookDirection = mainCameraBodyPosition - findArm[0]->Transform()->GetWorldPos();

		if (-0.1f <= cameraLookDirection.z && cameraLookDirection.z <= 0.1f)
		{
			cameraLookDirection.z = 1.f;
		}

		Transform()->SetLookAt(cameraLookDirection);
	}


	//Vec3 vFront = Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);
	//Vec3 vRight = Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);

	//if (KEYHOLD(KEY_TYPE::KEY_W))
	//{
	//	vPos += (vFront * DT * m_fSpeed * m_fMul);
	//}
	//if (KEYHOLD(KEY_TYPE::KEY_S))
	//{
	//	vPos += (-vFront * DT * m_fSpeed * m_fMul);
	//}
	//if (KEYHOLD(KEY_TYPE::KEY_A))
	//{
	//	vPos += (-vRight * DT * m_fSpeed * m_fMul);
	//}
	//if (KEYHOLD(KEY_TYPE::KEY_D))
	//{
	//	vPos += (vRight * DT * m_fSpeed * m_fMul);
	//}

	//if (KEYHOLD(KEY_TYPE::KEY_RBTN))
	//{
	//	Vec2 vDragDir = CKeyMgr::GetInst()->GetDragDir();

	//	Vec3 vRot = Transform()->GetLocalRot();
	//	vRot.y += DT * XM_PI * 0.5f * vDragDir.x;
	//	vRot.z = 0.f;

	//	Transform()->SetLocalRot(vRot);

	//	// ¿ìº¤ÅÍ È¸Àü
	//	Matrix matAxis = XMMatrixRotationAxis(Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT), DT * XM_PI * 0.5f * -vDragDir.y);
	//	Transform()->AddLocalRot(matAxis);
	//}

	//if (KEYHOLD(KEY_TYPE::KEY_LSHIFT))
	//{
	//	m_fMul += DT * 5.f;
	//}
	//if (KEYAWAY(KEY_TYPE::KEY_LSHIFT))
	//{
	//	m_fMul = 1.f;
	//}


}
