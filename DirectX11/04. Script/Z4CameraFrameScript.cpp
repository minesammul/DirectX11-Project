#include "stdafx.h"
#include "Z4CameraFrameScript.h"

#include "Z3CameraBottomCheckScript.h"
#include "Z5CameraTopCheckScript.h"
#include "Z6CameraRightCheckScript.h"
#include "Z7CameraLeftCheckScript.h"


CZ4CameraFrameScript::CZ4CameraFrameScript() : 
	CScript((UINT)SCRIPT_TYPE::Z4CAMERAFRAMESCRIPT)
{
}


CZ4CameraFrameScript::~CZ4CameraFrameScript()
{
}

void CZ4CameraFrameScript::start()
{
	vector<CGameObject*> playerObject;
	CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"Player", playerObject);
	if (playerObject.empty() == false)
	{
		target = playerObject[0];
		beforeTargetPosition = target->Transform()->GetLocalPos();
	}

	vector<CGameObject*> childObject = Object()->GetChild();
	for (int index = 0; index < childObject.size(); index++)
	{
		vector<CScript*> childScript = childObject[index]->GetScripts();
		if (childScript.empty() == false)
		{
			if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z3CAMERABOTTOMCHECKSCRIPT)
			{
				cameraBottomScript = dynamic_cast<CZ3CameraBottomCheckScript*>(childScript[0]);
			}
			else if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z5CAMERATOPCHECKSCRIPT)
			{
				cameraTopScript = dynamic_cast<CZ5CameraTopCheckScript*>(childScript[0]);
			}
			else if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z6CAMERARIGHTCHECKSCRIPT)
			{
				cameraRightScript = dynamic_cast<CZ6CameraRightCheckScript*>(childScript[0]);
			}
			else if (childScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z7CAMERALEFTCHECKSCRIPT)
			{
				cameraLeftScript = dynamic_cast<CZ7CameraLeftCheckScript*>(childScript[0]);
			}
		}
	}
}

void CZ4CameraFrameScript::update()
{
	if (target->IsActive() == true)
	{
		Vec3 cameraFramePosition = Object()->Transform()->GetLocalPos();
		Vec3 targetPosition = target->Transform()->GetLocalPos();

		//bool isBottomCollision = cameraBottomScript->GetIsCollision();
		//if (isBottomCollision == true)
		//{
		//	if (targetPosition.y <= beforeTargetPosition.y)
		//	{

		//	}
		//	else
		//	{
		//		cameraFramePosition.y = targetPosition.y;
		//	}
		//}
		//else
		//{
		//	cameraFramePosition.y = targetPosition.y;
		//}

		//bool isTopCollision = cameraTopScript->GetIsCollision();
		//if (isTopCollision == true)
		//{
		//	if (targetPosition.y >= beforeTargetPosition.y)
		//	{

		//	}
		//	else
		//	{
		//		cameraFramePosition.y = targetPosition.y;
		//	}
		//}
		//else
		//{
		//	cameraFramePosition.y = targetPosition.y;
		//}

		bool isRightCollision = cameraRightScript->GetIsCollision();
		if (isRightCollision == true)
		{
			if (targetPosition.x >= beforeTargetPosition.x)
			{

			}
			else
			{
				cameraFramePosition.x = targetPosition.x;
			}
		}
		else
		{
			cameraFramePosition.x = targetPosition.x;
		}

		bool isLeftCollision = cameraLeftScript->GetIsCollision();
		if (isLeftCollision == true)
		{
			if (targetPosition.x <= beforeTargetPosition.x)
			{

			}
			else
			{
				cameraFramePosition.x = targetPosition.x;
			}
		}
		else
		{
			cameraFramePosition.x = targetPosition.x;
		}

		beforeTargetPosition = targetPosition;

		Object()->Transform()->SetLocalPos(cameraFramePosition);
	}
}
