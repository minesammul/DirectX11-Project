struct VERTEX_INPUT
{
    float3 vPos : POSITION;
	float4 vColor : COLOR;
};

struct VERTEX_OUTPUT
{
	float4 vPos : SV_Position;
	float4 vColor : COLOR;
};


VERTEX_OUTPUT main( VERTEX_INPUT input )
{
	VERTEX_OUTPUT output = (VERTEX_OUTPUT) 0.f;

	output.vPos = float4(input.vPos, 1.f);
	output.vColor = input.vColor;

	return output;
}