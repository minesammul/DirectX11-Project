#pragma once

struct TResolution
{
	float fWidth;
	float fHeight;
};

struct TVertex
{
	DirectX::XMFLOAT3 vPos;
	DirectX::XMFLOAT4 vColor;
};

struct TObjectMatrix
{
	DirectX::XMFLOAT3 worldPosition;
	DirectX::XMFLOAT3 worldScale;
	DirectX::XMFLOAT3 worldRotation;
};