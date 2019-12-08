#include "stdafx.h"
#include "Collider3D.h"

#include "Transform.h"
#include "ResMgr.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "Script.h"

CResPtr<CMaterial> CCollider3D::g_pOriginMtrl = nullptr;
vector<CResPtr<CMaterial>> CCollider3D::g_vecColMtrl;

CCollider3D::CCollider3D() : 
	CComponent(COMPONENT_TYPE::COLLIDER3D)
	, m_vOffset(Vec3(0.f, 0.f, 0.f))
	, m_vScale(Vec3(1.f, 1.f, 1.f))
	, m_eType(COLLIDER3D_TYPE::END)
	, m_pCurMtrl(nullptr)
	, m_iColCount(0)
{
	SetColliderType(COLLIDER3D_TYPE::CUBE);
	m_pCurMtrl = g_pOriginMtrl;
}

CCollider3D::~CCollider3D()
{
}

void CCollider3D::update()
{
}

void CCollider3D::finalupdate()
{
	Vec3 vPos = Transform()->GetLocalPos();
	Vec3 vScale = Transform()->GetLocalScale();
	Vec3 vRot = Transform()->GetLocalRot();

	m_vFinalPos = vPos + m_vOffset;
	m_vFinalScale = vScale * m_vScale;

	Matrix matScale = XMMatrixScaling(m_vFinalScale.x, m_vFinalScale.y, m_vFinalScale.z);
	Matrix matRotationX = XMMatrixRotationX(vRot.x);
	Matrix matRotationY = XMMatrixRotationY(vRot.y);
	Matrix matRotationZ = XMMatrixRotationZ(vRot.z);
	Matrix matTrans = XMMatrixTranslation(m_vFinalPos.x, m_vFinalPos.y, m_vFinalPos.z);

	m_matColWorld = matScale * matRotationX * matRotationY * matRotationZ * matTrans;

	if (Object()->GetParent())
		m_matColWorld *= Object()->GetParent()->Transform()->GetWorldMat();
}

void CCollider3D::CreateMaterial()
{
	g_pOriginMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"Collider3DMtrl");

	for (UINT i = 0; i < 10; ++i)
	{
		CResPtr<CMaterial> pCloneMtrl = g_pOriginMtrl->Clone();
		CResMgr::GetInst()->AddCloneRes<CMaterial>(pCloneMtrl);
		g_vecColMtrl.push_back(pCloneMtrl);
	}
}

CResPtr<CMaterial> CCollider3D::GetCloneMtrl()
{
	if (g_vecColMtrl.empty())
	{
		CResPtr<CMaterial> pNewClone = g_pOriginMtrl->Clone();
		CResMgr::GetInst()->AddCloneRes<CMaterial>(pNewClone);
		return pNewClone;
	}

	CResPtr<CMaterial> pMtrl = g_vecColMtrl.back();
	g_vecColMtrl.pop_back();

	return pMtrl;
}

void CCollider3D::ClearMaterial()
{
	g_pOriginMtrl = nullptr;
	for (UINT i = 0; i < g_vecColMtrl.size(); ++i)
	{
		g_vecColMtrl[i] = nullptr;
	}
}

void CCollider3D::SetColliderType(COLLIDER3D_TYPE _eType)
{
	m_eType = _eType;
	if (COLLIDER3D_TYPE::CUBE == m_eType)
	{
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh");
	}
	else if (COLLIDER3D_TYPE::SPHERE == m_eType)
	{
		m_pMesh = CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh");
	}
	else
		assert(nullptr);
}

void CCollider3D::UpdateData()
{
	g_transform.matWorld = m_matColWorld;

	static CConstBuffer* pCB = CDevice::GetInst()->FindConstBuffer(L"Transform");

	pCB->AddData(&g_transform, sizeof(tTransform));
	pCB->UpdateData();
	pCB->SetRegister((UINT)SHADER_TYPE::VERTEX_SHADER);
}

void CCollider3D::render()
{
	UpdateData();

	m_pMesh->SetLayout(m_pCurMtrl->GetShader());
	m_pCurMtrl->UpdateData();
	m_pMesh->render();
}

void CCollider3D::OnCollisionEnter(CCollider3D * _pOther)
{
	// 현재 참조하고 있는 CurMtrl 이 이미 Clone 이라면 다시 풀에서 꺼내오지 않는다.
	if (g_pOriginMtrl == m_pCurMtrl)
		m_pCurMtrl = GetCloneMtrl();

	int collisionCheck = 1;
	m_pCurMtrl->SetData(SHADER_PARAM::INT_0, &collisionCheck);

	++m_iColCount;


	const vector<CScript*>& vecScript = Object()->GetScripts();
	for (UINT i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnCollisionEnter(_pOther);
	}
}

void CCollider3D::OnCollision(CCollider3D * _pOther)
{
	const vector<CScript*>& vecScript = Object()->GetScripts();
	for (UINT i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnCollision(_pOther);
	}
}

void CCollider3D::OnCollisionExit(CCollider3D * _pOther)
{
	--m_iColCount;

	if (0 == m_iColCount)
	{
		g_vecColMtrl.push_back(m_pCurMtrl);
		m_pCurMtrl = g_pOriginMtrl;
	}

	const vector<CScript*>& vecScript = Object()->GetScripts();
	for (UINT i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->OnCollisionExit(_pOther);
	}
}
void CCollider3D::SaveToScene(FILE * _pFile)
{
	fwrite(&m_vOffset, sizeof(Vec3), 1, _pFile);
	fwrite(&m_vScale, sizeof(Vec3), 1, _pFile);
	fwrite(&m_eType, sizeof(UINT), 1, _pFile);
}

void CCollider3D::LoadFromScene(FILE * _pFile)
{
	fread(&m_vOffset, sizeof(Vec3), 1, _pFile);
	fread(&m_vScale, sizeof(Vec3), 1, _pFile);
	fread(&m_eType, sizeof(UINT), 1, _pFile);

	SetColliderType(m_eType);
}
