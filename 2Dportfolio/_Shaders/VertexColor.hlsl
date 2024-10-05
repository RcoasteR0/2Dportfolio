struct VertexInput
{
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct PixelInput
{
	float4 position : SV_POSITION0;
	float4 color : COLOR0;
};

cbuffer World : register(b0)
{
    matrix _world;
};

cbuffer ViewProjection : register(b1)
{
    matrix _view;
    matrix _proj;
}

cbuffer Color : register(b2)
{
    float4 _color;
}

//¡§¡° ºŒ¿Ã¥ı
PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    
    output.color = _color;
    
    return output;
}

//«»ºø ºŒ¿Ã¥ı
float4 PS(PixelInput input) : SV_Target
{
    return input.color;
}