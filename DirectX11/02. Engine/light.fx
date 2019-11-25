#ifndef _LIGHT
#define _LIGHT

#include "value.fx"
#include "func.fx"

// =========================
// DirLight Shader
// mesh : Rect Mesh
// g_tex_0 : DiffuseTarget
// g_tex_1 : NormalTarget
// g_tex_2 : PositionTarget
// g_int_0 : Light Index ( 광원 버퍼에서 자신의 인덱스)
// =========================

struct VTX_IN
{
    float3 vPosition : POSITION;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

struct PS_OUT
{
    float4 vDiffuseLight : SV_Target;
    float4 vSpecularLight : SV_Target1;
};

VTX_OUT VS_DirLight(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition.xyz = _in.vPosition * 2.f;
    output.vPosition.w = 1.f;
    output.vUV = _in.vUV;
    
    return output;
}

PS_OUT PS_DirLight(VTX_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    float4 vViewPos = g_tex_2.Sample(g_sam_0, _in.vUV);
    if (vViewPos.z == 0.f)
        clip(-1);
    
    float4 vViewNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
    
    tLightColor color = (tLightColor) 0.f;
    CaculateLight(vViewPos.xyz, vViewNormal.xyz, g_int_0, color);
    
    output.vDiffuseLight = color.vLightDiff + color.vLightAmb;
    output.vSpecularLight = color.vLightSpec;
    
    return output;
}

#endif
