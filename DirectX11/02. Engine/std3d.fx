#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "func.fx"

struct VTX_IN
{
    float3 vPos : POSITION;
    float3 vNormal : NORMAL;
    float2 vUV : TEXCOORD;
};


struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vLightPow : POSITION;
};


// ==================
// 3D Phong Shader (Æþ ½¦ÀÌµù)
// ==================
struct VTX_OUT_PHONG
{
    float4 vPosition : SV_Position;
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
    float2 vUV : TEXCOORD;
};

VTX_OUT_PHONG VS_Phong(VTX_IN _in)
{
    VTX_OUT_PHONG output = (VTX_OUT_PHONG) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    output.vUV = _in.vUV;

    return output;
}

float4 PS_Phong(VTX_OUT_PHONG _in) : SV_Target
{
    float4 vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);

    tLightColor tCol = (tLightColor) 0.f;

    for (int i = 0; i < g_iLight3DCount; ++i)
    {
        CaculateLight(_in.vViewPos, _in.vViewNormal, i, tCol);
    }

    vOutColor.rgb = (tCol.vLightDiff.rgb * vOutColor.rgb) + (tCol.vLightSpec.rgb) + (vOutColor.rgb * tCol.vLightAmb.rgb);
    //vOutColor.rgb = (tCol.vLightDiff.rgb * vOutColor.rgb) + (tCol.vLightSpec.rgb) + (tCol.vLightAmb.rgb);

    return vOutColor;
}















#endif
