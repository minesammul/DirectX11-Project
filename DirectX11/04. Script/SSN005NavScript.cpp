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
		
		mNavObjectCollisionCheck[objectID] = false;
	}
}

void CSSN005NavScript::update()
{
	map<UINT, bool>::iterator navObjectIter = mNavObjectCollisionCheck.begin();
	while (navObjectIter != mNavObjectCollisionCheck.end())
	{
		if (navObjectIter->second == true)
		{
			mIsNavCollision = true;
			return;
		}

		navObjectIter++;
	}

	mIsNavCollision = false;
}

void CSSN005NavScript::OnCollision(CCollider3D * _pOther)
{
	//충돌지점 이후 위치 정하기
	mBeforePosition = Object()->GetParent()->Transform()->GetLocalPos();

	UINT objectID = _pOther->Object()->GetID();
	mNavObjectCollisionCheck[objectID] = true;

	{
		//월드에 존재하는 삼각형 충돌체로부터 평면의 방정식을 만든다.
		VTX triangleMesh[3] = {};
		triangleMesh[0].vPos = Vec3(-0.5f, 0.5f, 0.f);
		triangleMesh[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
		triangleMesh[0].vUV = Vec2(0.f, 0.f);

		triangleMesh[1].vPos = Vec3(0.5f, 0.5f, 0.f);
		triangleMesh[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
		triangleMesh[1].vUV = Vec2(1.f, 0.f);

		triangleMesh[2].vPos = Vec3(0.5f, -0.5f, 0.f);
		triangleMesh[2].vColor = Vec4(0.5f, 0.5f, 0.f, 1.f);
		triangleMesh[2].vUV = Vec2(1.f, 1.f);

		Matrix matTriangleWorld = _pOther->GetWorldMat();

		Vec3 TriangleWorldPos[3] = {};

		for (UINT i = 0; i < 3; ++i)
		{
			TriangleWorldPos[i] = XMVector3TransformCoord(triangleMesh[i].vPos, matTriangleWorld);
		}

		Vec4 triangleEquation = DirectX::XMPlaneFromPoints(TriangleWorldPos[0], TriangleWorldPos[1], TriangleWorldPos[2]);
		
		Vec3 navCollisionWorldPosition = Object()->Transform()->GetWorldPos();

		float wantDistance = Object()->Transform()->GetLocalScale().x - 100.f;

		float changeYPosition = (wantDistance - triangleEquation.x*navCollisionWorldPosition.x - triangleEquation.z*navCollisionWorldPosition.z - triangleEquation.w) / triangleEquation.y;
		
		Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
		characterPosition.y = changeYPosition;
		Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
	}
}

void CSSN005NavScript::OnCollisionExit(CCollider3D * _pOther)
{
	UINT objectID = _pOther->Object()->GetID();
	mNavObjectCollisionCheck[objectID] = false;
}
