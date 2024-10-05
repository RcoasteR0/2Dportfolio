#include "stdafx.h"
#include "PixelShader.h"

PixelShader::PixelShader()
{
}

PixelShader::~PixelShader()
{
	Clear();
}

void PixelShader::Create(wstring path, string entryName)
{
	this->path = path;
	this->entryName = entryName;

	//�ȼ� ���̴� ������
	CompileShader(path, entryName, "ps_5_0", &blob);

	//�ȼ� ���̴� ����
	HRESULT hr = DEVICE->CreatePixelShader
	(
		blob->GetBufferPointer(),	//���̴� ������ �ּ�
		blob->GetBufferSize(),		//���̴� ũ��
		nullptr,
		&shader						//������ �ȼ� ���̴� �ּ�
	);
	ASSERT(hr);
}

void PixelShader::Clear()
{
	//���� �ʱ�ȭ
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void PixelShader::SetShader()
{
	DC->PSSetShader(shader, nullptr, 0);
}
