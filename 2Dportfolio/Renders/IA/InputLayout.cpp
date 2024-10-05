#include "stdafx.h"
#include "InputLayout.h"

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
{
	//���� �ʱ�ȭ
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC * desc, const UINT & count, ID3DBlob * blob)
{
	//�Ű������� 0�̸� ���� �߻�
	if (!desc || !count || !blob)
		assert(false);

	//��ǲ ���̾ƿ� ����
	HRESULT hr = DEVICE->CreateInputLayout
	(
		desc,						//GPU�� ���� ���� ���� �迭
		count,						//���� �������� ��
		blob->GetBufferPointer(),	//���� ���̴��� �ּ�
		blob->GetBufferSize(),		//���� ���̴��� ũ��
		&inputLayout				//��ǲ ���̾ƿ��� �ּ�
	);
	ASSERT(hr);
}

void InputLayout::SetIA()
{
	//��ǲ ���̾ƿ��� IA �ܰ迡 ���
	DC->IASetInputLayout(inputLayout);
}
