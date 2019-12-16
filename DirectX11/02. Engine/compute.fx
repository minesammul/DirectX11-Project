#ifndef _COMPUTE
#define _COMPUTE

#include "value.fx"
#include "func.fx"

// =======================
// CS_Test
// g_rwtex_0 : 출력 텍스쳐
// g_tex_0 : brush 1
// g_tex_1 : brush 2

// g_int_0 : 높이맵 width
// g_int_1 : 높이맵 height

// g_vec4_0 : 출력 색상
// g_vec2_0 : 브러쉬 중심 위치(높이맵 좌상단 기준)
// g_vec2_1 : 브러쉬 크기


// =======================

// SV_GroupID           : 그룹 인덱스
// SV_GroupThreadID     : 해당 그룹 내에서의 스레드 인덱스
// SV_GroupIndex        : 해당 그룹내에서의 순번
// SV_DispatchThreadID  : 그룹 전체기준 스레드 인덱스

[numthreads(1024, 1, 1)] // 1024
void CS_Test(int3 _iThreadID : SV_DispatchThreadID)
{
    float2 vLTPos = g_vec2_0 - (g_vec2_1 / 2.f); // Brush 좌상단 위치    
    float2 vThreadPos = float2((float) _iThreadID.x / (float) g_int_0, (float) _iThreadID.y / (float) g_int_1); // 스레드의 위치값
    
    float2 vBrushUV = (vThreadPos - vLTPos) / g_vec2_1; // 브러쉬 추출 UV 값
    
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