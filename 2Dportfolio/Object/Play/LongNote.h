#pragma once

class DurationBuffer : public ShaderBuffer
{
public:
	DurationBuffer()
		:ShaderBuffer(&data, sizeof(Struct))
	{}

	void SetDuration(float duration)
	{
		data.duration = duration;
	}

	struct Struct
	{
		float duration;
		Vector3 dummy;
	};

private:
	Struct data;
};

class LongNote
{
public:
	LongNote(int line, float timing, float length);
	~LongNote();

	void SetSRV(ID3D11ShaderResourceView* SRV) { this->srv = SRV; }
	void SetSRV(wstring path);

	void SetShader(wstring shaderPath);

	void Move(Vector3 position);
	void SetSize(Vector3 size);

	void HitNote(bool hit) { this->hit = hit; }
	void SetHold(bool hold) { this->hold = hold; }
	bool GetHold() { return hold; }

	void Update();
	void Render();

	void GUI(int ordinal);

private:
	vector<VertexTexture> vertices;
	vector<UINT> indices;
	InputLayout* IL = nullptr;

	VertexBuffer* VB = nullptr;
	IndexBuffer* IB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	WorldBuffer* WB = nullptr;

	Matrix world, S, T;
	Vector3 position, size;

	DurationBuffer* DB;

	ID3D11BlendState* BS;
	ID3D11SamplerState* SS;

	ID3D11ShaderResourceView* srv = nullptr;
	ID3D11ShaderResourceView* nullView = nullptr;

	wstring texturePath = L"";
	wstring shaderPath = L"";

	bool hold;
	bool hit;
	float timing;
	float length;
	float progress;
};