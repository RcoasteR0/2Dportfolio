#pragma once

#include"IShader.h"

class VertexShader : public IShader		//IShader ���
{
public:
	//������, �Ҹ���
	VertexShader();
	~VertexShader();

	//���� ��ȯ
	ID3D11VertexShader* GetResource() { return shader; }
	ID3DBlob* GetBlob() { return blob; }

	//����, �ʱ�ȭ, ���� �Լ� �������̵�
	void Create(wstring path, string entryName) override;
	void Clear() override;
	void SetShader() override;

private:
	ID3D11VertexShader* shader = nullptr;
	ID3DBlob* blob = nullptr;
};