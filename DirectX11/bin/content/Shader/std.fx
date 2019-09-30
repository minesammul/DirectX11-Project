#include "value.fx"

#ifndef _STD
#define _STD

// ===================
// Vertex Color Shader
// ===================
struct VTX_INPUT
{
    float3 vPos : POSITION;
    float4 vCol : COLOR;
};

struct VTX_OUTPUT
{
    float4 vPos : SV_Position;
    float4 vCol : COLOR;
};

VTX_OUTPUT VS(VTX_INPUT _input)
{
    VTX_OUTPUT output = (VTX_OUTPUT) 0.f;   
    
    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vCol = _input.vCol;
    
    return output;
}

// 픽셀 쉐이더의 입력 값은, 각 정점으로부터의 거리에 따른 보간값이 들어온다.(레스터라이져 단계에서 계산됨)
struct PS_OUT
{
    float4 vOutCol : SV_Target;
};

PS_OUT PS(VTX_OUTPUT _input)
{    
    PS_OUT output = (PS_OUT) 0.f;
    output.vOutCol = _input.vCol;
    return output;
}

// ==========================
// Texture Shader
// g_tex_0 : Samling Texture
// ==========================
struct VTX_TEX_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VTX_TEX_OUTPUT
{
    float4 vPos : SV_Position;
    float2 vUV : TEXCOORD;
};

VTX_TEX_OUTPUT VS_Tex(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;
    
    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_Tex(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;
    output.vOutCol = g_tex_0.Sample( g_sam_0 , _input.vUV);    
    
    if (g_int_0)
    {
        output.vOutCol.r *= 1.1f;
        output.vOutCol.g *= 0.2f;
        output.vOutCol.b *= 0.2f;
    }

    return output;
}

// ==========================
// Std 2D Shader
// g_tex_0 : Samling Texture
// g_vec2_0 : Hilight Ratio
// ==========================
VTX_TEX_OUTPUT VS_Std2D(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;
    
    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_Std2D(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;       

    if (iAnimCheck)
    {
        float2 vAnimUV = vLT + (vSize * _input.vUV);   
        output.vOutCol = g_tex_anim.Sample(g_sam_0, vAnimUV);        
       
        output.vOutCol.r *= g_vec2_0.x;
        output.vOutCol.gb *= g_vec2_0.y;
    }
    else
    {
        output.vOutCol = g_tex_0.Sample(g_sam_0, _input.vUV);
    }      
    
    //dgkim Start
    //Shader Parameter test 용도
    if (g_vec4_0.z == 3.f)
    {
        output.vOutCol = float4(1.f, 0.f, 0.f, 1.f);
    }

    if (g_mat_0._11 == 3.f)
    {
        output.vOutCol = float4(0.f, 0.f, 1.f, 1.f);
    }
    //dgkim End

    return output;
}


// ==========================
// Collider2D Shader
// g_int_0 : Collision Check
// ==========================
VTX_TEX_OUTPUT VS_Collider2D(VTX_TEX_INPUT _input)
{    
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);

    output.vPos = mul(vViewPos, g_matProj);
    output.vUV = _input.vUV;

    return output;
}

float4 PS_Collider2D(VTX_TEX_OUTPUT _input) : SV_Target
{  
    if (g_int_0)
        return float4(1.f, 0.2f, 0.2f, 1.f);
    else
        return float4(0.2f, 1.f, 0.2f, 1.f);    
}

#endif