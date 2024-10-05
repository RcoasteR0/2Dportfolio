#include "stdafx.h"
#include "Square.h"

Square::Square(Vector3 position, Vector3 size, float rotation, Color color)
	: position(position)
	, size(size)
	, rotation(rotation)
	, color(color)
{
	vertices.assign(4, VertexColor());
	
	vertices[0].position = Vector3(-0.5f, -0.5f, 0.0f);
	//vertices[0].color = Red;

	vertices[1].position = Vector3(-0.5f, 0.5f, 0.0f);
	//vertices[1].color = Red;

	vertices[2].position = Vector3(0.5f, -0.5f, 0.0f);
	//vertices[2].color = Red;

	vertices[3].position = Vector3(0.5f, 0.5f, 0.0f);
	//vertices[3].color = Red;

	indices = { 0, 1, 2, 2, 1, 3 };

	VB = new VertexBuffer();
	IB = new IndexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	VS->Create(L"./_Shaders/VertexColor.hlsl", "VS");
	PS->Create(L"./_Shaders/VertexColor.hlsl", "PS");

	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());

	WB = new WorldBuffer();
	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&R);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

	WB->SetWorld(world);
	TransformVertices();

	CB = new ColorBuffer();
	SetColor(color);
}

Square::~Square()
{
	SAFE_DELETE(CB);
	SAFE_DELETE(WB);
	SAFE_DELETE(IL);
	SAFE_DELETE(PS);
	SAFE_DELETE(VS);
	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

void Square::Move(Vector3 position)
{
	this->position += position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * R * T;

	WB->SetWorld(world);
	TransformVertices();
}

void Square::Rotation(float rotation)
{
	this->rotation = rotation;
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(this->rotation));

	world = S * R * T;
	WB->SetWorld(world);
}

void Square::Update()
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

	right = Vector3(R._11, R._12, R._13);
	up = Vector3(R._21, R._22, R._23);
}

void Square::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	WB->SetVSBuffer(0);
	CB->SetVSBuffer(2);
	VS->SetShader();

	PS->SetShader();

	DC->DrawIndexed(IB->GetCount(), 0, 0);
}

//색 설정
void Square::SetColor(Color color)
{
	this->color = color;
	CB->SetColor(this->color);
}

void Square::TransformVertices()
{
	//D3DXVec3TransformCoord		//정점 위치 반환
	//D3DXVec3TransformNormal		//정점 방향 반환
	
	//사각형의 좌상단과 우하단 위치 반환
	D3DXVec3TransformCoord(&r.LT, &vertices[1].position, &world);
	D3DXVec3TransformCoord(&r.RB, &vertices[2].position, &world);
}
