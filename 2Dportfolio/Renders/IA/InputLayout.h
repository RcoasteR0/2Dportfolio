#pragma once

class InputLayout
{
public:
	//생성자, 소멸자
	InputLayout();
	~InputLayout();

	//변수 반환
	ID3D11InputLayout* GetResource() { return inputLayout; }

	//인풋 레이아웃 생성
	void Create(D3D11_INPUT_ELEMENT_DESC* desc, const UINT& count, ID3DBlob* blob);

	//IA에 인풋 레이아웃 전달
	void SetIA();
private:
	ID3D11InputLayout* inputLayout;
};