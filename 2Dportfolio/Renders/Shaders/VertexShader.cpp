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

	//���ؽ� ���̴� ������
	CompileShader(path, entryName, "vs_5_0", &blob);

	//���ؽ� ���̴� ����
	HRESULT hr = DEVICE->CreateVertexShader
	(
		blob->GetBufferPointer(),	//���̴� ������ �ּ�
		blob->GetBufferSize(),		//���̴� ũ��
		nullptr,
		&shader						//������ ���ؽ� ���̴� �ּ�
	);
	ASSERT(hr);
}

void VertexShader::Clear()
{
	//���� �ʱ�ȭ
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void VertexShader::SetShader()
{
	DC->VSSetShader(shader, nullptr, 0);
}
