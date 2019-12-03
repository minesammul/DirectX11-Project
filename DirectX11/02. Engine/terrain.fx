#ifndef _TERRAIN
#define _TERRAIN

#include "value.fx"
#include "func.fx"

struct VTX_IN
{
    float3 vPos : POSITION;    
    float3 vNormal : NORMAL;
    float3 vTangent : TANGENT;
    float3 vBinormal : BINORMAL;    
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPos : SV_Position;
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
    float3 vViewTangent : TANGENT;
    float3 vViewBinormal : BINORMAL;
    float2 vUV : TEXCOORD;
};

struct PS_OUT
{
    float4 vDiffuse : SV_Target;
    float4 vNormal : SV_Target1;
    float4 vPosition : SV_Target2;
};

// ====================
// Terrain Shader
// g_tex_0 : tile texture
// g_tex_1 : normalmap texture
// ====================
VTX_OUT VS_Terrain(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;    
    
    output.vPos = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vViewNormal = mul(float4(_in.vNormal, 0.f), g_matWV).xyz;
    output.vViewTangent = mul(float4(_in.vTangent, 0.f), g_matWV).xyz;
    output.vViewBinormal = mul(float4(_in.vBinormal, 0.f), g_matWV).xyz;
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV).xyz;
    
    output.vUV = _in.vUV;
    
    return output;
}

PS_OUT PS_Terrain(VTX_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    if(g_tcheck_0)    
        output.vDiffuse = g_tex_0.Sample(g_sam_0, _in.vUV);    
    else
        output.vDiffuse = float4(1.f, 0.f, 1.f, 1.f);
        
    if(g_tcheck_1)
    {
        float3x3 matTBN = { _in.vViewTangent, _in.vViewBinormal, _in.vViewNormal };
        float3 vViewNormal = g_tex_1.Sample(g_sam_0, _in.vUV).xyz;
        vViewNormal = (vViewNormal - 0.5f) * 2.f;
        vViewNormal = mul(vViewNormal.xyz, matTBN);
        output.vNormal.xyz = vViewNormal;
    }
    else
        output.vNormal.xyz = _in.vViewNormal;
    
    output.vPosition.xyz = _in.vViewPos;    
    
    return output;
}






#endif