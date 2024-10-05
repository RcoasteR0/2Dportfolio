#include "stdafx.h"
#include "VertexShader.h"

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
	Clear();
}

void VertexShader::Create(wstring path, string entryName)
{
	this->path = path;
	this->entryName = entryName;

	//버텍스 셰이더 컴파일
	CompileShader(path, entryName, "vs_5_0", &blob);

	//버텍스 셰이더 생성
	HRESULT hr = DEVICE->CreateVertexShader
	(
		blob->GetBufferPointer(),	//셰이더 데이터 주소
		blob->GetBufferSize(),		//셰이더 크기
		nullptr,
		&shader						//저장할 버텍스 셰이더 주소
	);
	ASSERT(hr);
}

void VertexShader::Clear()
{
	//변수 초기화
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void VertexShader::SetShader()
{
	DC->VSSetShader(shader, nullptr, 0);
}
