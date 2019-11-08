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

void SaveWString(const wchar_t* _pStr, FILE * _pFile)
{
	int iLen = wcslen(_pStr);
	fwrite(&iLen, sizeof(int), 1, _pFile);
	fwrite(_pStr, sizeof(wchar_t), iLen, _pFile);
}

wchar_t* LoadWString(FILE * _pFile)
{
	static wchar_t szBuffer[255] = {};
	wmemset(szBuffer, L'\0', 255);

	int iLen = 0;
	fread(&iLen, sizeof(int), 1, _pFile);
	fread(szBuffer, sizeof(wchar_t), iLen, _pFile);

	return szBuffer;
}

bool closeEnough(const float & a, const float & b, const float & epsilon)
{
	return (epsilon > std::abs(a - b));
}

Vec3 DecomposeRotMat(const Matrix & _matRot)
{
	// _mat 을 분해 후 다시 행렬 만들기	
	Vec4 vMat[4];
	XMStoreFloat4(&vMat[0], _matRot.Right());   // 1
	XMStoreFloat4(&vMat[1], _matRot.Up());      // 2
	XMStoreFloat4(&vMat[2], _matRot.Front());   // 3
	XMStoreFloat4(&vMat[3], _matRot.Translation());//4

	Vec3 vNewRot;
	if (closeEnough(vMat[0].z, -1.0f)) {
		float x = 0; //gimbal lock, value of x doesn't matter
		float y = XM_PI / 2;
		float z = x + atan2(vMat[1].x, vMat[2].x);
		vNewRot = Vec3{ x, y, z };
	}
	else if (closeEnough(vMat[0].z, 1.0f)) {
		float x = 0;
		float y = -XM_PI / 2;
		float z = -x + atan2(-vMat[1].x, -vMat[2].x);
		vNewRot = Vec3{ x, y, z };
	}
	else { //two solutions exist
		float y1 = -asin(vMat[0].z);
		float y2 = XM_PI - y1;

		float x1 = atan2f(vMat[1].z / cos(y1), vMat[2].z / cos(y1));
		float x2 = atan2f(vMat[1].z / cos(y2), vMat[2].z / cos(y2));

		float z1 = atan2f(vMat[0].y / cos(y1), vMat[0].x / cos(y1));
		float z2 = atan2f(vMat[0].y / cos(y2), vMat[0].x / cos(y2));

		//choose one solution to return
		//for example the "shortest" rotation
		if ((std::abs(x1) + std::abs(y1) + std::abs(z1)) <= (std::abs(x2) + std::abs(y2) + std::abs(z2)))
		{
			vNewRot = Vec3{ x1, y1, z1 };
		}
		else {
			vNewRot = Vec3{ x2, y2, z2 };
		}
	}
	return vNewRot;
}

