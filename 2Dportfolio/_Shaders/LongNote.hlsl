#include "CBuffers.hlsl"

struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

//Á¤Á¡ ¼ÎÀÌ´õ
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    
    output.uv = input.uv;
    
    return output;
}

Texture2D srcTex0 : register(t0);

SamplerState samp : register(s0);

//ÇÈ¼¿ ¼ÎÀÌ´õ
float4 PS(PixelInput input) : SV_Target
{
    float4 color = srcTex0.Sample(samp, input.uv);

	if (input.uv.y > 1 - _duration)
        discard;
    
    return color;
}