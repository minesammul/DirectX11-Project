
#include "value.fx"

#ifndef _STD3D
#define _STD3D

struct VTX_IN
{
    float3 vPos : POSITION;
    float3 vNormal : NORMAL;
};


struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vLightPow : POSITION;
};

// ==================
// 3D Gouraud Shader (��� ���̵�)
// ==================
VTX_OUT VS_Gouraud(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);  
    
    float3 vNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));

    float fPow = dot(-g_arrLight3D[0].vLightDir, vNormal);

    output.vLightPow.x = saturate(fPow);

    return output;
}

float4 PS_Gouraud(VTX_OUT _in) : SV_Target
{
    float4 vOutColor = float4(1.f, 1.f, 1.f, 1.f);

    vOutColor.rgb *= g_arrLight3D[0].vLightColor * _in.vLightPow.x;

    return vOutColor;
}

// ==================
// 3D Phong Shader (�� ���̵�)
// ==================
struct VTX_OUT_PHONG
{
    float4 vPosition : SV_Position;
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
};

VTX_OUT_PHONG VS_Phong(VTX_IN _in)
{
    VTX_OUT_PHONG output = (VTX_OUT_PHONG) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    
    return output;
}

float4 PS_Phong(VTX_OUT_PHONG _in) : SV_Target
{
    float fPow = 0.f;
    float fReflectPow = 0.f;
    float3 vLightViewDir = (float3) 0.f;
    float3 vViewReflectDir = (float3) 0.f;
           
    // Directional Light
    if (0 == g_arrLight3D[0].iLightType)
    {
        vLightViewDir = mul(float4(g_arrLight3D[0].vLightDir, 0.f), g_matView);
        fPow = saturate(dot(-vLightViewDir, _in.vViewNormal));

        // �������� ���� ���� ���͸� ��� ���� ������ ������Ų ����
        vViewReflectDir = normalize(vLightViewDir + 2 * dot(-vLightViewDir, _in.vViewNormal) * _in.vViewNormal);

        // �ü�����
        float3 vViewEye = normalize(_in.vViewPos);
        fReflectPow = saturate(dot(-vViewEye, vViewReflectDir));
        fReflectPow = pow(fReflectPow, 10);
    }
    else if (1 == g_arrLight3D[0].iLightType)
    {
        // View Space ���� ���� ��ġ
        float3 vLightViewPos = mul(float4(g_arrLight3D[0].vLightWorldPos, 1.f), g_matView);

        // View Space ���� �������� ���� ���� ����
        vLightViewDir = _in.vViewPos - vLightViewPos;
        float fDistance = length(vLightViewDir);
        vLightViewDir = normalize(vLightViewDir);
       
        // �Ÿ��� ���� ������ ���
        float fRatio = (g_arrLight3D[0].fLightRange - fDistance) / g_arrLight3D[0].fLightRange;
        fPow = saturate(dot(-vLightViewDir, _in.vViewNormal));
        fPow *= fRatio;


        // �������� ���� ���� ���͸� ��� ���� ������ ������Ų ����
        vViewReflectDir = normalize(vLightViewDir + 2 * dot(-vLightViewDir, _in.vViewNormal) * _in.vViewNormal);

        // �ü�����
        float3 vViewEye = normalize(_in.vViewPos);
        fReflectPow = saturate(dot(-vViewEye, vViewReflectDir));
        fReflectPow = pow(fReflectPow, 10);
    }

    float4 vOutColor = float4(1.f, 1.f, 1.f, 1.f);

    vOutColor.rgb = (vOutColor.rgb * g_arrLight3D[0].vLightColor * fPow)
                    + (g_arrLight3D[0].vLightColor * fReflectPow * 0.3f);

    return vOutColor;
}















#endif
