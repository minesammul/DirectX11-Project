#include "stdafx.h"
#include "Camera.h"

#include "Transform.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "RenderMgr.h"

#include "GameObject.h"
#include "MeshRender.h"
#include "Material.h"
#include "Shader.h"

CCamera::CCamera()
	: m_eType(PROJ_TYPE::PERSPECTIVE)
	, m_fScale(1.f)
	, m_fFOV(XM_PI / 4.f)
	, m_fNear(1.f)
	, m_fFar(100000.f)
	, m_iLayerCheck(0)
	, m_iCamOrder(0)
	, CComponent(COMPONENT_TYPE::CAMERA)
{	
}

CCamera::~CCamera()
{
}

void CCamera::update()
{
}

void CCamera::finalupdate()
{
	Vec3 vPos = Transform()->GetLocalPos();

	// View 행렬 만들기
	m_matView = XMMatrixIdentity();
	m_matView._41 = -vPos.x;	
	m_matView._42 = -vPos.y;
	m_matView._43 = -vPos.z;
	
	Vec3 vRight = Transform()->GetLocalDir(DIR_TYPE::DIR_RIGHT);
	Vec3 vUp = Transform()->GetLocalDir(DIR_TYPE::DIR_UP);
	Vec3 vFront = Transform()->GetLocalDir(DIR_TYPE::DIR_FRONT);

	// 우, 상, 전 행렬을 단위행렬(기저벡터) 로 만들수 있는 회전행렬이 바로 뷰스페이스 회전행렬
	// 기저벡터 행렬이 단위행렬이기 때문에, 뷰스페이스 회전행렬은 우, 상, 전 행렬의 역행렬이다.
	// 우, 상, 전 으로 만들어진 행렬은 직교행렬이기 때문에 전치행렬이 곧 역행렬

	Matrix matViewRot;
	matViewRot = Matrix::Identity;
	matViewRot._11 = vRight.x; matViewRot._12 = vUp.x; matViewRot._13 = vFront.x;
	matViewRot._21 = vRight.y; matViewRot._22 = vUp.y; matViewRot._23 = vFront.y;
	matViewRot._31 = vRight.z; matViewRot._32 = vUp.z; matViewRot._33 = vFront.z;


	m_matView *= matViewRot;


	// Projection 행렬 만들기	
	//tResolution tRes = CDevice::GetInst()->GetResolution();
	tResolution tRes = CRenderMgr::GetInst()->GetResolution();

	if( m_eType == PROJ_TYPE::PERSPECTIVE)
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, tRes.fWidth / tRes.fHeight, m_fNear, m_fFar);
	else
		m_matProj = XMMatrixOrthographicLH(tRes.fWidth * m_fScale, tRes.fHeight * m_fScale, m_fNear, m_fFar);

	CRenderMgr::GetInst()->RegisterCamera(this);
}

void CCamera::render_deferred()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	g_transform.matView = m_matView;
	g_transform.matViewInv = XMMatrixInverse(nullptr, m_matView);
	g_transform.matProj = m_matProj;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == pCurScene->GetLayer(i))
			continue;

		if (IsValiedLayer(i))
		{
			const vector<CGameObject*>& vecObj = pCurScene->GetLayer(i)->GetAllObject();

			for (size_t i = 0; i < vecObj.size(); ++i)
			{
				if (nullptr == vecObj[i]->MeshRender()
					|| nullptr == vecObj[i]->MeshRender()->GetSharedMaterial()
					|| nullptr == vecObj[i]->MeshRender()->GetSharedMaterial()->GetShader())
					continue;

				if (vecObj[i]->MeshRender()->GetSharedMaterial()->GetShader()->IsDeferred())
				{
					vecObj[i]->render();
				}
			}
		}
	}
}

void CCamera::render_forward()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	g_transform.matView = m_matView;
	g_transform.matProj = m_matProj;

	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		if (nullptr == pCurScene->GetLayer(i))
			continue;

		if (IsValiedLayer(i))
		{
			const vector<CGameObject*>& vecObj = pCurScene->GetLayer(i)->GetAllObject();

			for (size_t i = 0; i < vecObj.size(); ++i)
			{
				if (nullptr == vecObj[i]->MeshRender()
					|| nullptr == vecObj[i]->MeshRender()->GetSharedMaterial()
					|| nullptr == vecObj[i]->MeshRender()->GetSharedMaterial()->GetShader())
					continue;

				if (!vecObj[i]->MeshRender()->GetSharedMaterial()->GetShader()->IsDeferred())
				{
					vecObj[i]->render();
				}
			}
		}
	}
}

void CCamera::CheckLayer(UINT _iLayerIdx)
{
	UINT iCheck = 1 << _iLayerIdx;
	if (m_iLayerCheck & iCheck)
		m_iLayerCheck &= ~iCheck;
	else
		m_iLayerCheck |= iCheck;
}

void CCamera::SaveToScene(FILE * _pFile)
{
	fwrite(&m_eType, sizeof(UINT), 1, _pFile);
	fwrite(&m_fScale, sizeof(float), 1, _pFile);
	fwrite(&m_fFOV, sizeof(float), 1, _pFile);
	fwrite(&m_fNear, sizeof(float), 1, _pFile);
	fwrite(&m_fFar, sizeof(float), 1, _pFile);
	fwrite(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
	fwrite(&m_iCamOrder, sizeof(UINT), 1, _pFile);
}

void CCamera::LoadFromScene(FILE * _pFile)
{
	fread(&m_eType, sizeof(UINT), 1, _pFile);
	fread(&m_fScale, sizeof(float), 1, _pFile);
	fread(&m_fFOV, sizeof(float), 1, _pFile);
	fread(&m_fNear, sizeof(float), 1, _pFile);
	fread(&m_fFar, sizeof(float), 1, _pFile);
	fread(&m_iLayerCheck, sizeof(UINT), 1, _pFile);
	fread(&m_iCamOrder, sizeof(UINT), 1, _pFile);
}
