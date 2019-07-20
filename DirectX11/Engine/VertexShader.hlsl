cbuffer MATRIX : register(b0)
{
    matrix g_mWorld;
    matrix g_mView;
    matrix g_mProjection;
}

struct VERTEX_INPUT
{
    float3 vPos : POSITION;
	float4 vColor : COLOR;
};

struct VERTEX_OUTPUT
{
    float4 vPos : SV_POSITION;
	float4 vColor : COLOR;
};


VERTEX_OUTPUT main( VERTEX_INPUT input )
{
	VERTEX_OUTPUT output = (VERTEX_OUTPUT) 0.f;
    
    float4 vWorldPos = mul(float4(input.vPos, 1.f), g_mWorld);
    float4 vViewPos = mul(vWorldPos, g_mView);
    float4 vProjectionPos = mul(vViewPos, g_mProjection);
    output.vPos = vProjectionPos;
	output.vColor = input.vColor;

	return output;
}