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
// 2D Tileset Shader
// g_tex_1 : Samling Texture
// g_int_0 : nxn의 격자의 n의 수
// g_int_1 : Texture에서의 Tile의 수
// g_int_2 : Texture에서의 선택된 Tile
// ==========================
VTX_TEX_OUTPUT VS_TileSet2D(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_TileSet2D(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    float gridSize = (float) 1 / (float) g_int_0;
    int gridNowColumn = _input.vUV.x / gridSize;
    int gridNowRow = _input.vUV.y / gridSize;

    float tileSize = (float) 1 / (float) g_int_1;

    int tileIndex = g_int_0 * gridNowRow + gridNowColumn;
   
    if (tileIndex < g_int_1)
    {
        float2 normalizationGridUV;
        normalizationGridUV.x = _input.vUV.x - gridSize * gridNowColumn;
        normalizationGridUV.x = normalizationGridUV.x / gridSize;

        normalizationGridUV.y = _input.vUV.y - gridSize * gridNowRow;
        normalizationGridUV.y = normalizationGridUV.y / gridSize;

        float2 normalizationTileUV;
        normalizationTileUV.x = normalizationGridUV.x * tileSize + tileIndex * tileSize;
        normalizationTileUV.y = normalizationGridUV.y;

        output.vOutCol = g_tex_0.Sample(g_sam_0, normalizationTileUV);

        if (tileIndex==g_int_2)
        {
            output.vOutCol.g *= 1.5;
        }
    }

    return output;
}

// ==========================
// 2D TileMap Shader
// g_int_1 : Texture에서의 Tile의 수
// g_tex_1 : Samling Texture
// ==========================
VTX_TEX_OUTPUT VS_TileMap2D(VTX_TEX_INPUT _input)
{
    VTX_TEX_OUTPUT output = (VTX_TEX_OUTPUT) 0.f;

    float4 vWorldPos = mul(float4(_input.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProj = mul(vViewPos, g_matProj);

    output.vPos = vProj;
    output.vUV = _input.vUV;
    
    return output;
}

PS_OUT PS_TileMap2D(VTX_TEX_OUTPUT _input)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    float gridSize = (float)1 / (float)g_int_0;

    int gridNowColumn = _input.vUV.x / gridSize;

    int gridNowRow = _input.vUV.y / gridSize;

    float tileSize = (float)1 / (float)g_int_1;

    int tileIndex = g_int_0 * gridNowRow + gridNowColumn;

    int tileComponentBigIndex = tileIndex / 4;
    int tileComponentSmallIndex = tileIndex % 4;

    //int gridReferenceTileIndex = referenceTileIndex[tileIndex];
    int gridReferenceTileIndex = -1;

    //int4 tileComponentsmall = referenceTileIndex[tileComponentBigIndex].referenceIndex;
    int4 tileComponentsmall = g_tileData[tileComponentBigIndex].referenceIndex;

    if (tileComponentSmallIndex == 0)
    {
        gridReferenceTileIndex = tileComponentsmall.x;
    }
    else if (tileComponentSmallIndex == 1)
    {
        gridReferenceTileIndex = tileComponentsmall.y;
    }
    else if (tileComponentSmallIndex == 2)
    {
        gridReferenceTileIndex = tileComponentsmall.z;
    }
    else if (tileComponentSmallIndex == 3)
    {
        gridReferenceTileIndex = tileComponentsmall.w;
    }

    if ((-1 < gridReferenceTileIndex) && (gridReferenceTileIndex < g_int_1))
    {
        float2 normalizationGridUV;

        normalizationGridUV.x = _input.vUV.x - gridSize * gridNowColumn;

        normalizationGridUV.x = normalizationGridUV.x / gridSize;

        normalizationGridUV.y = _input.vUV.y - gridSize * gridNowRow;

        normalizationGridUV.y = normalizationGridUV.y / gridSize;

        float2 normalizationTileUV;

        normalizationTileUV.x = normalizationGridUV.x * tileSize + gridReferenceTileIndex * tileSize;

        normalizationTileUV.y = normalizationGridUV.y;

        output.vOutCol = g_tex_1.Sample(g_sam_0, normalizationTileUV);
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
    if (g_int_0)
        return float4(1.f, 0.2f, 0.2f, 1.f);
    else
        return float4(0.2f, 1.f, 0.2f, 1.f);    
}

#endif