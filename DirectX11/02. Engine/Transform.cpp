#include "stdafx.h"
#include "Transform.h"

#include "Device.h"
#include "ConstBuffer.h"

tTransform g_transform;

CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
{	
}

CTransform::~CTransform()
{
}

void CTransform::update()
{		
}

void CTransform::finalupdate()
{
	Matrix matScale = XMMatrixScaling(m_vLocalScale.x, m_vLocalScale.y, m_vLocalScale.z);
	Matrix matRotationX = XMMatrixRotationX(m_vLocalRot.x);
	Matrix matRotationY = XMMatrixRotationY(m_vLocalRot.y);
	Matrix matRotationZ = XMMatrixRotationZ(m_vLocalRot.z);
	Matrix matTrans = XMMatrixTranslation(m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	m_matWorld = matScale * matRotationX * matRotationY * matRotationZ * matTrans;

	// �θ� ������Ʈ�� ������, �θ� ��������� �ڿ� �����ش�.
	CGameObject* pParentObj = ParentObject();
	if (pParentObj)
	{
		const Matrix& matParentWorld = pParentObj->Transform()->GetWorldMat();
		m_matWorld *= matParentWorld;
	}
}

void CTransform::UpdateData()
{
	g_transform.matWorld = m_matWorld;
	g_transform.matWV = m_matWorld * g_transform.matView;
	g_transform.matWVP = g_transform.matWV * g_transform.matProj;



	static CConstBuffer* pCB = CDevice::GetInst()->FindConstBuffer(L"Transform");
	   
	pCB->AddData(&g_transform, sizeof(tTransform));
	pCB->UpdateData();	
	pCB->SetRegister((UINT)SHADER_TYPE::VERTEX_SHADER);
}
