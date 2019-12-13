#ifndef _COMPUTE
#define _COMPUTE

#include "value.fx"
#include "func.fx"

// =======================
// CS_Test
// g_rwtex_0 : 출력 텍스쳐
// g_vec4_0 : 출력 색상
// =======================

// SV_GroupID           : 그룹 인덱스
// SV_GroupThreadID     : 해당 그룹 내에서의 스레드 인덱스
// SV_GroupIndex        : 해당 그룹내에서의 순번
// SV_DispatchThreadID  : 그룹 전체기준 스레드 인덱스

[numthreads(1024, 1, 1)] // 1024
void CS_Test(int3 _iThreadID : SV_DispatchThreadID)
{
    //float fDist = distance((float2) _iThreadID, float2(512.f, 512.f));
    //float fTheta = (fDist / 512.f) * (3.141592 / 2.f);
    
    //float fHeight = cos(fTheta);
    //if (fHeight < 0.f)
    //    fHeight = 0.f;
    
    //g_rwtex_0[_iThreadID.xy] += fHeight / 10.f;
    g_rwtex_0[_iThreadID.xy] = float4(1.f, 0.f, 0.f, 1.f);

}


#endif