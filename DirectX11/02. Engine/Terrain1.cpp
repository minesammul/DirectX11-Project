#include "stdafx.h"
#include "Terrain.h"

#include "MeshRender.h"
#include "ResMgr.h"
#include "Material.h"
#include "Transform.h"
#include "RenderMgr.h"
#include "Camera.h"
#include "KeyMgr.h"

CTerrain::CTerrain()
	: CComponent(COMPONENT_TYPE::TERRAIN)
{
}

CTerrain::~CTerrain()
{
}

void CTerrain::init(UINT _iXFace, UINT _iZFace)
{	
	m_iXFaceCount = _iXFace;
	m_iZFaceCount = _iZFace;

	LoadResource();

	// Transform
	Transform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
}

void CTerrain::finalupdate()
{
	Vec4 vScale = Vec4(Transform()->GetLocalScale());
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::VEC4_0, &vScale);

	if (KEYHOLD(KEY_TYPE::KEY_UP))
	{
		tRay ray = m_pToolCam->GetRay();

		Matrix matWorldInv = Transform()->GetWorldMat();
		matWorldInv = XMMatrixInverse(nullptr, matWorldInv);

		Vec4 vStart = XMVector3TransformCoord(ray.vStart, matWorldInv);
		Vec4 vDir = XMVector3TransformNormal(ray.vDir, matWorldInv);
		vDir.Normalize();

		m_pPickMtrl->SetData(SHADER_PARAM::INT_0, &m_iXFaceCount);
		m_pPickMtrl->SetData(SHADER_PARAM::INT_1, &m_iZFaceCount);
		m_pPickMtrl->SetData(SHADER_PARAM::VEC4_0, &vStart);
		m_pPickMtrl->SetData(SHADER_PARAM::VEC4_1, &vDir);

		int iXGroup = (m_iXFaceCount * 2) / 32;
		int iYGroup = m_iZFaceCount / 32;

		if ((m_iXFaceCount * 2) % 32 != 0)
			iXGroup += 1;
		if (m_iZFaceCount % 32)
			iYGroup += 1;

		m_pPickMtrl->ExcuteComputeShader(iXGroup, iYGroup, 1);
		Vec4* pData = (Vec4*)m_pOutput->GetSysMem();

		// 픽킹 위치를 비율로 전환
		Vec2 vPos = Vec2(pData->x / (float)m_iXFaceCount, 1.f - (pData->z / (float)m_iZFaceCount));
		Vec2 vScale = Vec2(0.1f, 0.1f);

		m_pHeightMapMtrl->SetData(SHADER_PARAM::VEC2_0, &vPos);
		m_pHeightMapMtrl->SetData(SHADER_PARAM::VEC2_1, &vScale);

		m_pHeightMapMtrl->ExcuteComputeShader(1, 1024, 1);
	}
}
