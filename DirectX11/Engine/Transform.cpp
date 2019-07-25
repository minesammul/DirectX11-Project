#include "stdafx.h"
#include "Transform.h"

#include "Core.h"
#include "Device.h"

TTransform g_transform;

Transform::Transform()
{
	SetComponentType(EComponentType::TRANSFORM);

}


Transform::~Transform()
{
}

void Transform::Update()
{
	DirectX::XMMATRIX matScale = DirectX::XMMatrixScaling(m_vLocalScale.x, m_vLocalScale.y, m_vLocalScale.z);
	DirectX::XMMATRIX matRotationX = DirectX::XMMatrixRotationX(m_vLocalRot.x);
	DirectX::XMMATRIX matRotationY = DirectX::XMMatrixRotationY(m_vLocalRot.y);
	DirectX::XMMATRIX matRotationZ = DirectX::XMMatrixRotationZ(m_vLocalRot.z);
	DirectX::XMMATRIX matTrans = DirectX::XMMatrixTranslation(m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	m_matWorld = matScale * matRotationX * matRotationY * matRotationZ * matTrans;

}

void Transform::UpdateData()
{
	Device::GetInstance()->g_tTransform.matWorld = m_matWorld;
	Device::GetInstance()->g_tTransform.matWorld = DirectX::XMMatrixTranspose(Device::GetInstance()->g_tTransform.matWorld);

	Device::GetInstance()->g_tTransform.matView = DirectX::XMMatrixIdentity();
	Device::GetInstance()->g_tTransform.matView = DirectX::XMMatrixTranspose(Device::GetInstance()->g_tTransform.matView);

	// Projection 행렬 만들기	
	Device::GetInstance()->g_tTransform.matProj = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XM_PI / 4.f, 
		Core::GetInstance()->GetResolution().fWidth / Core::GetInstance()->GetResolution().fHeight,
		1.f, 
		1000.f
	);
	Device::GetInstance()->g_tTransform.matProj = DirectX::XMMatrixTranspose(Device::GetInstance()->g_tTransform.matProj);

	static TConstantBuffer& tBuffer = Device::GetInstance()->FindConstBuffer(L"Transform");

	D3D11_MAPPED_SUBRESOURCE tSub = {};

	Device::GetInstance()->GetContext()->Map(tBuffer.pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &Device::GetInstance()->g_tTransform, tBuffer.uiSize);
	Device::GetInstance()->GetContext()->Unmap(tBuffer.pBuffer, 0);

	Device::GetInstance()->GetContext()->VSSetConstantBuffers(tBuffer.uiRegister, 1, &tBuffer.pBuffer);

}
