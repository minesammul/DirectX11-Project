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
}
