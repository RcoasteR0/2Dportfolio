#include "stdafx.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer()
{
}

IndexBuffer::~IndexBuffer()
{
	//소멸자에서 변수 초기화
	SAFE_RELEASE(buffer);
}

void IndexBuffer::Create
(
	const vector<UINT>& indices,	//정점 인덱스 정보
	const D3D11_USAGE & usage		//자원 용도
)
{
	stride = sizeof(UINT);						//데이터의 크기
	count = static_cast<UINT>(indices.size());	//데이터의 개수

	D3D11_BUFFER_DESC desc;	//버퍼의 desc 생성
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));	//desc 초기화
	desc.Usage = usage;								//원하는 자원 용도 지정
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;		//자원 플래그(인덱스 버퍼)
	desc.ByteWidth = stride * count;				//버퍼 넓이(크기 * 개수)

	switch (usage)	//자원 용도에따라 CPU 접근권한 지정
	{
	case D3D11_USAGE_DEFAULT:		//기본 용도
		break;
	case D3D11_USAGE_IMMUTABLE:		//불변 용도
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:		//동적 용도(cpu 쓰기 가능)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:		//예비 용도(cpu 쓰기, 읽기 가능)
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}

	D3D11_SUBRESOURCE_DATA subData;	//인덱스 정보를 전달받을 서브데이터
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));	//초기화
	subData.pSysMem = indices.data();	//서브 데이터에 정점 정보 전달

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	//인덱스 버퍼 생성
	ASSERT(hr);
}

void IndexBuffer::SetIA()
{
	DC->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);	//인덱스 버퍼를 IA단계에 사용
}
