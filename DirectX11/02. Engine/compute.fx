#ifndef _COMPUTE
#define _COMPUTE

#include "value.fx"
#include "func.fx"

// =======================
// CS_Test
// g_rwtex_0 : ��� �ؽ���
// =======================

// SV_GroupID           : �׷� �ε���
// SV_GroupThreadID     : �ش� �׷� �������� ������ �ε���
// SV_GroupIndex        : �ش� �׷쳻������ ����
// SV_DispatchThreadID  : �׷� ��ü���� ������ �ε���

[numthreads(100, 1, 1)] // 1024
void CS_Test(int3 _iThreadID : SV_DispatchThreadID)
{
    if (_iThreadID.y == 49)
    {
        g_rwtex_0[_iThreadID.xy] = float4(1.f, 0.f, 0.f, 1.f);
    }    
}


#endif