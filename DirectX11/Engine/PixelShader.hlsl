struct PIXEL_INPUT
{
    float4 vPos : SV_Position;
    float4 vColor : COLOR;
};

float4 main(PIXEL_INPUT input) : SV_Target
{
    input.vColor = float4(1.0f, 1.0f, 0.0f, 1.0f);
	return input.vColor;
}