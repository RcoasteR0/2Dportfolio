#include "stdafx.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
	//�Ҹ��ڿ��� ���� �ʱ�ȭ
	SAFE_RELEASE(buffer);
}

void IndexBuffer::Create
(
	const vector<UINT>& indices,	//���� �ε��� ����
	const D3D11_USAGE & usage		//�ڿ� �뵵
)
{
	stride = sizeof(UINT);						//�������� ũ��
	count = static_cast<UINT>(indices.size());	//�������� ����

	D3D11_BUFFER_DESC desc;	//������ desc ����
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));	//desc �ʱ�ȭ
	desc.Usage = usage;								//���ϴ� �ڿ� �뵵 ����
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//�ڿ� �÷���(�ε��� ����)
	desc.ByteWidth = stride * count;				//���� ����(ũ�� * ����)

	switch (usage)	//�ڿ� �뵵������ CPU ���ٱ��� ����
	{
	case D3D11_USAGE_DEFAULT:		//�⺻ �뵵
		break;
	case D3D11_USAGE_IMMUTABLE:		//�Һ� �뵵
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:		//���� �뵵(cpu ���� ����)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:		//���� �뵵(cpu ����, �б� ����)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}

	D3D11_SUBRESOURCE_DATA subData;	//�ε��� ������ ���޹��� ���굥����
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));	//�ʱ�ȭ
	subData.pSysMem = indices.data();	//���� �����Ϳ� ���� ���� ����

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	//�ε��� ���� ����
	ASSERT(hr);
}

void IndexBuffer::SetIA()
{
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);	//�ε��� ���۸� IA�ܰ迡 ���
}
