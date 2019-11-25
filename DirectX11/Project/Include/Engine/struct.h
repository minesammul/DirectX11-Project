#pragma once

#include "define.h"

struct tResolution
{
	float fWidth;
	float fHeight;
};

struct tEvent
{
	EVENT_TYPE	eType;
	INT_PTR		wParam;	
	INT_PTR		lParam;	
};

// Vertex
struct VTX
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
	Vec3 vNormal;  // ���� ����
	Vec3 vTangent; // ���� ����
	Vec3 vBinormal;// ������ ����
};



//===============
// ������� ����ü
//===============
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
	Matrix matWV;
	Matrix matWVP;
};

struct tAnim2D
{
	Vec2 vLT;
	Vec2 vSize;
	int  iAnimCheck;
	int  iArrPadding[3];
};

struct tShaderParam
{
	int  arrInt[4];
	float arrFloat[4];
	Vec2 arrVec2[4];
	Vec4 arrVec4[4];
	Matrix arrMat[4];
	UINT arrTexCheck[(UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0];
};

struct tGlobalValue
{
	UINT iLightCount;
	float fDeltaTime;
	double dAccTime;
};

struct tLight3DInfo
{
	Vec4		vDiff;
	Vec4		vSpec;
	Vec4		vAmb;

	Vec4		vPos;
	Vec4		vDir; // ���⼺, spot
	UINT		iType;
	float		fRange; // ������, Spot
	float		fAngle; // Spot
	UINT		iPadding;
};
