#pragma once

class VertexBuffer
{
public:
	//������, �Ҹ���
	VertexBuffer();
	~VertexBuffer();
	
	//�������� ���� ���ø� �Լ�
	template <typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	//���� ��ȯ
	ID3D11Buffer * GetResource() { return buffer; }
	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

	//IA�� �������� ����
	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;
	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};

template<typename T>
inline void VertexBuffer::Create
(
	const vector<T> & vertices	//T �ڷ����� ���� ����
	, const D3D11_USAGE & usage	//�ڿ� �뵵
)
{
	stride = sizeof(T);					//�������� ũ��
	count = (UINT)(vertices.size());	//�������� ����

	D3D11_BUFFER_DESC desc;	//������ desc ����
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));	//desc �ּ� ���� ������ �ʱ�ȭ
	desc.Usage = usage;								//���ϴ� �ڿ� �뵵 ����
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//�ڿ� �÷���(���� ����)
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

	D3D11_SUBRESOURCE_DATA subData;	//���� ������ ���޹��� ���굥����
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));	//�ʱ�ȭ
	subData.pSysMem = vertices.data();	//���� �����Ϳ� ���� ���� ����

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	//���� ���� ����
	ASSERT(hr);
}