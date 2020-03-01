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

void CSSN005NavScript::OnCollisionEnter(CCollider3D * _pOther)
{
	//중력해제

}

void CSSN005NavScript::OnCollision(CCollider3D * _pOther)
{
	//충돌지점 이후 위치 정하기
	beforePosition = Object()->GetParent()->Transform()->GetLocalPos();

	UINT objectID = _pOther->Object()->GetID();
	navObjectCollisionCheck[objectID] = true;

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
		
		Vec3 triangle0to1VectorIsV1 = TriangleWorldPos[1] - TriangleWorldPos[0];
		Vec3 triangle1to2VectorIsV2 = TriangleWorldPos[2] - TriangleWorldPos[1];
		Vec3 triangle2to0VectorIsV3 = TriangleWorldPos[0] - TriangleWorldPos[2];

		Vec3 triangleNormalVector = XMVector3Cross(triangle0to1VectorIsV1, -triangle2to0VectorIsV3);
		triangleNormalVector.Normalize();

		Vec3 navCollisionWorldPosition = Object()->Transform()->GetWorldPos();

		float wantDistance = Object()->Transform()->GetLocalScale().x - 100.f;

		float changeYPosition = (wantDistance - triangleEquation.x*navCollisionWorldPosition.x - triangleEquation.z*navCollisionWorldPosition.z - triangleEquation.w) / triangleEquation.y;
		
		Vec3 characterPosition = Object()->GetParent()->Transform()->GetLocalPos();
		characterPosition.y = changeYPosition;
		Object()->GetParent()->Transform()->SetLocalPos(characterPosition);
	}

	//{
	//	Vec3 colliderPosition = _pOther->Object()->Transform()->GetLocalPos();
	//	Vec3 playerPosition = Object()->GetParent()->Transform()->GetLocalPos();
	//	playerPosition.y = colliderPosition.y;
	//	Object()->GetParent()->Transform()->SetLocalPos(playerPosition);
	//}

}

void CSSN005NavScript::OnCollisionExit(CCollider3D * _pOther)
{
	//중력적용

	UINT objectID = _pOther->Object()->GetID();
	navObjectCollisionCheck[objectID] = false;
}
