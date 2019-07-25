#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
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
}
