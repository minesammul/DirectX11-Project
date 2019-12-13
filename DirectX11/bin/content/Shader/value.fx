#ifndef _VALUE
#define _VALUE

struct tLightColor
{
    float4 vLightDiff; // 빛의 색상
    float4 vLightSpec; // 반사광 세기
    float4 vLightAmb; // 환경광 세기
};

struct tLight3D
{
    tLightColor tColor;
    float4 vLightWorldPos;
    float4 vLightDir; // 방향성, spot  
    uint iLightType;
    float fLightRange; // 점광원, Spot
    float fLightAngle; // Spot
    uint iPadding;
};

cbuffer MATRIX : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
    row_major matrix g_matWorldInv;
    row_major matrix g_matViewInv;
}

cbuffer MATERIAL : register(b1)
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;

    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;

    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;

    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;

    row_major Matrix g_mat_0;
    row_major Matrix g_mat_1;
    row_major Matrix g_mat_2;
    row_major Matrix g_mat_3;

    uint g_tcheck_0;
    uint g_tcheck_1;
    uint g_tcheck_2;
    uint g_tcheck_3;
    
    uint g_ucheck_0;
    uint g_ucheck_1;
    uint g_ucheck_2;
    uint g_ucheck_3;
}

cbuffer ANIM2D : register(b2)
{
    float2 vLT;
    float2 vSize;
    int iAnimCheck;
    float3 vPadding;
}

cbuffer GLOBAL_VALUE : register(b3)
{
    float fDT; // deltatime
    float fAccTime; // 누적시간
    float fTargetWidth; // 출력 타겟 해상도
    float fTargetHeight; // 출력 타겟 해상도
}

cbuffer LIGHT_3D : register(b4)
{
    tLight3D g_arrLight3D[100];
    int g_iLight3DCount;
    int3 g_iLight3DPadding;
}

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);

Texture2D g_tex_anim : register(t17);

RWTexture2D<float4> g_rwtex_0 : register(u0);
RWTexture2D<float4> g_rwtex_1 : register(u1);
RWTexture2D<float4> g_rwtex_2 : register(u2);
RWTexture2D<float4> g_rwtex_3 : register(u3);

SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);
SamplerState g_sam_2 : register(s2);
SamplerState g_sam_3 : register(s3);

#endif