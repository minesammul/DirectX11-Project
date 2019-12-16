#ifndef _COMPUTE
#define _COMPUTE

#include "value.fx"
#include "func.fx"

// =======================
// CS_Test
// g_rwtex_0 : ��� �ؽ���
// g_tex_0 : brush 1
// g_tex_1 : brush 2

// g_int_0 : ���̸� width
// g_int_1 : ���̸� height

// g_vec4_0 : ��� ����
// g_vec2_0 : �귯�� �߽� ��ġ(���̸� �»�� ����)
// g_vec2_1 : �귯�� ũ��


// =======================

// SV_GroupID           : �׷� �ε���
// SV_GroupThreadID     : �ش� �׷� �������� ������ �ε���
// SV_GroupIndex        : �ش� �׷쳻������ ����
// SV_DispatchThreadID  : �׷� ��ü���� ������ �ε���

[numthreads(1024, 1, 1)] // 1024
void CS_Test(int3 _iThreadID : SV_DispatchThreadID)
{
    float2 vLTPos = g_vec2_0 - (g_vec2_1 / 2.f); // Brush �»�� ��ġ    
    float2 vThreadPos = float2((float) _iThreadID.x / (float) g_int_0, (float) _iThreadID.y / (float) g_int_1); // �������� ��ġ��
    
    float2 vBrushUV = (vThreadPos - vLTPos) / g_vec2_1; // �귯�� ���� UV ��
    
    if (0.f <= vBrushUV.x && vBrushUV.x <= 1.f
        && 0.f <= vBrushUV.y && vBrushUV.y <= 1.f)
    {
        float fRatio = saturate(cos((distance(g_vec2_0, vThreadPos) / g_vec2_1) * (3.141592 / 0.5f)));
        
        float alpha = g_tex_0.SampleLevel(g_sam_0, vBrushUV, 0).a;
        if (alpha != 0.f)
        {
            g_rwtex_0[_iThreadID.xy] += fDT * fRatio;
        }
    }
}

#endif