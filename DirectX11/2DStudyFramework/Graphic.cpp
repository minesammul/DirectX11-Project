#include "stdafx.h"
#include "Graphic.h"

Graphic::Graphic()
{
}


Graphic::~Graphic()
{
}

void Graphic::Init(HWND hWnd, bool bWindowed)
{
	Core::GetInstance()->Init(hWnd, bWindowed);
}

void Graphic::Update()
{
	Core::GetInstance()->Update();
}

void Graphic::Render()
{
	Core::GetInstance()->Render();
}

void Graphic::SetWorldMatrix(std::string name, TObjectMatrix worldMatrix)
{
	Core::GetInstance()->SetObjectWorldPositionMatrix(name, worldMatrix.worldPosition);
}

void Graphic::SaveObjectData(TObject tData)
{
	m_tObjects.tVertex.push_back(tData.tVertex);
	m_tObjects.tWorldMatrix.push_back(tData.tWorldMatrix);
	m_tObjects.sName.push_back(tData.sName);
	m_tObjects.tIndexOrder.push_back(tData.tIndexOrder);
}

void Graphic::ObjectCreate()
{
	Core::GetInstance()->VertexBufferCreate(m_tObjects.tVertex, m_tObjects.tWorldMatrix, m_tObjects.sName);
	Core::GetInstance()->IndexBufferCreate(m_tObjects.tIndexOrder);
}
