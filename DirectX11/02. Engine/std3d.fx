#ifndef _STD3D
#define _STD3D

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
    float4 vPosition : SV_Position;
    float2 vLightPow : POSITION;
};

struct PS_OUT
{
    float4 vColor1 : SV_Target0;
    float4 vColor2 : SV_Target1;
    float4 vColor3 : SV_Target2;
    float4 vColor4 : SV_Target3;
};

// ==================
// 3D Phong Shader (�� ���̵�)
// g_tex_0 : ��� �ؽ���
// g_tex_1 : �븻 �ؽ���
// ==================
struct VTX_OUT_PHONG
{
    float4 vPosition : SV_Position;
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
    float3 vViewTangent : TANGENT;
    float3 vViewBinormal : BINORMAL;
    float2 vUV : TEXCOORD;
};

VTX_OUT_PHONG VS_Phong(VTX_IN _in)
{
    VTX_OUT_PHONG output = (VTX_OUT_PHONG) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV));
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV));

    output.vUV = _in.vUV;

    return output;
}

float4 PS_Phong(VTX_OUT_PHONG _in) : SV_Target
{
    float4 vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);

    float3x3 matTBN = { _in.vViewTangent,
                        _in.vViewBinormal,
                        _in.vViewNormal};

    // 0 ~ 1 ������ ���� -1 ~ 1 ���̷� Ȯ���Ѵ�.
    float4 vTexNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
    vTexNormal.xyz = (vTexNormal.xyz - 0.5f) * 2.f;
    float3 vViewNormal = mul(vTexNormal.xyz, matTBN);
       
    tLightColor tCol = (tLightColor) 0.f;

    for (int i = 0; i < g_iLight3DCount; ++i)
    {
        CaculateLight(_in.vViewPos, vViewNormal, i, tCol);
        //CaculateLight(_in.vViewPos, _in.vViewNormal, i, tCol);
    }

    vOutColor.rgb = (tCol.vLightDiff.rgb * vOutColor.rgb) + (tCol.vLightSpec.rgb) + (vOutColor.rgb * tCol.vLightAmb.rgb);

    return vOutColor;
}















#endif
