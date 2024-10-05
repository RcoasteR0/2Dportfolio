#include "CBuffers.hlsl"

struct VertexInput
{
	float4 position : POSITION0;
    float4 color : COLOR0;
	float2 uv : TEXCOORD0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
    float4 color : COLOR0;
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
    output.color = input.color;
    
    return output;
}

//Texture2D srcTex0 : register(t0);
Texture2D tileTex : register(t0);
SamplerState samp : register(s0);

//ÇÈ¼¿ ¼ÎÀÌ´õ
float4 PS(PixelInput input) : SV_Target
{
    float4 color = tileTex.Sample(samp, input.uv);
    
    if (input.uv.x > 0 || input.uv.y > 0)
        return color;
    else
        return input.color;
}