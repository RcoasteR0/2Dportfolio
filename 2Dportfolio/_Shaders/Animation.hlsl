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

//¡§¡° ºŒ¿Ã¥ı
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

//«»ºø ºŒ¿Ã¥ı
float4 PS(PixelInput input) : SV_Target
{
    float4 color = srcTex0.Sample(samp, input.uv);
    
    if (color.r < 0.30f && color.g < 0.30f && color.b < 0.30f)
        discard;
    
    return color;
}