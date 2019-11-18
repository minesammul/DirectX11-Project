#ifndef _TOOL
#define _TOOL

#include "value.fx"
#include "func.fx"

// ==================
// Grid Shader
// AlphaBlend : true
// ==================

struct VTX_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float3 vWorldPos : POSITION;
    float2 vUV : TEXCOORD;
};

VTX_OUT VS_Grid(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld).xyz;
    output.vUV = _in.vUV;

    return output;
}


float4 PS_Grid(VTX_OUT _in) : SV_Target
{   
    if (abs(_in.vWorldPos.x - round(_in.vWorldPos.x)) < 0.1f)
    {
        return float4(1.f, 1.f, 1.f, 1.f);
    }
    else
    {
        clip(-1);
        return float4(0.f, 0.f, 0.f, 0.f);
    }

    

}

#endif