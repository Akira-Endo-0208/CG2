#include "Basic.hlsli"

VSOutput main(float4 pos : POSITION)
{
	VSOutput output;
	output.svpos = mul(mat, pos);
	return output;
}