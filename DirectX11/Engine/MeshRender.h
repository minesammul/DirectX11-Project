#pragma once
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"

class MeshRender : public Component
{
private:
	Mesh * m_pMesh;
	Shader*	m_pShader;

public:
	MeshRender();
	~MeshRender();

public:
	void SetMesh(Mesh* _pMesh) { m_pMesh = _pMesh; }
	void SetShader(Shader* _pShader) { m_pShader = _pShader; }

public:
	virtual void Update();
	void Render();

};

