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
    output.vPos = mul(float4(_input.vPos, 1.f), g_matWVP);
    output.vUV = _input.vUV;
    return output;
}

PS_OUT PS_Tex(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;
    output.vOutCol = g_tex_0.Sample(g_sam_0, _input.vUV);
    return output;
}

// ==========================
// Texture UV Animation Shader
// g_tex_0 : Samling Texture
// g_float_0 : u value
// g_float_1 : v value
// g_float4_0 : Color Mul Value
// ==========================
VTX_TEX_OUTPUT VS_TexUV(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;
    
    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_TexUV(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;

    float2 nowUV = _input.vUV;
    nowUV.x += g_float_0;
    nowUV.y += g_float_1;

    //output.vOutCol = g_tex_0.Sample(g_sam_0, _input.vUV);
    output.vOutCol = g_tex_0.Sample(g_sam_0, nowUV);
    //output.vOutCol *= g_float_2;
    output.vOutCol.r *= g_vec4_0.x;
    output.vOutCol.g *= g_vec4_0.g;
    output.vOutCol.b *= g_vec4_0.b;

    return output;
}

// ==========================
// Fade In-Out Shader
// g_tex_0 : Samling Texture
// g_float_0 : Alpha Value
// ==========================
VTX_TEX_OUTPUT VS_Fade(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;
    
    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_Fade(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;

    float2 nowUV = _input.vUV;

    output.vOutCol = g_tex_0.Sample(g_sam_0, nowUV);
    output.vOutCol.r = 0.f;
    output.vOutCol.g = 0.f;
    output.vOutCol.b = 0.f;
    output.vOutCol.a = g_float_0;

    return output;
}


// ==========================
// Inverse Image 2D Shader
// g_tex_0 : Samling Texture
// g_int_0 : inverse on off
// ==========================
VTX_TEX_OUTPUT VS_Inverse2D(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_Inverse2D(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;

    if (g_int_0 == 1)
    {
        _input.vUV.x = 1 - _input.vUV.x;
    }

    if (iAnimCheck)
    {
        float2 vAnimUV = vLT + (vSize * _input.vUV);
        output.vOutCol = g_tex_anim.Sample(g_sam_0, vAnimUV);
    
        //output.vOutCol.r *= g_vec2_0.x;
        //output.vOutCol.gb *= g_vec2_0.y;
    }
    else
    {
        output.vOutCol = g_tex_0.Sample(g_sam_0, _input.vUV);
    }

    return output;
}

// ==========================
// Inverse AfterImage 2D Shader
// g_tex_0 : Samling Texture
// g_int_0 : inverse on off
// g_float_0 : Alpha Value
// ==========================
VTX_TEX_OUTPUT VS_InverseAfterImage2D(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_InverseAfterImage2D(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;

    if (g_int_0 == 1)
    {
        _input.vUV.x = 1 - _input.vUV.x;
    }

    if (iAnimCheck)
    {
        float2 vAnimUV = vLT + (vSize * _input.vUV);
        output.vOutCol = g_tex_anim.Sample(g_sam_0, vAnimUV);
    
        //output.vOutCol.r *= g_vec2_0.x;
        //output.vOutCol.gb *= g_vec2_0.y;
    }
    else
    {
        output.vOutCol = g_tex_0.Sample(g_sam_0, _input.vUV);
    }

    output.vOutCol.r = 1.f;
    output.vOutCol.g = 1.f;
    output.vOutCol.b = 1.f;

    if (output.vOutCol.a > 0.f)
    {
        output.vOutCol.a = g_float_0;
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
       
        //output.vOutCol.r *= g_vec2_0.x;
        //output.vOutCol.gb *= g_vec2_0.y;
    }
    else
    {
        output.vOutCol = g_tex_0.Sample(g_sam_0, _input.vUV);
    }    
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
    //if (g_int_0)
    //    return float4(1.f, 0.2f, 0.2f, 1.f);
    //else
    //    return float4(0.2f, 1.f, 0.2f, 1.f);

    return float4(0.f, 0.f, 0.f, 0.f);

}

#endif