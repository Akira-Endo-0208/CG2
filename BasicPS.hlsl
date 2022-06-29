cbuffer ConstBufferDataMaterial : register(b0)
{
	float4 color;
}

cbuffer ConstBufferDataTransform : register(b1)
{
	matrix mat;
}

float4 main() : SV_TARGET
{
	return color;
}