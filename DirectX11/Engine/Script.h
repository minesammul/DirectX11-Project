#pragma once
#include "Component.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResourceMgr.h"

#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"

#include "Scene.h"
#include "Layer.h"
#include "SceneMgr.h"

class Script : public Component
{
public:
	Script();
	virtual ~Script();
};

