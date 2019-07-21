#pragma once
struct TObject
{
	std::vector<TVertex> tVertex;
	TObjectMatrix	tWorldMatrix;
	std::vector<unsigned int> tIndexOrder;
	std::string sName;
};

struct TObjects
{
	std::vector<std::vector<TVertex>> tVertex;
	std::vector<TObjectMatrix> tWorldMatrix;
	std::vector<std::vector<unsigned int>> tIndexOrder;
	std::vector<std::string> sName;
};

class Graphic
{
private:
	TObjects m_tObjects;

public:
	Graphic();
	~Graphic();

	void Init(HWND hWnd, bool bWindowed);
	void Update();
	void Render();
	
	void SetWorldMatrix(std::string name, TObjectMatrix worldMatrix);

	void SaveObjectData(TObject tData);
	void ObjectCreate();
};

