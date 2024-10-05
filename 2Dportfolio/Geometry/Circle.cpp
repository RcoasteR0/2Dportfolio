#include "stdafx.h"
#include "Circle.h"


Circle::Circle(Vector3 position, Vector3 size, int segments, Color color)
	: position(position)
	, size(size)
	, segments(segments)
	, color(color)
{
	vertices.assign(segments + 1, VertexColor());	//������ �� = segments + 1
	{
		for (int i = 0; i < segments + 1; i++)
		{
			float t = 2 * (float)D3DX_PI * i / segments;
			vertices[i].position = Vector3(cosf(t), -sinf(t), 0);
		}
	}

	VB = new VertexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	//���� ����
	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	//���̴� ����
	VS->Create(L"./_Shaders/VertexColor.hlsl", "VS");
	PS->Create(L"./_Shaders/VertexColor.hlsl", "PS");

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());
	
	//���庯ȯ
	WB = new WorldBuffer();
	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&T);

	//ũ��, �̵�
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * T;

	//������ۿ� ������� ����
	WB->SetWorld(world);

	CB = new ColorBuffer();
	SetColor(color);
}

//�Ҹ���
Circle::~Circle()
{
	SAFE_DELETE(CB);
	SAFE_DELETE(WB);
	SAFE_DELETE(IL);
	SAFE_DELETE(PS);
	SAFE_DELETE(VS);
	SAFE_DELETE(VB);
}

void Circle::Move(Vector3 position)
{
	this->position += position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * T;

	WB->SetWorld(world);
}

void Circle::SetColor(Color color)
{
	this->color = color;
	CB->SetColor(this->color);
}

void Circle::Update()
{
	
}

void Circle::Render()
{
	VB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	WB->SetVSBuffer(0);
	CB->SetVSBuffer(2);
	VS->SetShader();

	PS->SetShader();

	DC->Draw(segments + 1, 0);
}