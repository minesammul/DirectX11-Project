#pragma once
class Core
{
private:
	HWND m_hWnd;
	bool m_bWindowed;
	float m_fClearColor[4];

	TResolution m_tRes;
	
	std::vector<TObjectMatrix> m_tObjectWorldMatrix;
	std::vector<unsigned int> m_iVertexOffset;
	std::vector<unsigned int> m_iIndexCount;
	std::vector<unsigned int> m_iIndexOffset;

	std::map<std::string, unsigned int> m_stdMapObjectName;

	ID3D11Buffer* m_pVertexBuffer	= nullptr;
	ID3D11Buffer* m_pIndexBuffer	= nullptr;
	ID3D11Buffer* m_pConstantBuffer = nullptr;

	ID3DBlob*	   m_pVertexBlob = nullptr;
	ID3DBlob*	   m_pPixelBlob = nullptr;
	ID3DBlob*	   m_pErrorBlob = nullptr;

	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader*	m_pPixelShader = nullptr;

	ID3D11InputLayout* m_pLayout = nullptr;
	
	bool m_bFire;

public:
	Core();
	~Core();

	int Init(HWND hWnd, bool bWindowed);
	void DeviceInit();
	void ManagerInit();
	void VertexBufferCreate();
	void VertexBufferCreate(std::vector<std::vector<TVertex>> vertexs, std::vector<TObjectMatrix> worldMatrix, std::vector<std::string> name);
	void IndexBufferCreate();
	void IndexBufferCreate(std::vector<std::vector<unsigned int>> indexs);
	void ConstantBufferCreate();
	void VertexShaderCreate();
	void PixelShaderCreate();
	void LayoutCreate();
	void ContextInit();

	void Update();
	
	void Render();
	void ApplyMatrix(DirectX::XMFLOAT3 worldPosition, DirectX::XMFLOAT3 worldScale, DirectX::XMFLOAT3 worldRotation);

	void SetObjectWorldPositionMatrix(std::string name, DirectX::XMFLOAT3 worldPosition);
	void SetObjectWorldScaleMatrix(DirectX::XMFLOAT3 worldScale);
	void SetObjectWorldRotationMatrix(DirectX::XMFLOAT3 worldRotation);

	HWND GetWindowHwnd()
	{
		return m_hWnd;
	}

	static Core* GetInstance()
	{
		static Core instance;
		return &instance;
	}
};

