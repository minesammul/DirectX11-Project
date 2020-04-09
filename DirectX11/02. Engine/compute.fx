#ifndef _COMPUTE
#define _COMPUTE

#include "value.fx"
#include "func.fx"

// ==============
// Texture Clear
// g_int_0 : width
// g_int_1 : height
// g_vec4_0 : clear color
// g_rwtex_0 : clear texture
// ==============
[numthreads(32, 32, 1)] // 1024
void CS_Clear(int3 _iThreadID : SV_DispatchThreadID)
{
    if (g_int_0 <= _iThreadID.x || g_int_1 <= _iThreadID.y)
        return;
    
    g_rwtex_0[_iThreadID.xy] = g_vec4_0;
}

// =======================
// CS_Height
// g_rwtex_0 : ��� �ؽ���
// g_tex_0 : brush

// g_int_0 : ���̸� width
// g_int_1 : ���̸� height
// g_int_2 : 1==Up, -1==Down

// g_vec4_0 : ��� ����
// g_vec2_0 : �귯�� �߽� ��ġ(���̸� �»�� ����)
// g_vec2_1 : �귯�� ũ��


// =======================

// SV_GroupID           : �׷� �ε���
// SV_GroupThreadID     : �ش� �׷� �������� ������ �ε���
// SV_GroupIndex        : �ش� �׷쳻������ ����
// SV_DispatchThreadID  : �׷� ��ü���� ������ �ε���

[numthreads(1024, 1, 1)] // 1024
void CS_HeightMap(int3 _iThreadID : SV_DispatchThreadID)
{
    float2 vLTPos = g_vec2_0 - (g_vec2_1 / 2.f); // Brush �»�� ��ġ    
    float2 vThreadPos = float2((float) _iThreadID.x / (float) g_int_0, (float) _iThreadID.y / (float) g_int_1); // �������� ��ġ��
    
    float2 vBrushUV = (vThreadPos - vLTPos) / g_vec2_1; // �귯�� ���� UV ��
    
    if (0.f <= vBrushUV.x && vBrushUV.x <= 1.f
        && 0.f <= vBrushUV.y && vBrushUV.y <= 1.f)
    {
        float fRatio = saturate(cos((distance(g_vec2_0, vThreadPos) / (g_vec2_1.x / 2.f)) * (3.141592 / 2.f)));
        
        float4 vColor = g_tex_0.SampleLevel(g_sam_0, vBrushUV, 0).a;
        if (vColor.a != 0.f)
        {
            if (g_int_2 >= 0)
            {

                g_rwtex_0[_iThreadID.xy] += fDT * fRatio * (vColor.x * vColor.y * vColor.z);
            }
            else
            {
                g_rwtex_0[_iThreadID.xy] -= fDT * fRatio * (vColor.x * vColor.y * vColor.z);

            }
        }
    }
}

// =======================
// CS_Weight
// g_rwtex_0 : ��� �ؽ��� (weight texture)
// g_tex_0 : brush

// g_int_0 : ���̸� width
// g_int_1 : ���̸� height

// g_int_2 : Tile Index (����ġ�� �ø� Ÿ��)

// g_vec4_0 : ��� ����
// g_vec2_0 : �귯�� �߽� ��ġ(���̸� �»�� ����)
// g_vec2_1 : �귯�� ũ��
// =======================

