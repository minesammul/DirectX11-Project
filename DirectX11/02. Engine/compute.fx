#ifndef _COMPUTE
#define _COMPUTE

#include "value.fx"
#include "func.fx"

// =======================
// CS_Test
// g_rwtex_0 : 출력 텍스쳐
// =======================

// SV_GroupID           : 그룹 인덱스
// SV_GroupThreadID     : 해당 그룹 내에서의 스레드 인덱스
// SV_GroupIndex        : 해당 그룹내에서의 순번
// SV_DispatchThreadID  : 그룹 전체기준 스레드 인덱스

[numthreads(100, 1, 1)] // 1024
void CS_Test(int3 _iThreadID : SV_DispatchThreadID)
{
    if (_iThreadID.y == 49)
    {
        g_rwtex_0[_iThreadID.xy] = float4(1.f, 0.f, 0.f, 1.f);
    }    
}


#endif