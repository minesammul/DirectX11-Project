struct PIXEL_INPUT
{
	float3 vPos : POSITION;
	float4 vColor : COLOR;
};

float4 main(PIXEL_INPUT input) : SV_TARGET
{
    input.vColor = float4(1.0f, 1.0f, 0.0f, 1.0f);
	return input.vColor;
}