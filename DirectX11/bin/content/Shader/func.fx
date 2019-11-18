#ifndef _FUNC
#define _FUNC

#include "value.fx"

void CaculateLight(float3 _vViewPos, float3 _vViewNormal, int _iLightIdx, inout tLightColor _color)
{
    float fPow = 0.f;
    float fReflectPow = 0.f;
    float3 vLightViewDir = (float3) 0.f;
    float3 vViewReflectDir = (float3) 0.f;
           
    float4 vNormalizeLightDirection = float4(g_arrLight3D[_iLightIdx].vLightDir.xyz, 0.f);

    if (0 == g_arrLight3D[_iLightIdx].iLightType)
    {
        // Directional Light
        //vLightViewDir = mul(float4(g_arrLight3D[_iLightIdx].vLightDir.xyz, 0.f), g_matView);
        vLightViewDir = mul(float4(g_arrLight3D[_iLightIdx].vLightDir.xyz, 0.f), g_matView).xyz;
        fPow = saturate(dot(-vLightViewDir, _vViewNormal));

        // 광원에서 오는 방향 벡터를 노발 벡터 쪽으로 투영시킨 길이
        vViewReflectDir = normalize(vLightViewDir + 2 * dot(-vLightViewDir, _vViewNormal) * _vViewNormal);

        // 시선벡터
        float3 vViewEye = normalize(_vViewPos);
        fReflectPow = saturate(dot(-vViewEye, vViewReflectDir));
        fReflectPow = pow(fReflectPow, 10);
    }
    else if (1 == g_arrLight3D[_iLightIdx].iLightType)
    {
        // Point Light

        // View Space 에서 광원 위치
        float3 vLightViewPos = mul(float4(g_arrLight3D[_iLightIdx].vLightWorldPos.xyz, 1.f), g_matView).xyz;

        // View Space 에서 광원으로 부터 오는 방향
        vLightViewDir = _vViewPos - vLightViewPos;
        float fDistance = length(vLightViewDir);
        vLightViewDir = normalize(vLightViewDir);
       
        // 거리에 따른 비율을 계산
        float fRatio = (g_arrLight3D[_iLightIdx].fLightRange - fDistance) / g_arrLight3D[_iLightIdx].fLightRange;
        fPow = saturate(dot(-vLightViewDir, _vViewNormal));
        fPow *= fRatio;
               
        // 광원에서 오는 방향 벡터를 노발 벡터 쪽으로 투영시킨 길이
        vViewReflectDir = normalize(vLightViewDir + 2 * dot(-vLightViewDir, _vViewNormal) * _vViewNormal);

        // 시선벡터
        float3 vViewEye = normalize(_vViewPos);
        fReflectPow = saturate(dot(-vViewEye, vViewReflectDir));
        fReflectPow = pow(fReflectPow, 10);
    }
    else if (2 == g_arrLight3D[_iLightIdx].iLightType)
    {
        // Spot Light
        float3 vLightViewPos = mul(float4(g_arrLight3D[_iLightIdx].vLightWorldPos.xyz, 1.f), g_matView).xyz;
        
        //float3 vLightViewiDirection = mul(float4(g_arrLight3D[_iLightIdx].vLightDir.xyz, 0.f), g_matView);
        float3 vLightViewiDirection = mul(vNormalizeLightDirection, g_matView).xyz;
        
        vLightViewiDirection = normalize(vLightViewiDirection);

        vLightViewDir = _vViewPos - vLightViewPos;

        float fLightZToPixelAngle = acos(dot(normalize(vLightViewDir), vLightViewiDirection));
        
        if (fLightZToPixelAngle < g_arrLight3D[_iLightIdx].fLightAngle)
        {
            float fDistance = length(vLightViewDir);
            vLightViewDir = normalize(vLightViewDir);

            float fRatio = (g_arrLight3D[_iLightIdx].fLightRange - fDistance) / g_arrLight3D[_iLightIdx].fLightRange;
            fPow = saturate(dot(-vLightViewDir, _vViewNormal));
            fPow *= fRatio;

            // 광원에서 오는 방향 벡터를 노발 벡터 쪽으로 투영시킨 길이
            vViewReflectDir = normalize(vLightViewDir + 2 * dot(-vLightViewDir, _vViewNormal) * _vViewNormal);

            // 시선벡터
            float3 vViewEye = normalize(_vViewPos);
            fReflectPow = saturate(dot(-vViewEye, vViewReflectDir));
            fReflectPow = pow(fReflectPow, 10);
        }
    }


    _color.vLightDiff += g_arrLight3D[_iLightIdx].tColor.vLightDiff * fPow;
    _color.vLightSpec += g_arrLight3D[_iLightIdx].tColor.vLightSpec * fReflectPow;
    _color.vLightAmb += g_arrLight3D[_iLightIdx].tColor.vLightAmb;
}

#endif