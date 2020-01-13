#include "stdafx.h"
#include "Animator3D.h"

#include "TimeMgr.h"
#include "MeshRender.h"
#include "Material.h"
#include "ResMgr.h"
#include "ResPtr.h"

CAnimator3D::CAnimator3D()
	: m_iCurClip(0)
	, m_fCurTime(0.f)
	, m_iFrameCount(30)
	, CComponent(COMPONENT_TYPE::ANIMATOR3D)
{	
}

CAnimator3D::~CAnimator3D()
{
}

void CAnimator3D::update()
{	
}

void CAnimator3D::lateupdate()
{	
}

void CAnimator3D::finalupdate()
{
	m_fCurTime = 0.f;
	// 현재 재생중인 Clip 의 시간을 진행한다.
	m_vecClipUpdateTime[m_iCurClip] += DT;

	if (m_vecClipUpdateTime[m_iCurClip] >= m_pVecClip->at(m_iCurClip).dTimeLength)
	{
		//m_vecClipUpdateTime[m_iCurClip] = 0.f;
	}

	m_fCurTime = m_pVecClip->at(m_iCurClip).dStartTime + m_vecClipUpdateTime[m_iCurClip];

	// 본 개수만큼 반복하며 현재 시간에 맞게 모든 본 행렬을 모두 보간해준다.
	for (size_t i = 0; i < m_pVecBones->size(); ++i)
	{
		if (m_pVecBones->at(i).vecKeyFrame.empty())
		{
			// 키프레임 별 행렬이 없는 본일 경우
			m_vecFinalBoneMat[i] = m_pVecBones->at(i).matBone;
			continue;
		}

		// 시간을 통하여 인덱스를 구한다.
		int	iFrameIndex = (int)(m_fCurTime * m_iFrameCount);
		int	iFrameNextIndex = 0.f;

		if (iFrameIndex >= m_pVecClip->at(m_iCurClip).iEndFrame - 1)
		{
			iFrameIndex = m_pVecClip->at(m_iCurClip).iEndFrame - 1;
			iFrameNextIndex = m_pVecClip->at(m_iCurClip).iEndFrame - 1;
		}
		else
		{
			iFrameNextIndex = iFrameIndex + 1;
		}

		const tMTKeyFrame& tKeyFrame = m_pVecBones->at(i).vecKeyFrame[iFrameIndex];
		const tMTKeyFrame& tNextKeyFrame = m_pVecBones->at(i).vecKeyFrame[iFrameNextIndex];

		float	fFrameTime = tKeyFrame.fTime;
		float	fNextFrameTime = tNextKeyFrame.fTime;

		// 프레임간의 시간에 따른 비율을 구해준다.
		float	fPercent = (m_fCurTime - fFrameTime) / (1.f / m_iFrameCount);

		XMVECTOR vS1 = tKeyFrame.vScale;
		XMVECTOR vS2 = tNextKeyFrame.vScale;

		XMVECTOR vT1 = tKeyFrame.vTranslate;
		XMVECTOR vT2 = tNextKeyFrame.vTranslate;

		XMVECTOR vQ1 = XMLoadFloat4(&tKeyFrame.qRot);
		XMVECTOR vQ2 = XMLoadFloat4(&tNextKeyFrame.qRot);

		XMVECTOR vS = XMVectorLerp(vS1, vS2, fPercent);
		XMVECTOR vT = XMVectorLerp(vT1, vT2, fPercent);
		XMVECTOR vQ = XMQuaternionSlerp(vQ1, vQ2, fPercent);

		XMVECTOR vQZero = XMVectorSet(0.f, 0.f, 0.f, 1.f);

		// 오프셋 행렬을 곱하여 최종 본행렬을 만들어낸다.				
		m_vecFinalBoneMat[i] = m_pVecBones->at(i).matOffset * XMMatrixAffineTransformation(vS, vQZero, vQ, vT);
	}	
}

void CAnimator3D::SaveToScene(FILE * _pFile)
{
	wstring meshName = Object()->MeshRender()->GetMesh()->GetName();
	SaveWString(meshName.c_str(), _pFile);
}

void CAnimator3D::LoadFromScene(FILE * _pFile)
{
	//현재 추가되는 오브젝트의 다른 component를 참조할 수 없다.
	//오로지 여기서 저장했던 정보만을 가져와서 다시 로드시켜야한다.
	//다만, 리소스는 이미 싱글톤에 존재하며, 이것을 이용할 순 있을 것이다.
	wstring meshName = LoadWString(_pFile);
	CResPtr<CMesh> pMesh = CResMgr::GetInst()->FindRes<CMesh>(meshName);
	SetBones(pMesh->GetBones());
	SetAnimClip(pMesh->GetAnimClip());
	SetBoneTex(pMesh->GetBoneTex());
}

void CAnimator3D::SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip)
{
	m_pVecClip = _vecAnimClip;
	m_vecClipUpdateTime.resize(m_pVecClip->size());
}

void CAnimator3D::UpdateData()
{
	// Bone Texture Update
	m_pBoneTex->SetData(&m_vecFinalBoneMat[0], sizeof(Matrix) * m_vecFinalBoneMat.size());

	UINT iMtrlCount = MeshRender()->GetMaterialCount();
	CResPtr<CMaterial> pMtrl = nullptr;
	for (UINT i = 0; i < iMtrlCount; ++i)
	{
		pMtrl = MeshRender()->GetSharedMaterial(i);
		if (nullptr == pMtrl)
			continue;

		pMtrl->SetData(SHADER_PARAM::TEX_7, &m_pBoneTex);
	}
}