#pragma once

class TextureRect
{
public:
	TextureRect(Vector3 position, Vector3 size, float rotation);
	~TextureRect();

	void SetSRV(ID3D11ShaderResourceView* SRV) { this->srv = SRV; }
	void SetSRV(wstring path);

	void SetShader(wstring shaderPath);

	void Move(Vector3 position);
	void SetPos(Vector3 position);
	void SetSize(Vector3 size);
	void InvisibleTexture(bool invisible);

	RectEdges GetTransformedCoord() { return r; }

	void Update();
	void Render();

	void GUI(int ordinal);

private:
	void TransformVertices();

	vector<VertexTexture> vertices;
	vector<UINT> indices;
	InputLayout* IL = nullptr;

	VertexBuffer* VB = nullptr;
	IndexBuffer* IB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	WorldBuffer* WB = nullptr;

	Matrix world, S, R, T;
	Vector3 position, size;
	float rotation;

	ID3D11BlendState* BS;
	ID3D11SamplerState* SS;

	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11ShaderResourceView* nullView = nullptr;

	RectEdges r;
	InvisibleBuffer* SB = nullptr;

	wstring texturePath = L"";
	wstring shaderPath = L"";

	char text[255] = "";
};