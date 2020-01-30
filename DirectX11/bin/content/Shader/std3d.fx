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


// ==================
// 3D Phong Shader (퐁 쉐이딩)
// g_tex_0 : 출력 텍스쳐
// g_tex_1 : 노말 텍스쳐
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

struct PS_OUT_PHONG
{
    float4 vDiffuse : SV_Target0;
    float4 vNormal : SV_Target1;
    float4 vPosition : SV_Target2;
};

VTX_OUT_PHONG VS_Phong(VTX_IN _in)
{
    VTX_OUT_PHONG output = (VTX_OUT_PHONG) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV).xyz;
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV)).xyz;
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV)).xyz;
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV)).xyz;

    output.vUV = _in.vUV;

    return output;
}

PS_OUT_PHONG PS_Phong(VTX_OUT_PHONG _in)
{
    PS_OUT_PHONG output = (PS_OUT_PHONG) 0.f;

    output.vDiffuse.xyz = g_tex_0.Sample(g_sam_0, _in.vUV).xyz;

    float3x3 matTBN =
    {
        _in.vViewTangent,
                        _in.vViewBinormal,
                        _in.vViewNormal
    };

    // 0 ~ 1 사이의 값을 -1 ~ 1 사이로 확장한다.
    float4 vTexNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
    vTexNormal.xyz = (vTexNormal.xyz - 0.5f) * 2.f;
    float3 vViewNormal = mul(vTexNormal.xyz, matTBN);

    output.vNormal.xyz = vViewNormal;
    output.vPosition.xyz = _in.vViewPos;

       
    //tLightColor tCol = (tLightColor) 0.f;

    //for (int i = 0; i < g_iLight3DCount; ++i)
    //{
    //    CaculateLight(_in.vViewPos, vViewNormal, i, tCol);
    //    //CaculateLight(_in.vViewPos, _in.vViewNormal, i, tCol);
    //}     

    //vOutColor.rgb = (tCol.vLightDiff.rgb * vOutColor.rgb) + (tCol.vLightSpec.rgb) + (vOutColor.rgb * tCol.vLightAmb.rgb);

    return output;
}

// ==============================
// STD 3D Shader
// g_tex_0 : 출력 텍스쳐
// g_tex_1 : 노말 텍스쳐
// g_tex_2 : 반사광 텍스쳐
// g_tex_3 : 발광(Emissive) 텍스쳐
// ==============================

struct VTX_STD3D_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float3 vTangent : TANGENT;
    float3 vBinormal : BINORMAL;
    float2 vUV : TEXCOORD;

    float4 vWeights : WEIGHTS;
    float4 vIndices : BLENDINDICES;
    
    // Instancing
    row_major matrix matWorld : WORLD;
    row_major matrix matWV : WV;
    row_major matrix matWVP : WVP;
    int iRowIdx : ROWINDEX; // Animaion 행렬 행

    uint iInstanceID : SV_InstanceID;
};

struct VTX_STD3D_OUT
{
    float4 vPosition : SV_Position;
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
    float3 vViewTangent : TANGENT;
    float3 vViewBinormal : BINORMAL;
    float2 vUV : TEXCOORD;
};

struct PS_STD3D_OUT
{
    float4 vDiffuse : SV_Target0;
    float4 vNormal : SV_Target1;
    float4 vPosition : SV_Target2;
};


VTX_STD3D_OUT VS_STD3D(VTX_STD3D_IN _in)
{
    VTX_STD3D_OUT output = (VTX_STD3D_OUT) 0.f;

     // 8 번째 텍스쳐는 Bone Matrix Tex(VTF - vertex texture fetch) 예약자리
    if (g_tcheck_7)
    {
        Skinning(_in.vPosition, _in.vTangent
        , _in.vBinormal, _in.vNormal
        , _in.vWeights, _in.vIndices, 0);
    }
    
    output.vPosition = mul(float4(_in.vPosition, 1.f), g_matWVP);

    output.vViewPos = mul(float4(_in.vPosition, 1.f), g_matWV).xyz;
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV)).xyz;
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV)).xyz;
    output.vViewNormal = normalize(cross(output.vViewBinormal, output.vViewTangent)).xyz;

    output.vUV = _in.vUV;

    return output;
}

VTX_STD3D_OUT VS_STD3D_Inst(VTX_STD3D_IN _in)
{
    VTX_STD3D_OUT output = (VTX_STD3D_OUT) 0.f;

     // 8 번째 텍스쳐는 Bone Matrix Tex(VTF - vertex texture fetch) 예약자리
    if (g_tcheck_7)
    {
        Skinning(_in.vPosition, _in.vTangent
        , _in.vBinormal, _in.vNormal
        , _in.vWeights, _in.vIndices, _in.iRowIdx); // <-- 변경점
    }
    
    output.vPosition = mul(float4(_in.vPosition, 1.f), _in.matWVP);

    output.vViewPos = mul(float4(_in.vPosition, 1.f), _in.matWV).xyz;
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), _in.matWV)).xyz;
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), _in.matWV)).xyz;
    output.vViewNormal = normalize(cross(output.vViewBinormal, output.vViewTangent)).xyz;

    output.vUV = _in.vUV;

    return output;
}

PS_STD3D_OUT PS_STD3D(VTX_STD3D_OUT _in)
{
    PS_STD3D_OUT output = (PS_STD3D_OUT) 0.f;

    if (g_tcheck_0)
    {
        output.vDiffuse.xyz = g_tex_0.Sample(g_sam_0, _in.vUV).xyz;
    }
    else
    {
        output.vDiffuse.xyz = float3(1.f, 0.f, 1.f);
    }
        
    if (g_tcheck_1)
    {
        float3x3 matTBN =
        {
            _in.vViewTangent,
            _in.vViewBinormal,
            _in.vViewNormal
        };
        
        // 0 ~ 1 사이의 값을 -1 ~ 1 사이로 확장한다.
        float4 vTexNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
        vTexNormal.xyz = (vTexNormal.xyz - 0.5f) * 2.f;
        float3 vViewNormal = mul(vTexNormal.xyz, matTBN);
        
        output.vNormal.xyz = vViewNormal;
    }
    else
    {
        output.vNormal.xyz = _in.vViewNormal;
    }
   
    output.vPosition.xyz = _in.vViewPos;

    return output;
}

// ==============================
// Collider3D Shader
// g_int_0 : Collision Check
// ==============================
VTX_STD3D_OUT VS_COLLIDER3D(VTX_STD3D_IN _in)
{
    VTX_STD3D_OUT output = (VTX_STD3D_OUT) 0.f;
  
    
    output.vPosition = mul(float4(_in.vPosition, 1.f), g_matWorld);
    output.vPosition = mul(output.vPosition, g_matView);
    output.vPosition = mul(output.vPosition, g_matProj);
    
    return output;
}

float4 PS_COLLIDER3D(VTX_STD3D_OUT _in) : SV_Target
{
    float4 output = float4(0.f, 1.0f, 0.f, 1.0f);
    
    if (g_int_0 == 1)
    {
        output = float4(1.f, 0.0f, 0.f, 1.0f);
    }
    
    return output;
}
#endif
