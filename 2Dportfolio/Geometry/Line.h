#pragma once

class Line
{
public:
	Line(Vector3 position, float length, float rotation, Color color);
	~Line();

	void Move(Vector3 position);
	void Rotation(float rotation);

	void Update();
	void Render();

	void SetColor(Color color);

private:
	vector<VertexColor> vertices;
	InputLayout* IL = nullptr;

	VertexBuffer* VB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	WorldBuffer* WB = nullptr;
	Matrix world, S, R, T;
	Vector3 position;
	float length;
	float rotation;
	Color color;

	ColorBuffer* CB = nullptr;
};