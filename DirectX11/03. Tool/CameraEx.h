#pragma once
#include <Engine/Camera.h>

class CCameraEx :
	public CCamera
{
public:
	virtual void finalupdate();

public:
	CCameraEx();
	virtual ~CCameraEx();
};

