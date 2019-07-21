struct PIXEL_INPUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

float4 main(PIXEL_INPUT input) : SV_Target
{
	return input.vColor;
}