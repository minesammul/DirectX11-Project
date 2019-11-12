
#include "value.fx"

#ifndef _STD3D
#define _STD3D

struct VTX_IN
{
    float3 vPos : POSITION;
    float3 vNormal : NORMAL;
};


struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vLightPow : POSITION;
};

// ==================
// 3D Gouraud Shader (°í·Î ½¦ÀÌµù)
// ==================
VTX_OUT VS_Gouraud(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);  
    
    float3 vNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));

    float fPow = dot(-g_arrLight3D[0].vLightDir, vNormal);

    output.vLightPow.x = saturate(fPow);

    return output;
}

float4 PS_Gouraud(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = float4(1.f, 1.f, 1.f, 1.f);

    vOutColor.rgb *= g_arrLight3D[0].vLightColor * _in.vLightPow.x;

    return vOutColor;
}

// ==================
// 3D Gouraud Shader (°í·Î ½¦ÀÌµù)
// ==================
struct VTX_OUT_PHONG
{
    float4 vPosition : SV_Position;
    float3 vNormal : NORMAL;
};

VTX_OUT_PHONG VS_Phong(VTX_IN _in)
{
    VTX_OUT_PHONG output = (VTX_OUT_PHONG) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));
    
    return output;
}

float4 PS_Phong(VTX_OUT_PHONG _in) : SV_Target
{
    float fPow = saturate(dot(-g_arrLight3D[0].vLightDir, _in.vNormal));

    float4 vOutColor = float4(1.f, 1.f, 1.f, 1.f);
    vOutColor.rgb *= g_arrLight3D[0].vLightColor * fPow;

    return vOutColor;
}















#endif
