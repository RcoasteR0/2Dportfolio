#pragma once

struct RectEdges
{
	Vector3 LT;
	Vector3 RB;
};

class Square
{
public:
	Square(Vector3 position, Vector3 size, float rotation, Color color);
	~Square();

	void Move(Vector3 position);
	void Rotation(float rotation);

	void Update();
	void Render();

	Matrix GetSMatrix() { return S; }
	Matrix GetRMatrix() { return R; }
	Matrix GetTMatrix() { return T; }

	Vector3 GetPosition() { return position; }
	void SetPosition(Vector3 position) { this->position = position; }

	Vector3 GetScale() { return size; }
	void SetScale(Vector3 size) { this->size = size; }

	void SetColor(Color color);

	RectEdges GetTransformedCoord() { return r; }

	void SetIntersect(bool bIntersect) { this->bIntersect = bIntersect; }

	Vector3 Right() { return right; }
	Vector3 Up() { return up; }

private:
	void TransformVertices();

	vector<VertexColor> vertices;
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
	Color color;

	RectEdges r;
	ColorBuffer* CB = nullptr;
	bool bIntersect = false;

	Vector3 right = Vector3(1.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
};