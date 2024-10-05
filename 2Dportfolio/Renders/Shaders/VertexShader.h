#pragma once

#include"IShader.h"

class VertexShader : public IShader		//IShader 상속
{
public:
	//생성자, 소멸자
	VertexShader();
	~VertexShader();

	//변수 반환
	ID3D11VertexShader* GetResource() { return shader; }
	ID3DBlob* GetBlob() { return blob; }

	//생성, 초기화, 설정 함수 오버라이드
	void Create(wstring path, string entryName) override;
	void Clear() override;
	void SetShader() override;

private:
	ID3D11VertexShader* shader = nullptr;
	ID3DBlob* blob = nullptr;
};