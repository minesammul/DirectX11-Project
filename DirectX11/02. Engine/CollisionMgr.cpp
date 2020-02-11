#include "stdafx.h"
#include "CollisionMgr.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"

#include "GameObject.h"
#include "Collider2D.h"
#include "Collider3D.h"

#include "ResMgr.h"


CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; ++j)
		{
			if (m_arrCheck[i] & (1 << j))
			{
				// i ObjTYpe, j ObjType 충돌 진행
				CollisionGroup(i, j);
			}
		}
	}
}

bool CCollisionMgr::IsCollisionLayers(const wstring & _strLayerName1, const wstring & _strLayerName2)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeftLayer = pCurScene->FindLayer(_strLayerName1);
	CLayer* pRightLayer = pCurScene->FindLayer(_strLayerName2);

	assert(!(nullptr == pLeftLayer || nullptr == pRightLayer));

	UINT iIdx = (UINT)(pLeftLayer->GetLayerIdx() < pRightLayer->GetLayerIdx() ? pLeftLayer->GetLayerIdx() : pRightLayer->GetLayerIdx());
	UINT iBitIdx = iIdx == (UINT)pLeftLayer->GetLayerIdx() ? (UINT)pRightLayer->GetLayerIdx() : (UINT)pLeftLayer->GetLayerIdx();
	
	bool layerCollision = false;
	if (m_arrCheck[iIdx] & (1 << iBitIdx))
	{
		layerCollision = true;
	}

	return layerCollision;
}

void CCollisionMgr::CollisionUnCheck(const wstring & _strLayerName1, const wstring & _strLayerName2)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeftLayer = pCurScene->FindLayer(_strLayerName1);
	CLayer* pRightLayer = pCurScene->FindLayer(_strLayerName2);

	assert(!(nullptr == pLeftLayer || nullptr == pRightLayer));

	UINT iIdx = (UINT)(pLeftLayer->GetLayerIdx() < pRightLayer->GetLayerIdx() ? pLeftLayer->GetLayerIdx() : pRightLayer->GetLayerIdx());
	UINT iBitIdx = iIdx == (UINT)pLeftLayer->GetLayerIdx() ? (UINT)pRightLayer->GetLayerIdx() : (UINT)pLeftLayer->GetLayerIdx();
	
	m_arrCheck[iIdx] &= (0 << iBitIdx);
}

