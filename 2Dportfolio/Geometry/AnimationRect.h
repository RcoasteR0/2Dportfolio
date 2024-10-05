#pragma once

class Animator;
class AnimationClip;

class AnimationRect
{
public:
	AnimationRect(Vector3 position, Vector3 size, float rotation);
	~AnimationRect();

	void Update();
	void Render();

	void Move(Vector3 position);
	void SetPos(Vector3 position);
	void SetSize(Vector3 size);

	Vector3 GetPosition() { return position; }

protected:
	Texture2D* texture = nullptr;
	Animator* animator = nullptr;
	vector<AnimationClip*> animClips;

private:
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

	ID3D11ShaderResourceView* nullView = nullptr;

	//AnimationClip* runR = nullptr;
	//AnimationClip* runL = nullptr;

	ID3D11BlendState* BS;
	ID3D11SamplerState* SS;
};