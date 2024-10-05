#include "stdafx.h"
#include "LongNote.h"

LongNote::LongNote(int line, float timing, float length)
	:timing(timing)
	, length(length)
{
	if (line == 1 || line == 3 || line == 4 || line == 6)
	{
		SetSRV(L"./_Textures/white_long.png");
		size = { WhlteLaneSize, length * Setting::Get()->GetNoteSpeed() * Common_Speed, 1 };
	}
	else if (line == 2 || line == 5)
	{
		SetSRV(L"./_Textures/black_long.png");
		size = { BlackLaneSize, length * Setting::Get()->GetNoteSpeed() * Common_Speed, 1 };
	}

	float linePos;
	switch (line)
	{
	case(1):
		linePos = Lane1Pos;
		break;
	case(2):
		linePos = Lane2Pos;
		break;
	case(3):
		linePos = Lane3Pos;
		break;
	case(4):
		linePos = Lane4Pos;
		break;
	case(5):
		linePos = Lane5Pos;
		break;
	case(6):
		linePos = Lane6Pos;
		break;
	}

	position = { linePos, timing * Setting::Get()->GetNoteSpeed() * Common_Speed + Common_Pos + Setting::Get()->GetJudgementLinePos(), 0 };

	//정점과 uv좌표 지정
	vertices.assign(4, VertexTexture());
	vertices[0].position = Vector3(-0.5f, 0.0f, 0.0f);
	vertices[0].uv = Vector2(0.0f, 1.0f);

	vertices[1].position = Vector3(-0.5f, 1.0f, 0.0f);
	vertices[1].uv = Vector2(0.0f, 0.0f);

	vertices[2].position = Vector3(0.5f, 0.0f, 0.0f);
	vertices[2].uv = Vector2(1.0f, 1.0f);

	vertices[3].position = Vector3(0.5f, 1.0f, 0.0f);
	vertices[3].uv = Vector2(1.0f, 0.0f);

	//인덱스
	indices = { 0,1,2,2,1,3 };

	//그래픽 파이프라인
	VB = new VertexBuffer();
	IB = new IndexBuffer();

	VS = new VertexShader();
	PS = new PixelShader();

	IL = new InputLayout();

	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	shaderPath = L"./_Shaders/LongNote.hlsl";
	VS->Create(shaderPath, "VS");
	PS->Create(shaderPath, "PS");

	IL->Create(VertexTexture::descs, VertexTexture::count, VS->GetBlob());

	WB = new WorldBuffer();
	D3DXMatrixIdentity(&world);

	D3DXMatrixIdentity(&S);
	D3DXMatrixIdentity(&T);

	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * T;

	WB->SetWorld(world);

	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));

		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		HRESULT hr = DEVICE->CreateBlendState(&desc, &BS);
		ASSERT(hr);
	}

	{
		D3D11_SAMPLER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_SAMPLER_DESC));

		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.MaxAnisotropy = 16;
		desc.MinLOD = numeric_limits<float>::min();
		desc.MaxLOD = numeric_limits<float>::max();
		desc.MipLODBias = 0.0f;

		HRESULT hr = DEVICE->CreateSamplerState(&desc, &SS);
		ASSERT(hr);
	}

	DB = new DurationBuffer;
}

LongNote::~LongNote()
{
	SAFE_RELEASE(nullView);
	SAFE_RELEASE(srv);

	SAFE_DELETE(DB);
	SAFE_RELEASE(SS);
	SAFE_RELEASE(BS);
	SAFE_DELETE(WB);
	SAFE_DELETE(IL);
	SAFE_DELETE(PS);
	SAFE_DELETE(VS);
	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

//셰이더 자원 뷰 생성
void LongNote::SetSRV(wstring path)
{
	texturePath = path;
	ViewFactory::GenerateSRV(path, &srv);
}

//셰이더 지정
void LongNote::SetShader(wstring shaderPath)
{
	this->shaderPath = shaderPath;
	if (VS)
	{
		VS->Clear();
		VS->Create(shaderPath, "VS");
	}

	if (PS)
	{
		PS->Clear();
		PS->Create(shaderPath, "PS");
	}
}

void LongNote::Move(Vector3 position)
{
	this->position += position;
	D3DXMatrixTranslation(&T, this->position.x, this->position.y, this->position.z);

	world = S * T;
	WB->SetWorld(world);
}

void LongNote::SetSize(Vector3 size)
{
	this->size = size;
	D3DXMatrixScaling(&S, this->size.x, this->size.y, this->size.z);

	world = S * T;
	WB->SetWorld(world);
}

void LongNote::Update()
{
	progress = Time::Get()->Running() - timing;
	if (hold)
		DB->SetDuration(progress / length);
	if (hit)
		SetSize({ 0,0,0 });

	Move({ 0, -Common_Speed * Time::Get()->Delta() * Setting::Get()->GetNoteSpeed() , 0 });
}

//랜더링
void LongNote::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	WB->SetVSBuffer(0);

	VS->SetShader();

	PS->SetShader();
	if (srv)
		DC->PSSetShaderResources(0, 1, &srv);	//이미지 SRV에 전달

	DC->PSSetSamplers(0, 1, &SS);
	DB->SetPSBuffer(3);

	DC->OMSetBlendState(BS, 0, 1);

	DC->DrawIndexed(IB->GetCount(), 0, 0);

	//랜더링 후 SRV 지우기
	if (srv)
		DC->PSSetShaderResources(0, 1, &nullView);	//SRV에 nullptr 전달

}

void LongNote::GUI(int ordinal)
{

}