#include "stdafx.h"
#include "Camera.h"

#include "Transform.h"
#include "Device.h"
#include "SceneMgr.h"

Camera::Camera() :
	m_eType(PROJ_TYPE::PERSPECTIVE),
	m_fScale(1.f),
	m_fFOV(DirectX::XM_PI / 4.f),
	m_fNear(1.f),
	m_fFar(1000.f),
	m_uiLayerCheck(0)
{
	SetComponentType(EComponentType::CAMERA);
}


Camera::~Camera()
{
}

void Camera::Update()
{
	
}

void Camera::FinalUpdate()
{
	//// View 행렬 만들기
	//g_transform.matView = XMMatrixIdentity();
	//g_transform.matView._41 = -g_vCamPos.x;	g_transform.matView._42 = -g_vCamPos.y; g_transform.matView._43 = -g_vCamPos.z;
	//
	//// Projection 행렬 만들기	
	//g_transform.matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, m_tRes.fWidth / m_tRes.fHeight, 1.f, 1000.f);
	//
	//XMMatrixOrthographicLH();

	DirectX::XMFLOAT3 vPos = GetTransform()->GetLocalPos();

	// View ��� �����
	m_matView = DirectX::XMMatrixIdentity();
	m_matView = DirectX::XMMatrixTranslation(-vPos.x, -vPos.y, -vPos.z);
	m_matView = DirectX::XMMatrixTranspose(m_matView);

	// Projection ��� �����    
	TResolution tRes = Device::GetInstance()->GetResolution();

	if (m_eType == PROJ_TYPE::PERSPECTIVE)
		m_matProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PI / 4.f, tRes.fWidth / tRes.fHeight, m_fNear, m_fFar);
	else
		m_matProj = DirectX::XMMatrixOrthographicLH(tRes.fWidth * m_fScale, tRes.fHeight * m_fScale, m_fNear, m_fFar);

	m_matProj = DirectX::XMMatrixTranspose(m_matProj);

	SceneMgr::GetInstance()->RegisterCamera(this);
}

void Camera::CheckLayer(UINT _iLayerIdx)
{
	UINT iCheck = 1 << _iLayerIdx;
	if (m_uiLayerCheck & iCheck)
		m_uiLayerCheck &= ~iCheck;
	else
		m_uiLayerCheck |= iCheck;
}
