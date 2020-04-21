#ifndef _LIGHT
#define _LIGHT

#include "value.fx"
#include "func.fx"

// =========================
// DirLight Shader
// mesh : Rect Mesh
// g_tex_0 : NormalTarget
// g_tex_1 : PositionTarget

// g_tex_2 : Light Shadow Map

// g_mat_0 : Light VP(View, Proj)
// g_mat_1 : Main Camera Inv View Matrix

// g_int_0 : Light Index ( 광원 버퍼에서 자신의 인덱스)
// =========================

struct VTX_IN
{
    float3 vPosition : POSITION;
    float2 vUV : TEXCOORD;
};

struct VTX_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

struct PS_OUT
{
    float4 vDiffuseLight : SV_Target;
    float4 vSpecularLight : SV_Target1;
};

VTX_OUT VS_DirLight(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition.xyz = _in.vPosition * 2.f;
    output.vPosition.w = 1.f;
    output.vUV = _in.vUV;
    
    return output;
}

PS_OUT PS_DirLight(VTX_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    float4 vViewPos = g_tex_1.Sample(g_sam_0, _in.vUV);
    if (vViewPos.z == 0.f)
        clip(-1);
    
    float4 vViewNormal = g_tex_0.Sample(g_sam_0, _in.vUV);
    
    tLightColor color = (tLightColor) 0.f;
    CaculateLight(vViewPos.xyz, vViewNormal.xyz, g_int_0, color);
    
     // 그림자 판정    
    // 빛이 없으면 그림자 처리를 하지 않는다.
    if (dot(color.vLightDiff, color.vLightDiff) != 0.f)
    {
        float4 vWorldPos = mul(float4(vViewPos.xyz, 1.f), g_mat_1); // 메인카메라 view 역행렬을 곱해서 월드좌표를 알아낸다.
        float4 vShadowProj = mul(vWorldPos, g_mat_0); // 광원 시점으로 투영시킨 좌표 구하기
        float fDepth = vShadowProj.z / vShadowProj.w; // w 로 나눠서 실제 투영좌표 z 값을 구한다.(올바르게 비교하기 위해서)
    
        // 계산된 투영좌표를 UV 좌표로 변경해서 ShadowMap 에 기록된 깊이값을 꺼내온다.
        float2 vShadowUV = float2((vShadowProj.x / vShadowProj.w) * 0.5f + 0.5f
                           , (vShadowProj.y / vShadowProj.w) * -0.5f + 0.5f);
    
        if (0.01f < vShadowUV.x && vShadowUV.x < 0.99f
        && 0.01f < vShadowUV.y && vShadowUV.y < 0.99f)
        {
            float fShadowDepth = g_tex_2.Sample(g_sam_0, vShadowUV).r;
      
            // 그림자인 경우 빛을 약화시킨다.
            if (fDepth > fShadowDepth + 0.0001f)
            {
                color.vLightDiff *= 0.1f;
                color.vLightSpec = (float4) 0.f;
            }
        }
    }
    
    output.vDiffuseLight = color.vLightDiff + color.vLightAmb;
    output.vSpecularLight = color.vLightSpec;
    
    return output;
}

// =========================
// PointLight Shader
// mesh : Sphere
// Rasterizer : CULL_FRONT
// BlendState : One-One
// DepthStencilState : NO_DEPTH, NO_WRITE

// Parameter
// g_tex_0 : NormalTarget
// g_tex_1 : PositionTarget
// g_int_0 : Light Index ( 광원 버퍼에서 자신의 인덱스)
// =========================
VTX_OUT VS_PointLight(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPosition, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    return output;
}

PS_OUT PS_PointLight(VTX_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    // Sphere 내부에 들어오는지 확인한다.
    // 해당 픽셀의 화면 전체기준 UV 위치를 알아내야 한다.
    // VS_OUT은 Position이 SV_Position으로 되었기 때문에 PS에서는 화면좌표계 좌표로 변환된다.
    float2 vScreenUV = (float2) 0.f;
    vScreenUV.x = _in.vPosition.x / fTargetWidth;
    vScreenUV.y = _in.vPosition.y / fTargetHeight;
        
    //g_tex_1에는 Point Light의 볼륨메쉬가 없는 장면에 대해 Position값이 기록되어 있다.
    float3 vViewPos = g_tex_1.Sample(g_sam_0, vScreenUV).xyz;
    
    if (vViewPos.z == 0.f)
    {
        clip(-1); // void
    }
    
    float4 vWorldPos = mul(float4(vViewPos, 1.f), g_matViewInv);
    float4 vLocalPos = mul(vWorldPos, g_matWorldInv);
    
    if (distance(float3(0.f, 0.f, 0.f), vLocalPos.xyz) <= 1.f)
    {
        float3 vViewNormal = g_tex_0.Sample(g_sam_0, vScreenUV).xyz;
        
        tLightColor color = (tLightColor) 0.f;
        CaculateLight(vViewPos.xyz, vViewNormal.xyz, g_int_0, color);
    
        output.vDiffuseLight = color.vLightDiff + color.vLightAmb;
        output.vSpecularLight = color.vLightSpec;
    }
    else
    {
        clip(-1);
    }
    
    return output;
}

