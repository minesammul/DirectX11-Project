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
    float2 vFullUV : TEXCOORD1;
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
// g_tex_2 : Height Map

// g_int_0 : Terrain Face X
// g_int_1 : Terrain Face Z
// ====================
VTX_OUT VS_Terrain(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;    
    
    output.vFullUV = float2(_in.vUV.x / (float) g_int_0, _in.vUV.y / (float) g_int_1);
    _in.vPos.y = g_tex_2.SampleLevel(g_sam_0, output.vFullUV, 0.f).x;
    
    float3 vRightPos = _in.vPos;
    vRightPos.x += 0.1f;
    float3 vLeftPos = _in.vPos;
    vLeftPos.x -= 0.1f;
    
    vRightPos.y = g_tex_2.SampleLevel(g_sam_0, float2(output.vFullUV.x + 0.02f, output.vFullUV.y), 0.f).x;
    vLeftPos.y = g_tex_2.SampleLevel(g_sam_0, float2(output.vFullUV.x - 0.02f, output.vFullUV.y), 0.f).x;
           
    float3 vLocalTangent = normalize(vRightPos - vLeftPos);
    float3 vLocalBinormal = float3(0.f, 0.f, 1.f);
    float3 vLocalNormal = normalize(cross(vLocalBinormal, vLocalTangent));
          
    output.vPos = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vViewNormal = normalize(mul(float4(vLocalNormal, 0.f), g_matWV).xyz);
    output.vViewTangent = normalize(mul(float4(vLocalTangent, 0.f), g_matWV).xyz);
    output.vViewBinormal = normalize(mul(float4(vLocalBinormal, 0.f), g_matWV).xyz);
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV).xyz;
    
    output.vUV = _in.vUV;
    
    return output;
}

PS_OUT PS_Terrain(VTX_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    if (g_tcheck_0)    
        output.vDiffuse = g_tex_0.Sample(g_sam_0, _in.vUV);
    else
        output.vDiffuse = float4(1.f, 0.f, 1.f, 1.f);
        
    //if(g_tcheck_1)
    //{
    //    float3x3 matTBN = { _in.vViewTangent, _in.vViewBinormal, _in.vViewNormal };
    //    float3 vViewNormal = g_tex_1.Sample(g_sam_0, _in.vUV).xyz;
    //    vViewNormal = (vViewNormal - 0.5f) * 2.f;
    //    vViewNormal = mul(vViewNormal.xyz, matTBN);
    //    output.vNormal.xyz = vViewNormal;
    //}
    //else
    output.vNormal.xyz = _in.vViewNormal;
    
    output.vPosition.xyz = _in.vViewPos;
    
    return output;
}

// ================
// Tesselation Test
// ================
struct VS_TESS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_TESS_OUT
{
    float3 vPosition : POSITION;
    float2 vUV : TEXCOORD;
};

VS_TESS_OUT VS_Tess(VS_TESS_IN _in)
{
    VS_TESS_OUT output = (VS_TESS_OUT) 0.f;
    
    output.vPosition = _in.vPos;
    output.vUV = _in.vUV;
    
    return output;
}



struct HS_OUT
{
    float3 vPosition : POSITION;
    float2 vUV : TEXCOORD;
};

// HullShader 
// 패치상수함수
struct TessLv
{
    float3 vEdgeFactor : SV_TessFactor;
    float fInsideFactor : SV_InsideTessFactor;
};
    
TessLv PatchConstFunc(InputPatch<VS_TESS_OUT, 3> _patch, uint _patchID : SV_PrimitiveID)
{
    TessLv output = (TessLv) 0.f;
    
    output.vEdgeFactor[0] = 4;
    output.vEdgeFactor[1] = 4;
    output.vEdgeFactor[2] = 4;
    output.fInsideFactor = 1.f;
    
    return output;
}

[domain("tri")]
[partitioning("interger")]
[outputcontrolpoints(3)]
[patchconstfunc("PatchConstFunc")]
[maxtessfactor(64)]
HS_OUT HS_Tess(InputPatch<VS_TESS_OUT, 3> _patch, uint i : SV_OutputControlPointID, uint _patchID : SV_PrimitiveID)
{
    HS_OUT output = (HS_OUT) 0.f;
    
    output.vPosition = _patch[i].vPosition;
    output.vUV = _patch[i].vUV;
    
    return output;
}


// Domain Shader
struct DS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

DS_OUT DS_Tess(OutputPatch<VS_TESS_OUT, 3> _patch, float3 _vRatio : SV_DomainLocation, TessLv _tess)
{
    DS_OUT output = (DS_OUT) 0.f;
    
    float3 vLocalPos = _patch[0].vPosition * _vRatio[0]
                        + _patch[1].vPosition * _vRatio[1]
                        + _patch[2].vPosition * _vRatio[2];
    
    float2 vUV = _patch[0].vUV * _vRatio[0]
                        + _patch[1].vUV * _vRatio[1]
                        + _patch[2].vUV * _vRatio[2];
    
    output.vPosition = mul(float4(vLocalPos, 1.f), g_matWVP);
    output.vUV = vUV;
    
    return output;
}






float4 PS_Tess(VS_TESS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;

    
    return vColor;
}

#endif