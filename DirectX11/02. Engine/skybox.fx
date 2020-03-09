#ifndef _SKYBOX
#define _SKYBOX

#include "value.fx"
//========================
// Skybox Shader
// Rasteraizer : CULL_FRONT
// mesh : Sphere
// Depth func : LESS_QUAL
// g_tex_0 : Skybox Texture1
// g_tex_1 : Skybox Texture2
// g_vec2_0 : UV
// g_vec2_1  : Blend Ratio(x=Texture1, y=Texture2)
//=========================

struct VTX_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VTX_OUT VS_Skybox(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;
    
    // View, Proj    
    float4 vViewPos = mul(float4(_in.vPos, 0.f), g_matView); // View 변환에서 회전부분만 영향
    float4 vProjPos = mul(vViewPos, g_matProj);
    
    //vProjPos.x; // Proj.x * View.z()
    //vProjPos.y; // Proj.y * View.z()
    //vProjPos.z; // View.z()
    //vProjPos.w; // View.z()
    
    vProjPos.z = vProjPos.w;    
    
    output.vPosition = vProjPos;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Skybox(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;    
    
    float2 nowUV = _in.vUV;
    nowUV.x += g_vec2_0.x;
    
    float4 texture1Color = g_tex_0.Sample(g_sam_0, nowUV);
    float4 texture2Color = g_tex_1.Sample(g_sam_0, nowUV);
    
    texture1Color *= g_vec2_1.x;
    texture2Color *= g_vec2_1.y;
    
    //vOutColor = g_tex_0.Sample(g_sam_0, nowUV);
    
    vOutColor = texture1Color + texture2Color;
    
    return vOutColor;
}
#endif