#include "stdafx.h"
#include "PotalVerticalScript.h"

#include "Z2FadeScript.h"

CPotalVerticalScript::CPotalVerticalScript():
	CScript((UINT)SCRIPT_TYPE::POTALVERTICALSCRIPT)
{
}


CPotalVerticalScript::~CPotalVerticalScript()
{
}

void CPotalVerticalScript::OnCollisionEnter(CCollider2D * _pOther)
{
	wstring objectName = _pOther->Object()->GetName();

	if (objectName.compare(L"Player") == 0)
	{
		Vec3 playerPosition = _pOther->GetFinalPositon();
		Vec3 potalPosition = Object()->Transform()->GetLocalPos();
		if (playerPosition.y < potalPosition.y)
		{
			//Bottom to Top
			Vec3 potalRightPosition = potalPosition;
			potalRightPosition.y += Object()->Transform()->GetLocalScale().y / 2;

			Vec3 playerPotalPosition = potalRightPosition;
			playerPotalPosition.y += _pOther->GetFinalScale().y;

			_pOther->Object()->Transform()->SetLocalPos(playerPotalPosition);

		}
		else
		{
			//Top to Bottom
			Vec3 potalRightPosition = potalPosition;
			potalRightPosition.y -= Object()->Transform()->GetLocalScale().y / 2;

			Vec3 playerPotalPosition = potalRightPosition;
			playerPotalPosition.y -= _pOther->GetFinalScale().y;

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
