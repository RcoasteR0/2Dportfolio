#pragma once

class InputLayout
{
public:
	//������, �Ҹ���
	InputLayout();
	~InputLayout();

	//���� ��ȯ
	ID3D11InputLayout* GetResource() { return inputLayout; }

	//��ǲ ���̾ƿ� ����
	void Create(D3D11_INPUT_ELEMENT_DESC* desc, const UINT& count, ID3DBlob* blob);

	//IA�� ��ǲ ���̾ƿ� ����
	void SetIA();
private:
	ID3D11InputLayout* inputLayout;
};