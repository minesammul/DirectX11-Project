
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

static float3 g_vLightDir = float3(1.f, -1.f, 1.f);
static float3 g_vLightColor = float3(1.f, 1.f, 1.f);

// ==================
// 3D Gouraud Shader (°í·Î ½¦ÀÌµù)
// ==================
VTX_OUT VS_Gouraud(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);  
    
    float3 vNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));

    float3 vLightDir = normalize(-g_vLightDir);
    float fPow = dot(vLightDir, vNormal);
    output.vLightPow.x = saturate(fPow);

    return output;
}

float4 PS_Gouraud(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = float4(1.f, 0.3f, 0.3f, 1.f);
    vOutColor.rgb *= _in.vLightPow.x;

    return vOutColor;
}

















#endif