void CCollisionMgr::CollisionGroup(int _leftIdx, int _rightIdx)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CGameObject*>& vecLeft = pCurScene->GetLayer(_leftIdx)->GetAllObject();
	const vector<CGameObject*>& vecRight = pCurScene->GetLayer(_rightIdx)->GetAllObject();

	COL_ID colID;

	for (UINT i = 0; i < vecLeft.size(); ++i)
	{
		for (UINT j = 0; j < vecRight.size(); ++j)
		{
			// 2D 두 오브젝트 중에서 충돌체가 없는 경우
			if (vecLeft[i]->Collider2D() == nullptr || vecRight[j]->Collider2D() == nullptr)
			{
				//continue;
			}
			else
			{
				colID.left = vecLeft[i]->Collider2D()->GetID();
				colID.right = vecRight[j]->Collider2D()->GetID();

				map<unsigned long long, bool>::iterator iter = m_mapID2D.find(colID.ID);

				if (IsCollision(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D()))
				{
					// 충돌 했다.
					if (iter == m_mapID2D.end())
					{
						// 충돌 조합 등록된적 없음 ==> 충돌한적 없음					
						vecLeft[i]->Collider2D()->OnCollisionEnter(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->OnCollisionEnter(vecLeft[i]->Collider2D());
						m_mapID2D.insert(make_pair(colID.ID, true));
					}
					else if (false == iter->second)
					{
						// 이전에 충돌하지 않고 있었다.
						vecLeft[i]->Collider2D()->OnCollisionEnter(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->OnCollisionEnter(vecLeft[i]->Collider2D());
						iter->second = true;
					}
					else {
						// 충돌 중이다.
						vecLeft[i]->Collider2D()->OnCollision(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->OnCollision(vecLeft[i]->Collider2D());
					}
				}
				else // 충돌하지 않고 있다.
				{
					if (iter != m_mapID2D.end() && true == iter->second)
					{
						// 이전에는 충돌 중이었다. ==>이번에 떨어진 상황
						vecLeft[i]->Collider2D()->OnCollisionExit(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->OnCollisionExit(vecLeft[i]->Collider2D());
						iter->second = false;
					}
				}
			}
			
			// 3D 오브젝트가 충돌하지 않는 경우와 충돌하는 경우
			if (vecLeft[i]->Collider3D() == nullptr || vecRight[j]->Collider3D() == nullptr)
			{
				continue;
			}
			else
			{
				colID.left = vecLeft[i]->Collider3D()->GetID();
				colID.right = vecRight[j]->Collider3D()->GetID();

				map<unsigned long long, bool>::iterator iter = m_mapID3D.find(colID.ID);

				if (IsCollision(vecLeft[i]->Collider3D(), vecRight[j]->Collider3D()))
				{
					// 충돌 했다.
					if (iter == m_mapID3D.end())
					{
						// 충돌 조합 등록된적 없음 ==> 충돌한적 없음					
						vecLeft[i]->Collider3D()->OnCollisionEnter(vecRight[j]->Collider3D());
						vecRight[j]->Collider3D()->OnCollisionEnter(vecLeft[i]->Collider3D());
						m_mapID3D.insert(make_pair(colID.ID, true));
					}
					else if (false == iter->second)
					{
						// 이전에 충돌하지 않고 있었다.
						vecLeft[i]->Collider3D()->OnCollisionEnter(vecRight[j]->Collider3D());
						vecRight[j]->Collider3D()->OnCollisionEnter(vecLeft[i]->Collider3D());
						iter->second = true;
					}
					else {
						// 충돌 중이다.
						vecLeft[i]->Collider3D()->OnCollision(vecRight[j]->Collider3D());
						vecRight[j]->Collider3D()->OnCollision(vecLeft[i]->Collider3D());
					}
				}
				else // 충돌하지 않고 있다.
				{
					if (iter != m_mapID3D.end() && true == iter->second)
					{
						// 이전에는 충돌 중이었다. ==>이번에 떨어진 상황
						vecLeft[i]->Collider3D()->OnCollisionExit(vecRight[j]->Collider3D());
						vecRight[j]->Collider3D()->OnCollisionExit(vecLeft[i]->Collider3D());
						iter->second = false;
					}
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider2D * _pLeft, CCollider2D * _pRight)
{
	if (_pLeft->GetCollider2DType() == COLLIDER2D_TYPE::RECT && _pRight->GetCollider2DType() == COLLIDER2D_TYPE::RECT)
	{
		// Rect Rect 충돌
		return CollisionRect(_pLeft, _pRight);
	}
	else if (_pLeft->GetCollider2DType() == COLLIDER2D_TYPE::CIRCLE && _pRight->GetCollider2DType() == COLLIDER2D_TYPE::CIRCLE)
	{
		// Circle Circle

	}
	else
	{
		// Rect, Circle
	}

	return false;
}

bool CCollisionMgr::CollisionRect(CCollider2D * _pLeft, CCollider2D * _pRight)
{
	static CResPtr<CMesh> pRectMesh = CResMgr::GetInst()->FindRes<CMesh>(L"ColliderRectMesh");

	Matrix matLeftWorld = _pLeft->GetWorldMat();
	Matrix matRightWorld = _pRight->GetWorldMat();

	VTX* pVtx = (VTX*)pRectMesh->GetVtxSysMem();

	Vec3 vLeftWorldPos[4] = {};
	Vec3 vRightWorldPos[4] = {};	   

	for (UINT i = 0; i < 4; ++i)
	{
		vLeftWorldPos[i] = XMVector3TransformCoord(pVtx[i].vPos, matLeftWorld);
		vLeftWorldPos[i].z = 0.f;
	}

	for (UINT i = 0; i < 4; ++i)
	{
		vRightWorldPos[i] = XMVector3TransformCoord(pVtx[i].vPos, matRightWorld);
		vRightWorldPos[i].z = 0.f;
	}

	Vec3 vLeftCenter = (vLeftWorldPos[3] + vLeftWorldPos[0]) / 2.f;
	Vec3 vRightCenter = (vRightWorldPos[3] + vRightWorldPos[0]) / 2.f;

	Vec3 vCenter = vLeftCenter - vRightCenter;

	Vec3 vProj[4] = {};
	Vec3 vAxis[4] = {};

	vProj[0] = vLeftWorldPos[0] - vLeftWorldPos[2];
	vAxis[0] = vProj[0];	

	vProj[1] = vLeftWorldPos[3] - vLeftWorldPos[2];
	vAxis[1] = vProj[1];	

	vProj[2] = vRightWorldPos[0] - vRightWorldPos[2];
	vAxis[2] = vProj[2];	

	vProj[3] = vRightWorldPos[3] - vRightWorldPos[2];
	vAxis[3] = vProj[3];
	
	for (UINT i = 0; i < 4; ++i)
	{
		if (vAxis[i] == Vec3::Zero)
			return false;

		vAxis[i].Normalize();
	}

	float fSum = 0.f;

	for (UINT i = 0; i < 4; ++i)
	{
		fSum = 0.f;
		for (UINT j = 0; j < 4; ++j)
		{
			fSum += abs(vProj[j].Dot(vAxis[i]));
		}

		// 충돌체 각 변을 투영시킨 거리의 절반
		fSum /= 2.f;

		// 중심을 이은 벡터를 투영시킨 거리
		float fDist = abs(vCenter.Dot(vAxis[i]));
		
		if (fDist > fSum)
			return false;
	}

	return true;
}

bool CCollisionMgr::CollisionCircle(CCollider2D * _pLeft, CCollider2D * _pRight)
{
	Matrix matLeftWorld = _pLeft->GetWorldMat();
	Matrix matRightWorld = _pRight->GetWorldMat();



	return false;
}

bool CCollisionMgr::IsCollision(CCollider3D * _pLeft, CCollider3D * _pRight)
{
	if (_pLeft->GetCollider3DType() == COLLIDER3D_TYPE::CUBE && _pRight->GetCollider3DType() == COLLIDER3D_TYPE::CUBE)
	{
		// Rect Rect 충돌
		return CollisionCube(_pLeft, _pRight);
	}
	else if (_pLeft->GetCollider3DType() == COLLIDER3D_TYPE::SPHERE && _pRight->GetCollider3DType() == COLLIDER3D_TYPE::SPHERE)
	{
		// Circle Circle
		return CollisionSphere(_pLeft, _pRight);
	}
	else
	{
		// Rect, Circle
	}

	return false;
}


bool CCollisionMgr::CollisionCube(CCollider3D * _pLeft, CCollider3D * _pRight)
{
	static CResPtr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh");

	Matrix matLeftWorld = _pLeft->GetWorldMat();
	Matrix matRightWorld = _pRight->GetWorldMat();

	//VTX* pVtx = (VTX*)pMesh->GetVtxSysMem();
	VTX arrCube[24] = {};

	// 윗면
	arrCube[0].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[0].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[0].vUV = Vec2(0.f, 0.f);
	arrCube[0].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[1].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[1].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[1].vUV = Vec2(0.f, 0.f);
	arrCube[1].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[2].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[2].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[2].vUV = Vec2(0.f, 0.f);
	arrCube[2].vNormal = Vec3(0.f, 1.f, 0.f);

	arrCube[3].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[3].vColor = Vec4(1.f, 1.f, 1.f, 1.f);
	arrCube[3].vUV = Vec2(0.f, 0.f);
	arrCube[3].vNormal = Vec3(0.f, 1.f, 0.f);


	// 아랫 면	
	arrCube[4].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[4].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[4].vUV = Vec2(0.f, 0.f);
	arrCube[4].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[5].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[5].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[5].vUV = Vec2(0.f, 0.f);
	arrCube[5].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[6].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[6].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[6].vUV = Vec2(0.f, 0.f);
	arrCube[6].vNormal = Vec3(0.f, -1.f, 0.f);

	arrCube[7].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[7].vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	arrCube[7].vUV = Vec2(0.f, 0.f);
	arrCube[7].vNormal = Vec3(0.f, -1.f, 0.f);

	// 왼쪽 면
	arrCube[8].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[8].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[8].vUV = Vec2(0.f, 0.f);
	arrCube[8].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[9].vPos = Vec3(-0.5f, 0.5f, -0.5f);
	arrCube[9].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[9].vUV = Vec2(0.f, 0.f);
	arrCube[9].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[10].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[10].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[10].vUV = Vec2(0.f, 0.f);
	arrCube[10].vNormal = Vec3(-1.f, 0.f, 0.f);

	arrCube[11].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[11].vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	arrCube[11].vUV = Vec2(0.f, 0.f);
	arrCube[11].vNormal = Vec3(-1.f, 0.f, 0.f);

	// 오른쪽 면
	arrCube[12].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[12].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[12].vUV = Vec2(0.f, 0.f);
	arrCube[12].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[13].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[13].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[13].vUV = Vec2(0.f, 0.f);
	arrCube[13].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[14].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[14].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[14].vUV = Vec2(0.f, 0.f);
	arrCube[14].vNormal = Vec3(1.f, 0.f, 0.f);

	arrCube[15].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[15].vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	arrCube[15].vUV = Vec2(0.f, 0.f);
	arrCube[15].vNormal = Vec3(1.f, 0.f, 0.f);

	// 뒷 면
	arrCube[16].vPos = Vec3(0.5f, 0.5f, 0.5f);
	arrCube[16].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[16].vUV = Vec2(0.f, 0.f);
	arrCube[16].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[17].vPos = Vec3(-0.5f, 0.5f, 0.5f);
	arrCube[17].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[17].vUV = Vec2(0.f, 0.f);
	arrCube[17].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[18].vPos = Vec3(-0.5f, -0.5f, 0.5f);
	arrCube[18].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[18].vUV = Vec2(0.f, 0.f);
	arrCube[18].vNormal = Vec3(0.f, 0.f, 1.f);

	arrCube[19].vPos = Vec3(0.5f, -0.5f, 0.5f);
	arrCube[19].vColor = Vec4(1.f, 1.f, 0.f, 1.f);
	arrCube[19].vUV = Vec2(0.f, 0.f);
	arrCube[19].vNormal = Vec3(0.f, 0.f, 1.f);

	// 앞 면
	arrCube[20].vPos = Vec3(-0.5f, 0.5f, -0.5f);;
	arrCube[20].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[20].vUV = Vec2(0.f, 0.f);
	arrCube[20].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[21].vPos = Vec3(0.5f, 0.5f, -0.5f);
	arrCube[21].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[21].vUV = Vec2(0.f, 0.f);
	arrCube[21].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[22].vPos = Vec3(0.5f, -0.5f, -0.5f);
	arrCube[22].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[22].vUV = Vec2(0.f, 0.f);
	arrCube[22].vNormal = Vec3(0.f, 0.f, -1.f);

	arrCube[23].vPos = Vec3(-0.5f, -0.5f, -0.5f);
	arrCube[23].vColor = Vec4(1.f, 0.f, 1.f, 1.f);
	arrCube[23].vUV = Vec2(0.f, 0.f);
	arrCube[23].vNormal = Vec3(0.f, 0.f, -1.f);

	Vec3 vLeftWorldPos[24] = {};
	Vec3 vRightWorldPos[24] = {};

	for (UINT i = 0; i < 24; ++i)
	{
		vLeftWorldPos[i] = XMVector3TransformCoord(arrCube[i].vPos, matLeftWorld);
	}

	for (UINT i = 0; i < 24; ++i)
	{
		vRightWorldPos[i] = XMVector3TransformCoord(arrCube[i].vPos, matRightWorld);
	}

	Vec3 vLeftCenter = (vLeftWorldPos[0] + vLeftWorldPos[5]) / 2.f;
	Vec3 vRightCenter = (vRightWorldPos[0] + vRightWorldPos[5]) / 2.f;

	Vec3 vCenter = vLeftCenter - vRightCenter;

	Vec3 vProj[6] = {};
	Vec3 vAxis[6] = {};

	vProj[0] = vLeftWorldPos[0] - vLeftWorldPos[1];
	vAxis[0] = vProj[0];

	vProj[1] = vLeftWorldPos[0] - vLeftWorldPos[3];
	vAxis[1] = vProj[1];

	vProj[2] = vLeftWorldPos[0] - vLeftWorldPos[7];
	vAxis[2] = vProj[2];

	vProj[3] = vRightWorldPos[0] - vRightWorldPos[1];
	vAxis[3] = vProj[3];

	vProj[4] = vRightWorldPos[0] - vRightWorldPos[3];
	vAxis[4] = vProj[4];

	vProj[5] = vRightWorldPos[0] - vRightWorldPos[7];
	vAxis[5] = vProj[5];

	for (UINT i = 0; i < 6; ++i)
	{
		if (vAxis[i] == Vec3::Zero)
			return false;

		vAxis[i].Normalize();
	}

	float fSum = 0.f;

	for (UINT i = 0; i < 6; ++i)
	{
		fSum = 0.f;
		for (UINT j = 0; j < 6; ++j)
		{
			fSum += abs(vProj[j].Dot(vAxis[i]));
		}

		// 충돌체 각 변을 투영시킨 거리의 절반
		fSum /= 2.f;

		// 중심을 이은 벡터를 투영시킨 거리
		float fDist = abs(vCenter.Dot(vAxis[i]));

		if (fDist > fSum)
			return false;
	}

	return true;
}

bool CCollisionMgr::CollisionSphere(CCollider3D * _pLeft, CCollider3D * _pRight)
{
	Vec3 leftScale = _pLeft->GetFinalScale();
	Vec3 rightScale = _pRight->GetFinalScale();
	float leftRightRadius = leftScale.x + rightScale.x;


	Vec3 leftPosition = _pLeft->GetFinalPositon();
	Vec3 rightPosition = _pRight->GetFinalPositon();

	Vec3 distanceVector = leftPosition - rightPosition;
	float distance = distanceVector.Length();
	if (distance <= leftRightRadius)
	{
		return true;
	}
	

	return false;
}

void CCollisionMgr::CollisionCheck(const wstring & _strLayerName1, const wstring & _strLayerName2)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeftLayer = pCurScene->FindLayer(_strLayerName1);
	CLayer* pRightLayer = pCurScene->FindLayer(_strLayerName2);

	assert(!(nullptr == pLeftLayer || nullptr == pRightLayer));

	CollisionCheck(pLeftLayer->GetLayerIdx(), pRightLayer->GetLayerIdx());
}

void CCollisionMgr::CollisionCheck(int _iLayerIdx1, int _iLayerIdx2)
{
	// 배열의 인덱스
	UINT iIdx = (UINT)(_iLayerIdx1 < _iLayerIdx2 ? _iLayerIdx1 : _iLayerIdx2);
	UINT iBitIdx = iIdx == (UINT)_iLayerIdx1 ? (UINT)_iLayerIdx2 : (UINT)_iLayerIdx1;
	m_arrCheck[iIdx] |= (1 << iBitIdx);
}