#include "stdafx.h"
#include "func.h"

float GetAngle(float _fRadian)
{
	return (_fRadian / XM_PI) * 180.f;
}

float GetRadian(float _fAngle)
{
	return (_fAngle / 180.f) * XM_PI;
}
