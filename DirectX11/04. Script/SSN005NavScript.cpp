#include "stdafx.h"
#include "SSN005NavScript.h"


CSSN005NavScript::CSSN005NavScript():
	CScript((UINT)SCRIPT_TYPE::SSN005NAVSCRIPT)
{
}


CSSN005NavScript::~CSSN005NavScript()
{
}

void CSSN005NavScript::start()
{
	CLayer* navObjectLayer = CSceneMgr::GetInst()->GetCurScene()->FindLayer(L"NavMesh");

	for (int index = 0; index < navObjectLayer->GetParentObject().size(); index++)
	{
		UINT objectID = navObjectLayer->GetParentObject()[index]->GetID();
		
		navObjectCollisionCheck[objectID] = false;
	}
}

void CSSN005NavScript::update()
{
	map<UINT, bool>::iterator navObjectIter = navObjectCollisionCheck.begin();
	while (navObjectIter != navObjectCollisionCheck.end())
	{
		if (navObjectIter->second == true)
		{
			isNavCollision = true;
			return;
		}

		navObjectIter++;
	}

	isNavCollision = false;
}

void CSSN005NavScript::OnCollision(CCollider3D * _pOther)
{
	beforePosition = Object()->GetParent()->Transform()->GetLocalPos();

	UINT objectID = _pOther->Object()->GetID();
	navObjectCollisionCheck[objectID] = true;
}

void CSSN005NavScript::OnCollisionExit(CCollider3D * _pOther)
{
	UINT objectID = _pOther->Object()->GetID();
	navObjectCollisionCheck[objectID] = false;
}
