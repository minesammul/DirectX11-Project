#ifndef _TERRAIN
#define _TERRAIN

#include "value.fx"
#include "func.fx"
static float g_fMaxTess = 16.f;

struct VS_TERRAIN_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_TERRAIN_OUT
{
    float3 vLocalPos : POSITION;
    float2 vUV : TEXCOORD;
    float2 vFullUV : TEXCOORD1;
};

struct PS_TERRAIN_OUT
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
VS_TERRAIN_OUT VS_Terrain(VS_TERRAIN_IN _in)
{
    VS_TERRAIN_OUT output = (VS_TERRAIN_OUT) 0.f;
    
    output.vLocalPos = _in.vPos;
    output.vUV = _in.vUV;
    output.vFullUV = float2(_in.vUV.x / (float) g_int_0, _in.vUV.y / (float) g_int_1);
    
    return output;
}

// HullShader 
// 패치상수함수
struct TessLv
{
    float vEdgeFactor[3] : SV_TessFactor;
    float fInsideFactor : SV_InsideTessFactor;
};
    
TessLv TerrainPatchConstFunc(InputPatch<VS_TERRAIN_OUT, 3> _patch, uint _patchID : SV_PrimitiveID)
{
    TessLv output = (TessLv) 0.f;
    
    output.vEdgeFactor[0] = 16;
    output.vEdgeFactor[1] = 16;
    output.vEdgeFactor[2] = 16;
    output.fInsideFactor = 16.f;
    
    return output;
}

[domain("tri")]
[partitioning("integer")]
[outputcontrolpoints(3)]
[patchconstantfunc("TerrainPatchConstFunc")]
[maxtessfactor(64.f)]
[outputtopology("triangle_cw")]
VS_TERRAIN_OUT HS_Terrain(InputPatch<VS_TERRAIN_OUT, 3> _patch, uint i : SV_OutputControlPointID, uint _patchID : SV_PrimitiveID)
{
    VS_TERRAIN_OUT output = (VS_TERRAIN_OUT) 0.f;
    
    output.vLocalPos = _patch[i].vLocalPos;
    
    output.vUV = _patch[i].vUV;
    output.vFullUV = _patch[i].vFullUV;
    
    return output;
}

struct DS_TERRAIN_OUT
{
    float4 vPosition : SV_Position;
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
    float3 vViewTangent : TANGENT;
    float3 vViewBinormal : BINORMAL;
    float2 vUV : TEXCOORD;
    float2 vFullUV : TEXCOORD1;
};


[domain("tri")]
DS_TERRAIN_OUT DS_Terrain(OutputPatch<VS_TERRAIN_OUT, 3> _patch, float3 _vRatio : SV_DomainLocation, TessLv _tess)
{
    DS_TERRAIN_OUT output = (DS_TERRAIN_OUT) 0.f;
    
    output.vUV = _patch[0].vUV * _vRatio[0]
                        + _patch[1].vUV * _vRatio[1]
                        + _patch[2].vUV * _vRatio[2];
    
    
    output.vFullUV = _patch[0].vFullUV * _vRatio[0]
                        + _patch[1].vFullUV * _vRatio[1]
                        + _patch[2].vFullUV * _vRatio[2];
    
    float3 vLocalPos = _patch[0].vLocalPos * _vRatio[0]
                        + _patch[1].vLocalPos * _vRatio[1]
                        + _patch[2].vLocalPos * _vRatio[2];
    
    vLocalPos.y = g_tex_2.SampleLevel(g_sam_0, output.vFullUV, 0).x;
    
    output.vPosition = mul(float4(vLocalPos, 1.f), g_matWVP);
    output.vViewPos = mul(float4(vLocalPos, 1.f), g_matWV).xyz;
    
    // Texcell UV Step
    float2 vUVStep = float2(1.f / (float) g_int_0 * g_fMaxTess, 1.f / (float) g_int_1 * g_fMaxTess);
    
    float3 vRightPos = vLocalPos;
    vRightPos.x += 1.f;
    
    float3 vLeftPos = vLocalPos;
    vLeftPos.x -= 1.f;
    
    float3 vUpPos = vLocalPos;
    vUpPos.z += 1.f;
    
    float3 vDownPos = vLocalPos;
    vDownPos.z -= 1.f;
    
    float2 vNearUV = output.vFullUV;
    vNearUV.x += vUVStep.x;
    vRightPos.y = g_tex_2.SampleLevel(g_sam_0, vNearUV, 0).x;
    
    vNearUV.x -= vUVStep.x * 2.f;
    vLeftPos.y = g_tex_2.SampleLevel(g_sam_0, vNearUV, 0).x;
   
    vNearUV = float2(output.vFullUV.x, output.vFullUV.y - vUVStep.y);
    vUpPos.y = g_tex_2.SampleLevel(g_sam_0, vNearUV, 0).x;
    
    vNearUV = float2(output.vFullUV.x, output.vFullUV.y + vUVStep.y);
    vDownPos.y = g_tex_2.SampleLevel(g_sam_0, vNearUV, 0).x;
    
    float3 vTangent = normalize(vRightPos - vLeftPos);
    float3 vBinormal = normalize(vUpPos - vDownPos);
    float3 vNormal = cross(vBinormal, vTangent);
    
    output.vViewTangent = mul(float4(vTangent, 0.f), g_matWV);
    output.vViewBinormal = mul(float4(vBinormal, 0.f), g_matWV);
    output.vViewNormal = mul(float4(vNormal, 0.f), g_matWV);
        
    return output;
}


PS_TERRAIN_OUT PS_Terrain(DS_TERRAIN_OUT _in)
{
    PS_TERRAIN_OUT output = (PS_TERRAIN_OUT) 0.f;
    
    if (g_tcheck_0) 
        output.vDiffuse = g_tex_0.Sample(g_sam_0, _in.vUV);
    else
        output.vDiffuse = float4(1.f, 0.f, 1.f, 1.f);
        
    output.vDiffuse = float4(1.f, 1.f, 1.f, 1.f);
    
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
    
TessLv PatchConstFunc(InputPatch<VS_TESS_OUT, 3> _patch, uint _patchID : SV_PrimitiveID)
{
    TessLv output = (TessLv) 0.f;
    
    output.vEdgeFactor[0] = 16;
    output.vEdgeFactor[1] = 16;
    output.vEdgeFactor[2] = 16;
    output.fInsideFactor = 8.f;
    
    return output;
}


[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstFunc")]
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

[domain("tri")]
DS_OUT DS_Tess(OutputPatch<HS_OUT, 3> _patch, float3 _vRatio : SV_DomainLocation, TessLv _tess)
{
    DS_OUT output = (DS_OUT) 0.f;
    
    float3 vLocalPos;
    vLocalPos = _patch[0].vPosition * _vRatio.x + _patch[1].vPosition * _vRatio.y + _patch[2].vPosition * _vRatio.z;
    
    float2 vUV;
    vUV = _patch[0].vUV * _vRatio.x + _patch[1].vUV * _vRatio.y + _patch[2].vUV * _vRatio.z;
    
    output.vPosition = mul(float4(vLocalPos, 1.f), g_matWVP);
    output.vUV = vUV;
    
    return output;
}






float4 PS_Tess(DS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    vColor.a = 1.f;
    
    return vColor;
}

#endif