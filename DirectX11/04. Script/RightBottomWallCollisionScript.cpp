#include "stdafx.h"
#include "RightBottomWallCollisionScript.h"
#include "BottomWallCollisionScript.h"
#include "GravityScript.h"


CRightBottomWallCollisionScript::CRightBottomWallCollisionScript() : 
	CScript((UINT)SCRIPT_TYPE::RIGHTBOTTOMWALLCOLLISIONSCRIPT)
{
}


CRightBottomWallCollisionScript::~CRightBottomWallCollisionScript()
{
}

void CRightBottomWallCollisionScript::update()
{

}

void CRightBottomWallCollisionScript::OnCollisionEnter(CCollider2D * _pOther)
{
	collisionPosition = Object()->GetParent()->Transform()->GetLocalPos();

	collisionOn = true;

	vector<CGameObject*> brotherObject = Object()->GetParent()->GetChild();
	for (int brotherIndex = 0; brotherIndex < brotherObject.size(); brotherIndex++)
	{
		vector<CScript*> brotherScripts;
		brotherScripts = brotherObject[brotherIndex]->GetScripts();

		for (int scriptIndex = 0; scriptIndex < brotherScripts.size(); scriptIndex++)
		{
			if (brotherScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::BOTTOMWALLCOLLISIONSCRIPT)
			{
				CBottomWallCollisionScript* bottomWallCollisionScript = dynamic_cast<CBottomWallCollisionScript*>(brotherScripts[scriptIndex]);
				bottomWallCollisionScript->SetCollision(false);
			}
		}
	}
}

void CRightBottomWallCollisionScript::OnCollision(CCollider2D * _pOther)
{
	if (collisionOn == true)
	{
		vector<CScript*> parentScripts;
		parentScripts = Object()->GetParent()->GetScripts();

		for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
		{
			if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
			{
				CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
				gravityScript->SetActiveGravity(false);
			}
		}

		CResPtr<CMesh> pRectMesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
		VTX* pVtx = (VTX*)pRectMesh->GetVtxSysMem();
		DirectX::XMVECTOR objectWorldPos[4];

		Matrix objectWorldMatrix = _pOther->Object()->Transform()->GetWorldMat();
		for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++)
		{
			objectWorldPos[vertexIndex] = DirectX::XMVector3TransformCoord(pVtx[vertexIndex].vPos, objectWorldMatrix);
		}

		//y=(y2-y1/x2-x1)*(x-x1) + y1
		float x1 = objectWorldPos[USE_POINT_INDEX_0].vector4_f32[0];
		float x2 = objectWorldPos[USE_POINT_INDEX_1].vector4_f32[0];
		float y1 = objectWorldPos[USE_POINT_INDEX_0].vector4_f32[1];
		float y2 = objectWorldPos[USE_POINT_INDEX_1].vector4_f32[1];

		float characterPositionX = Object()->GetParent()->Transform()->GetLocalPos().x + Object()->GetParent()->Transform()->GetLocalScale().x/2;
		float x = characterPositionX;

		if (x > x2)
		{
			return;
		}

		float y = ((y2 - y1) / (x2 - x1))*(x - x1) + y1;

		Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
		Vec3 characterScale = Object()->GetParent()->Transform()->GetLocalScale();
		characterPosition.y = y + (Object()->GetParent()->Transform()->GetLocalScale().y / 2) - 5.f;
		Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
	}
}

void CRightBottomWallCollisionScript::OnCollisionExit(CCollider2D * _pOther)
{
	collisionOn = false;

	vector<CScript*> parentScripts;
	parentScripts = Object()->GetParent()->GetScripts();
	for (int scriptIndex = 0; scriptIndex < parentScripts.size(); scriptIndex++)
	{
		if (parentScripts[scriptIndex]->GetScriptType() == (UINT)SCRIPT_TYPE::GRAVITYSCRIPT)
		{
			CGravityScript* gravityScript = dynamic_cast<CGravityScript*>(parentScripts[scriptIndex]);
			gravityScript->SetActiveGravity(true);
		}
	}
}
