#pragma once

struct VertexColor
{
	//생성자
	VertexColor() : position(0, 0, 0), color(0, 0, 0, 0) {}
	VertexColor(const Vector3& position, const Color& color)
		:position(position)		//정점의 위치
		, color(color)			//정점의 색
	{}

	Vector3 position;
	Color color;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 2;
};

struct VertexTexture
{
	VertexTexture() : position(0,0,0), uv(0,0) {}

	Vector3 position;
	Vector2 uv;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 2;
};

struct VertexTextureColor
{
	VertexTextureColor() : position(0, 0, 0), color(0, 0, 0, 1), uv(0, 0) {}
	VertexTextureColor(const Vector3& position, const Color& color, const Vector2& uv)
		: position(position)
		, color(color)
		, uv(uv)
	{}

	Vector3 position;
	Color color;
	Vector2 uv;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 3;
};

struct VertexTile
{
	VertexTile() : position(0, 0, 0), uv(0, 0), tileUv(0, 0), isTiled(false) {}
	VertexTile(const Vector3& position, const Vector2& uv, const Vector2& tileUv, const bool& isTied)
		: position(position)
		, uv(uv)
		, tileUv(tileUv)
		, isTiled(isTiled)
	{}

	Vector3 position;
	Vector2 uv;
	Vector2 tileUv;
	bool isTiled;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static constexpr UINT count = 4;
};