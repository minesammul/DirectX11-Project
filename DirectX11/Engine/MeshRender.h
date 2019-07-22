#pragma once
#include "Component.h"
#include "Mesh.h"

class MeshRender : public Component
{
private:
	Mesh * m_pMesh;

public:
	MeshRender();
	virtual ~MeshRender();
};

