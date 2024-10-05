#pragma once

class Circle
{
public:
	Circle(Vector3 position, Vector3 size, int segmests, Color color);
	~Circle();

	void Move(Vector3 position);
	void SetColor(Color color);

	void Update();
	void Render();

private:
	vector<VertexColor> vertices;

	InputLayout* IL = nullptr;

	VertexBuffer* VB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	WorldBuffer* WB = nullptr;
	Matrix world, S, T;
	Vector3 position, size;

	int segments;

	ColorBuffer* CB = nullptr;
	Color color;
};