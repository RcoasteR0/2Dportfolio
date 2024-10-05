#include "stdafx.h"
#include "Line.h"

Line::Line(D3DXVECTOR3 position, float length, float rotation, Color color)
	: position(position)
	, length(length)
	, rotation(rotation)
	, color(color)
{
	vertices.assign(2, VertexColor());
	
	vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//vertices[0].color = Red;

	vertices[1].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//vertices[1].color = Red;

	VB = new VertexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	VB->Create(vertices, D3D11_USAGE_DYNAMIC);

	VS->Create(L"./_Shaders/VertexColor.hlsl", "VS");
	PS->Create(L"./_Shaders/VertexColor.hlsl", "PS");

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());

	WB = new WorldBuffer();
	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, length, 0, 0);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	WB->SetWorld(world);

	CB = new ColorBuffer();
	SetColor(color);
}

Line::~Line()
{
	SAFE_DELETE(CB);
	SAFE_DELETE(WB);
	SAFE_DELETE(IL);
	SAFE_DELETE(PS);
	SAFE_DELETE(VS);
	SAFE_DELETE(VB);
}

void Line::Move(D3DXVECTOR3 position)
{
	this->position += position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;

	WB->SetWorld(world);
}

void Line::Rotation(float rotation)
{
	this->rotation = rotation;
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(this->rotation));

	world = S * R * T;

	WB->SetWorld(world);
}

void Line::Update()
{
	/*D3D11_MAPPED_SUBRESOURCE subResource;

	DC->Map(
		VB->GetResource(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&subResource
	);

	for (VertexColor& v : vertices)
		v.color = D3DXCOLOR(1, 0, 0, 1);
	memcpy(subResource.pData, vertices.data(), sizeof(VertexColor) * vertices.size());
	DC->Unmap(VB->GetResource(), 0);*/
}

void Line::Render()
{
	VB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	WB->SetVSBuffer(0);
	CB->SetVSBuffer(2);
	VS->SetShader();

	PS->SetShader();

	DC->Draw(VB->GetCount(), 0);
}

void Line::SetColor(Color color)
{
	this->color = color;
	CB->SetColor(color);
}
