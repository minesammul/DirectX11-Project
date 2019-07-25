#pragma once

struct TResolution
{
	float fWidth;
	float fHeight;
};

struct TVertex
{
	DirectX::XMFLOAT3 f3Position;
	DirectX::XMFLOAT4 f4Color;
};

struct TConstantBuffer
{
	ID3D11Buffer* pBuffer;
	UINT		  uiSize;
	UINT		  uiRegister;
};

struct TTransform
{
	DirectX::XMMATRIX matWorld;
	DirectX::XMMATRIX matView;
	DirectX::XMMATRIX matProj;
};
