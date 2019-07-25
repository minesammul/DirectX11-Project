#include "stdafx.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Transform.h"

MeshRender::MeshRender()
{
	SetComponentType(EComponentType::MESHRENDER);

}


MeshRender::~MeshRender()
{
}

void MeshRender::Update()
{
}

void MeshRender::Render()
{
	Object()->GetTransform()->UpdateData();

	m_pShader->UpdateData();
	m_pMesh->SetLayout(m_pShader->GetVertexShaderBlob());

	m_pMesh->Render();
}
