#pragma once
#include "Component.h"

class Transform : public Component
{
private:
	DirectX::XMFLOAT3		m_vLocalPos;
	DirectX::XMFLOAT3		m_vLocalScale;
	DirectX::XMFLOAT3		m_vLocalRot;

	DirectX::XMMATRIX		m_matWorld;


public:
	Transform();
	~Transform();

	CLONE(Transform);

public:
	void SetLocalPos(const DirectX::XMFLOAT3& _vPos) { m_vLocalPos = _vPos; }
	void SetLocalScale(const DirectX::XMFLOAT3& _vScale) { m_vLocalScale = _vScale; }
	void SetLocalRot(const DirectX::XMFLOAT3& _vRot) { m_vLocalRot = _vRot; }

	const DirectX::XMFLOAT3& GetLocalPos() { return m_vLocalPos; }
	const DirectX::XMFLOAT3& GetLocalScale() { return m_vLocalScale; }
	const DirectX::XMFLOAT3& GetLocalRot() { return m_vLocalRot; }

public:
	void Update();
	void UpdateData();
};

