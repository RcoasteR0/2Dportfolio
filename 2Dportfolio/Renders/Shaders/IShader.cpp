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
		path.c_str(),						//hlsl ����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//include�� ������ hlsl������ ���
		entryName.c_str(),					//������ �Լ� �̸�
		profile.c_str(),					//���̴� ��
		D3DCOMPILE_ENABLE_STRICTNESS,		//���� �������� ������� �ʰڴ�
		0,
		blob,								//������ blob �ּ�
		&error								//�����޽���
	);
	//������ �� ������ �ִ��� Ȯ��
	CheckShaderError(hr, error);
	SAFE_RELEASE(error);
}

void IShader::CheckShaderError(HRESULT hr, ID3DBlob * error)
{
	//���̴� ������ ���н� ���� ���
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
