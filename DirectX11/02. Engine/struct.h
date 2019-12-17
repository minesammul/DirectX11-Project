#pragma once

#include "define.h"

struct tResolution
{
	float fWidth = 0.f;
	float fHeight = 0.f;
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
	Vec3 vNormal;  // 법선 벡터
	Vec3 vTangent; // 접선 벡터
	Vec3 vBinormal;// 종법선 벡터
};

struct tRay
{
	Vec3 vStart;
	Vec3 vDir;
};

//===============
// 상수버퍼 구조체
//===============
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
	Matrix matWV;
	Matrix matWVP;
	Matrix matWorldInv;
	Matrix matViewInv;
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
	UINT arrRWTexCheck[(UINT)SHADER_PARAM::RWTEX_END - (UINT)SHADER_PARAM::RWTEX_0];
};

struct tGlobalValue
{
	float fDeltaTime;
	float dAccTime;
	tResolution tResolution;
};

struct tLight3DInfo
{
	Vec4		vDiff;
	Vec4		vSpec;
	Vec4		vAmb;

	Vec4		vPos;
	Vec4		vDir; // 방향성, spot
	UINT		iType;
	float		fRange; // 점광원, Spot
	float		fAngle; // Spot
	UINT		iPadding;
};
