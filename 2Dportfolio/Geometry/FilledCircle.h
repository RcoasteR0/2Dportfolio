#pragma once

class FilledCircle
{
public:
	FilledCircle(Vector3 position, Vector3 size, int segmests, Color color);
	~FilledCircle();

	void Move(Vector3 position);
	void SetColor(Color color);

	void Update();
	void Render();

private:
	vector<VertexColor> vertices;
	vector<UINT> indices;

	InputLayout* IL = nullptr;

	VertexBuffer* VB = nullptr;
	IndexBuffer* IB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	WorldBuffer* WB = nullptr;
	Matrix world, S, T;
	Vector3 position, size;

	int segments;

	ColorBuffer* CB = nullptr;
	Color color;
};