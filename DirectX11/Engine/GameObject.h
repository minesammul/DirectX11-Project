#pragma once
#include "Entity.h"

class Component;
class Transform;
class Camera;
class MeshRender;

class GameObject : public Entity
{
private:
	Component * m_arrCom[(UINT)EComponentType::END];

public:
	GameObject();
	virtual ~GameObject();

public:
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

	void AddComponent(Component* _pCom);

	Transform* GetTransform() { return (Transform*)m_arrCom[(UINT)EComponentType::TRANSFORM]; }
	MeshRender* GetMeshRender() { return (MeshRender*)m_arrCom[(UINT)EComponentType::MESHRENDER]; }
	Camera * GetCamera() { return (Camera*)m_arrCom[(UINT)EComponentType::CAMERA]; }



};