[numthreads(1024, 1, 1)] // 1024
void CS_Weight(int3 _iThreadID : SV_DispatchThreadID)
{
    float2 vLTPos = g_vec2_0 - (g_vec2_1 / 2.f); // Brush �»�� ��ġ    
    float2 vThreadPos = float2((float) _iThreadID.x / (float) g_int_0, (float) _iThreadID.y / (float) g_int_1); // �������� ��ġ��
    
    float2 vBrushUV = (vThreadPos - vLTPos) / g_vec2_1; // �귯�� ���� UV ��
    
    if (0.f <= vBrushUV.x && vBrushUV.x <= 1.f
        && 0.f <= vBrushUV.y && vBrushUV.y <= 1.f)
    {
        float fRatio = saturate(cos((distance(g_vec2_0, vThreadPos) / (g_vec2_1.x / 2.f)) * (3.141592 / 2.f)));
        
        float vAlpha = g_tex_0.SampleLevel(g_sam_0, vBrushUV, 0).a;
        if (vAlpha != 0.f)
        {
            float fAdd = fDT * fRatio * vAlpha * 4.f;
            float4 vOrigin = g_rwtex_0[_iThreadID.xy];
            if (g_int_2 == 0)
            {
                vOrigin[0] += fAdd;
                if (vOrigin[0] > 1.f)
                    vOrigin[0] = 1.f;
                
                float fOver = vOrigin[0] + vOrigin[1] + vOrigin[2] + vOrigin[3] - 1.f;
                if (fOver < 0.f)
                    fOver = 0.f;
                
                float fRest = vOrigin[1] + vOrigin[2] + vOrigin[3];
                if (fRest == 0.f)
                    fRest = 1.f;
                
                vOrigin[1] -= fOver * (vOrigin[1] / fRest);
                vOrigin[2] -= fOver * (vOrigin[2] / fRest);
                vOrigin[3] -= fOver * (vOrigin[3] / fRest);
                
                g_rwtex_0[_iThreadID.xy] = vOrigin;
            }
            else if (g_int_2 == 1)
            {
                vOrigin[1] += fAdd;
                if (vOrigin[1] > 1.f)
                    vOrigin[1] = 1.f;
                
                float fOver = vOrigin[0] + vOrigin[1] + vOrigin[2] + vOrigin[3] - 1.f;
                if (fOver < 0.f)
                    fOver = 0.f;
                
                float fRest = vOrigin[0] + vOrigin[2] + vOrigin[3];
                if (fRest == 0.f)
                    fRest = 1.f;
                
                vOrigin[0] -= fOver * (vOrigin[0] / fRest);
                vOrigin[2] -= fOver * (vOrigin[2] / fRest);
                vOrigin[3] -= fOver * (vOrigin[3] / fRest);
                
                g_rwtex_0[_iThreadID.xy] = vOrigin;
            }
            else if (g_int_2 == 2)
            {
                vOrigin[2] += fAdd;
                if (vOrigin[2] > 1.f)
                    vOrigin[2] = 1.f;
                
                float fOver = vOrigin[0] + vOrigin[1] + vOrigin[2] + vOrigin[3] - 1.f;
                if (fOver < 0.f)
                    fOver = 0.f;
                
                float fRest = vOrigin[0] + vOrigin[1] + vOrigin[3];
                if (fRest == 0.f)
                    fRest = 1.f;
                
                vOrigin[0] -= fOver * (vOrigin[0] / fRest);
                vOrigin[1] -= fOver * (vOrigin[1] / fRest);
                vOrigin[3] -= fOver * (vOrigin[3] / fRest);
                
                g_rwtex_0[_iThreadID.xy] = vOrigin;
            }
            else if (g_int_2 == 3)
            {
                vOrigin[3] += fAdd;
                if (vOrigin[3] > 1.f)
                    vOrigin[3] = 1.f;
                
                float fOver = vOrigin[0] + vOrigin[1] + vOrigin[2] + vOrigin[3] - 1.f;
                if (fOver < 0.f)
                    fOver = 0.f;
                
                float fRest = vOrigin[0] + vOrigin[1] + vOrigin[2];
                if (fRest == 0.f)
                    fRest = 1.f;
                
                vOrigin[0] -= fOver * (vOrigin[0] / fRest);
                vOrigin[1] -= fOver * (vOrigin[1] / fRest);
                vOrigin[2] -= fOver * (vOrigin[2] / fRest);
                
                g_rwtex_0[_iThreadID.xy] = vOrigin;
            }
        }
    }
}

// =======================
// Picking Shader
// g_int_0 : Face X
// g_int_1 : Face Z

// g_vec4_0 : Ray Start
// g_vec4_1 : Ray Dir

// g_tex_0 : Height Map
// g_rwtex_0 : output texture
// =======================
[numthreads(32, 32, 1)]
void CS_Picking(uint3 _iThreadID : SV_DispatchThreadID)
{
    // ������ ���� �Ѿ�� �������� ��� ���ܷ���
    if (_iThreadID.x >= (uint) g_int_0 * 2 || _iThreadID.y >= (uint) g_int_1)
        return;
    
    uint iXFace = _iThreadID.x / 2;
    uint iYFace = _iThreadID.y;

    float3 vLocalPos[3];
    
    // �Ʒ� �ﰢ��
    if (_iThreadID.x % 2 == 0)
    {
        vLocalPos[0] = float3(iXFace, 0.f, g_int_1 - _iThreadID.y);
        vLocalPos[1] = float3(iXFace + 1.f, 0.f, g_int_1 - _iThreadID.y - 1.f);
        vLocalPos[2] = float3(iXFace, 0.f, g_int_1 - _iThreadID.y - 1.f);
    }
    else // ���� �ﰢ��
    {
        vLocalPos[0] = float3(iXFace + 1.f, 0.f, g_int_1 - _iThreadID.y - 1.f);
        vLocalPos[1] = float3(iXFace, 0.f, g_int_1 - _iThreadID.y);
        vLocalPos[2] = float3(iXFace + 1.f, 0.f, g_int_1 - _iThreadID.y);
    }
   
    // ������ ��� �浹 ����
    float fResult = 0.f;
    if (IntersectsLay(vLocalPos, g_vec4_0.xyz, g_vec4_1.xyz, fResult))
    {
        float4 vPosition = (float4) 0.f;
        vPosition.xyz = GetIntercestsPos(vLocalPos, g_vec4_0.xyz, g_vec4_1.xyz);
        vPosition.w = distance(g_vec4_0.xyz, vPosition.xyz);
        g_rwtex_0[int2(0, 0)] = vPosition;
    }
}


// =======================
// HeightMap Value Shader
// g_vec2_0 : input UV

// g_tex_0 : Height Map
// g_rwtex_0 : output texture
// =======================
[numthreads(1, 1, 1)]
void CS_HeightMapValue(uint3 _iThreadID : SV_DispatchThreadID)
{
    float4 height = g_tex_0.SampleLevel(g_sam_0, g_vec2_0, 0);
    g_rwtex_0[int2(0, 0)] = height;
}
#endif