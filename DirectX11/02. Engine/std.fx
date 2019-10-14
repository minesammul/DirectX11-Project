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

// �ȼ� ���̴��� �Է� ����, �� �������κ����� �Ÿ��� ���� �������� ���´�.(�����Ͷ����� �ܰ迡�� ����)
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
// g_tex_0 : Samling Texture
// g_int_0 : nxn�� ������ n�� ��
// g_int_1 : Texture������ Tile�� ��
// g_int_2 : Texture������ ���õ� Tile
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
// g_tex_0 : Samling Texture
// g_int_0 : ������ ��
// g_int_1 : ������ ��
// g_int_2 : Texture�� Tile Index
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
    //�ӽ��ڵ� ���߿� ���� Ÿ�ϸ� ���̴��� �ۼ��Ѵ�.
    //�ش� �ڵ�� ���� ����� Ÿ�ϸʿ� ���� ���̴� �ڵ��.
    //float tileSizeX = _input.vPos.x / g_int_0;
    //float tileSizeY = _input.vPos.y / g_int_0;
    //_input.vPos.x /= g_int_0;
    //_input.vPos.y /= g_int_0;
    //int repeatCount = g_int_0 - 1;
    //for (int index = 0; index < repeatCount; index++)
    //{
    //    if (tileSizeX < 0)
    //    {
    //        _input.vPos.x += tileSizeX;
    //    }
    //    else
    //    {
    //        _input.vPos.x -= tileSizeX;
    //    }

    //    if(tileSizeY > 0)
    //    {
    //        _input.vPos.y += tileSizeY;
    //    }
    //    else
    //    {
    //        _input.vPos.y -= tileSizeY;
    //    }
    //}

    //_input.vPos.x += tileSizeX * g_vec2_0.x;
    //_input.vPos.y -= tileSizeY * g_vec2_0.y;
    //
    _input.vPos.x /= 16;
    _input.vPos.y /= 16;

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
        _input.vUV.x /= 487;
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