// ==============================================================
// Merge Shader(Light(Light + Specular) , Diffuse ) -> SwapChain
// BlendState : Default
// DepthStencilState : NO Test Write
// g_tex_0 : Diffuse Target
// g_tex_1 : Light Target
// g_tex_2 : Specular Target
// g_tex_3 : Position target
// =======================================

VTX_OUT VS_Merge(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition.xyz = _in.vPosition * 2.f;
    output.vPosition.w = 1.f;
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_Merge(VTX_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;

    float3 vDiffuseColor = g_tex_0.Sample(g_sam_0, _in.vUV).xyz;
    float3 vLight = g_tex_1.Sample(g_sam_0, _in.vUV).xyz;
    //float3 vLight = 0.f;
    float3 vSpecular = g_tex_2.Sample(g_sam_0, _in.vUV).xyz;
    
    float vBrushAlpha = g_tex_3.Sample(g_sam_0, _in.vUV).a;
    
    //vColor.rgb = vDiffuseColor * vLight + vSpecular + (float3(0.2f, 0.2f, 1.f) * vBrushAlpha);
    vColor.rgb = (vDiffuseColor * vLight) + (vSpecular * vLight) + (float3(0.2f, 0.2f, 0.2f));
    
    return vColor;
}

// ==============================================================
// Decal Shader -> SwapChain
// BlendState : Default
// DepthStencilState : NO Test Write
// g_tex_0 : Diffuse Texture
// g_tex_1 : Light Target
// g_tex_2 : Specular Texture
// g_tex_3 : Position target
// =======================================
VTX_OUT VS_Decal(VTX_IN _in)
{
    VTX_OUT output = (VTX_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPosition, 1.f), g_matWVP);
    output.vUV = _in.vUV;
   
    return output;
}

float4 PS_Decal(VTX_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;

    float2 vScreenUV = (float2) 0.f;
    vScreenUV.x = _in.vPosition.x / fTargetWidth; 
    vScreenUV.y = _in.vPosition.y / fTargetHeight;
    
    float3 vViewPos = g_tex_3.Sample(g_sam_0, vScreenUV).xyz; 
    if (vViewPos.z == 0.f)
    {
        clip(-1); 
    }
    
    float4 vWorldPos = mul(float4(vViewPos, 1.f), g_matViewInv); 
    float4 vLocalPos = mul(vWorldPos, g_matWorldInv);
    
    
    if ((-0.5f <= vLocalPos.x && vLocalPos.x <= 0.5f) &&
        (-0.5f <= vLocalPos.y && vLocalPos.y <= 0.5f) &&
        (-0.5f <= vLocalPos.z && vLocalPos.z <= 0.5f))
    {
        float3 vLight = g_tex_1.Sample(g_sam_0, vScreenUV).xyz; 
        
        float2 decalTextureUV = vLocalPos.xz + 0.5f;  
        float4 vDiffuseColor = g_tex_0.Sample(g_sam_0, decalTextureUV); 
        float4 vSpecular = g_tex_2.Sample(g_sam_0, decalTextureUV); 
        
        vColor.xyz = (vDiffuseColor.xyz * vLight) + (vSpecular.xyz * vLight) + (float3(0.2f, 0.2f, 0.2f)); 
        vColor.a = vDiffuseColor.a;
    }
    else
    {
        clip(-1); 
    }

    
    return vColor;
}

// =================
// Shadow Map Shader
// =================

struct VS_ShadowIn
{
    float3 vPos : POSITION;
    float4 vWeights : WEIGHTS;
    float4 vIndices : BLENDINDICES;
};

struct VS_ShadowOut
{
    float4 vPos : SV_Position;
    float4 vProj : POSITION;
};

VS_ShadowOut VS_ShadowMap(VS_ShadowIn _in)
{
    VS_ShadowOut output = (VS_ShadowOut) 0.f;
    
    if (g_tcheck_7)
    {
        Skinning(_in.vPos, _in.vWeights, _in.vIndices, 0);
    }
    
    output.vPos = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vProj = output.vPos;

    return output;
}

float4 PS_ShadowMap(VS_ShadowOut _input) : SV_Target
{
    return float4(_input.vProj.z / _input.vProj.w, 0.f, 0.f, 0.f);
}

#endif
