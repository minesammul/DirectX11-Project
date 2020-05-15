#include "value.fx"

#ifndef _HLSL_SKYBOX
#define _HLSL_SKYBOX


struct VS_INPUT
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 vOutPos : SV_Position;
    float2 vCenterUV : POSITION;
    float fMaxDistUV : POSITION2;
    float2 vOutUV : TEXCOORD;
};

//========================
// Distortion Shader
// AlphaBlend = false
// PostEffect = true
// g_Tex_0 : Posteffect Target
// g_tex_1 : velocity target
// g_Tex_2 : Position Target
// g_tex_3 : Before target
//========================

VS_OUTPUT VS_Distortion(VS_INPUT _input)
{
    // input 으로 들어온 위치정보를 투영좌표계 까지 변환한다.
    //VS_OUTPUT output = (VS_OUTPUT) 0.f;
   
    //output.vOutPos = mul(float4(_input.vPos, 1.f), g_matWVP);
    //output.vOutUV = _input.vUV;
    VS_OUTPUT output = (VS_OUTPUT) 0.f;

    output.vOutPos.xyz = _input.vPos * 2.f;
    output.vOutPos.z = 0.2f;
    output.vOutPos.w = 1.f;
    output.vOutUV = _input.vUV;
    
    return output;
}

float4 PS_Distortion(VS_OUTPUT _input) : SV_Target
{        
    float2 vScreenUV = float2(_input.vOutPos.x / fTargetWidth, _input.vOutPos.y / fTargetHeight);
    
    //float2 vDir = normalize(float2(0.5f, 0.5f) - _input.vOutUV);
    
    //float fDist = distance(float2(0.5f, 0.5f), _input.vOutUV);

    //// 왜곡 강도에 영향을 주는 중심으로부터 떨어진 비율( 중심에 가까울 수록 0에 가깝다.)
    //float fRatio = (fDist / 0.5f);
    //fRatio = fRatio * (0.2f + (fRatio) * 0.4f);

    //vScreenUV += vDir * sin(abs((fRatio - fAccTime * 0.06f) * 80.f)) * 0.03f;
    
    float4 velocity = g_tex_1.Sample(g_sam_0, _input.vOutUV);
    
    float velocityLength = dot(velocity.xy, velocity.xy);
    
    velocity.xy /= (float) 300;
    
    int sampleCount = 1;
    
    float4 blurColor;
    float4 beforeBlurColor;
    float4 position;
    float4 outputColor = g_tex_0.Sample(g_sam_0, _input.vOutUV);
    
    for (int index = 1; index < 300; index++)
    {
        blurColor = g_tex_0.Sample(g_sam_0, _input.vOutUV + velocity.xy * (float) index);
        beforeBlurColor = g_tex_3.Sample(g_sam_0, _input.vOutUV + velocity.xy * (float) index);
        position = g_tex_2.Sample(g_sam_0, _input.vOutUV + velocity.xy * (float) index);
        
        blurColor += beforeBlurColor;
        
        blurColor /= 2.f;
        
        if (velocityLength > 0.0001f)
        {
            if (velocity.z < position.z + 0.04f)
            {
                sampleCount += 1;
                outputColor += blurColor;
            }
        }
    }
    
    outputColor /= (float) sampleCount;
    
    return outputColor;
}

#endif