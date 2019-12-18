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
void CS_HeightMap(int3 _iThreadID : SV_DispatchThreadID)
{
    float2 vLTPos = g_vec2_0 - (g_vec2_1 / 2.f); // Brush 좌상단 위치    
    float2 vThreadPos = float2((float) _iThreadID.x / (float) g_int_0, (float) _iThreadID.y / (float) g_int_1); // 스레드의 위치값
    
    float2 vBrushUV = (vThreadPos - vLTPos) / g_vec2_1; // 브러쉬 추출 UV 값
    
    if (0.f <= vBrushUV.x && vBrushUV.x <= 1.f
        && 0.f <= vBrushUV.y && vBrushUV.y <= 1.f)
    {
        float fRatio = saturate(cos((distance(g_vec2_0, vThreadPos) / g_vec2_1.x) * (3.141592 / 0.5f)));
        
        float4 vColor = g_tex_0.SampleLevel(g_sam_0, vBrushUV, 0).a;
        if (vColor.a != 0.f)
        {
            //g_rwtex_0[_iThreadID.xy] += fDT * fRatio * (1.f - (vColor.x * vColor.y * vColor.z)) * vColor.a;
            
            g_rwtex_0[_iThreadID.xy] += fDT * fRatio * (vColor.x * vColor.y * vColor.z);
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
    // 배정된 면을 넘어서는 스레드의 경우 예외러리
    if (_iThreadID.x >= (uint) g_int_0 * 2 || _iThreadID.y >= (uint) g_int_1)
        return;
    
    uint iXFace = _iThreadID.x / 2;
    uint iYFace = _iThreadID.y;

    float3 vLocalPos[3];
    
    // 아래 삼각형
    if (_iThreadID.x % 2 == 0)
    {
        vLocalPos[0] = float3(iXFace, 0.f, g_int_1 - _iThreadID.y);
        vLocalPos[1] = float3(iXFace + 1.f, 0.f, g_int_1 - _iThreadID.y - 1.f);
        vLocalPos[2] = float3(iXFace, 0.f, g_int_1 - _iThreadID.y - 1.f);
    }
    else // 위쪽 삼각형
    {
        vLocalPos[0] = float3(iXFace + 1.f, 0.f, g_int_1 - _iThreadID.y - 1.f);
        vLocalPos[1] = float3(iXFace, 0.f, g_int_1 - _iThreadID.y);
        vLocalPos[2] = float3(iXFace + 1.f, 0.f, g_int_1 - _iThreadID.y);
    }
   
    // 직선과 평면 충돌 여부
    float fResult = 0.f;
    if (IntersectsLay(vLocalPos, g_vec4_0.xyz, g_vec4_1.xyz, fResult))
    {
        float4 vPosition = (float4) 0.f;
        vPosition.xyz = GetIntercestsPos(vLocalPos, g_vec4_0.xyz, g_vec4_1.xyz);
        g_rwtex_0[int2(0, 0)] = vPosition;
    }
}

#endif