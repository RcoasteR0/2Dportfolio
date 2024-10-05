/////////////////////////////VertexShader/////////////////////////////////////
cbuffer World : register(b0)
{
    matrix _world;
};

cbuffer ViewProjection : register(b1)
{
    matrix _view;
    matrix _proj;
}

/////////////////////////////PixelShader/////////////////////////////////////
cbuffer SelectBuffer : register(b0)
{
    //int _selection;
    //float2 _textureSize;
    //bool _bOutline;
    bool _bInvisible;
}

cbuffer BlurBuffer : register(b1)
{
    uint _count;
}

cbuffer LocalBuffer : register(b2)
{
    float4 _localRect;
}

cbuffer DurationBuffer : register(b3)
{
	float1 _duration;
}