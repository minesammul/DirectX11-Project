#pragma once
#include "Component.h"
class Transform :
	public Component
{
private:
	DirectX::XMFLOAT3 m_f3LocalPosition;
	DirectX::XMFLOAT3 m_f3LocalScale;
	DirectX::XMFLOAT3 m_f3LocalRotation;

	DirectX::XMMATRIX m_matWorld;

public:
	Transform();
	virtual ~Transform();
};

