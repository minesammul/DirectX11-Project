struct PIXEL_INPUT
{
	float3 vPos : POSITION;
	float4 vColor : COLOR;
};

float4 main(PIXEL_INPUT input) : SV_TARGET
{
	return input.vColor;
}