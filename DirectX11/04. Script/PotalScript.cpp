#include "stdafx.h"
#include "PotalScript.h"

#include "Z2FadeScript.h"

CPotalScript::CPotalScript() :
	CScript((UINT)SCRIPT_TYPE::POTALSCRIPT)
{
}


CPotalScript::~CPotalScript()
{
}

void CPotalScript::OnCollisionEnter(CCollider2D * _pOther)
{
	wstring objectName = _pOther->Object()->GetName();

	if (objectName.compare(L"Player") == 0)
	{
		Vec3 playerPosition = _pOther->GetFinalPositon();
		Vec3 potalPosition = Object()->Transform()->GetLocalPos();
		if (playerPosition.x < potalPosition.x)
		{
			//Left to Right
			Vec3 potalRightPosition = potalPosition;
			potalRightPosition.x += Object()->Transform()->GetLocalScale().x / 2;

			Vec3 playerPotalPosition = potalRightPosition;
			playerPotalPosition.x += _pOther->GetFinalScale().x;

			_pOther->Object()->Transform()->SetLocalPos(playerPotalPosition);

		}
		else
		{
			//Right to Left
			Vec3 potalRightPosition = potalPosition;
			potalRightPosition.x -= Object()->Transform()->GetLocalScale().x / 2;

			Vec3 playerPotalPosition = potalRightPosition;
			playerPotalPosition.x -= _pOther->GetFinalScale().x;

			_pOther->Object()->Transform()->SetLocalPos(playerPotalPosition);
		}

		vector<CGameObject*> fadeInOutObject;
		CSceneMgr::GetInst()->GetCurScene()->FindGameObject(L"FadeInOutObject", fadeInOutObject);
		if (fadeInOutObject.empty() == false)
		{
			vector<CScript*> fadeInOutScript = fadeInOutObject[0]->GetScripts();
			if (fadeInOutScript.empty() == false)
			{
				if (fadeInOutScript[0]->GetScriptType() == (UINT)SCRIPT_TYPE::Z2FADESCRIPT)
				{
					CZ2FadeScript* fadeScript = dynamic_cast<CZ2FadeScript*>(fadeInOutScript[0]);
					fadeScript->SetIsStart(true);
				}
			}
		}
	}
}