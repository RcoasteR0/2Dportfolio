#include "stdafx.h"
#include "IShader.h"

IShader::IShader()
{
}

void IShader::CompileShader(wstring path, string entryName, string profile, ID3DBlob ** blob)
{
	this->path = path;
	this->entryName = entryName;
	this->profile = profile;

	ID3DBlob* error = nullptr;
	HRESULT hr = D3DCompileFromFile
	(
		path.c_str(),						//hlsl 파일
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//include한 파일을 hlsl에서도 사용
		entryName.c_str(),					//진입점 함수 이름
		profile.c_str(),					//셰이더 모델
		D3DCOMPILE_ENABLE_STRICTNESS,		//옛날 구문들을 사용하지 않겠다
		0,
		blob,								//저장할 blob 주소
		&error								//오류메시지
	);
	//컴파일 중 오류가 있는지 확인
	CheckShaderError(hr, error);
	SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob * error)
{
	//셰이더 컴파일 실패시 오류 출력
	if (FAILED(hr))
	{
		if (error)
		{
			string str = (const char*)error->GetBufferPointer();
			MessageBoxA(NULL, str.c_str(), "Shader Error", MB_OK);
		}
		ASSERT(false);
	}
}
