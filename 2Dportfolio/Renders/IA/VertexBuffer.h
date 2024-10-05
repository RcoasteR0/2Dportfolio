#pragma once

class VertexBuffer
{
public:
	//생성자, 소멸자
	VertexBuffer();
	~VertexBuffer();
	
	//정점버퍼 설정 템플릿 함수
	template <typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	//변수 반환
	ID3D11Buffer * GetResource() { return buffer; }
	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

	//IA에 정점버퍼 전달
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
	const vector<T> & vertices	//T 자료형의 정점 정보
	, const D3D11_USAGE & usage	//자원 용도
)
{
	stride = sizeof(T);					//데이터의 크기
	count = (UINT)(vertices.size());	//데이터의 개수

	D3D11_BUFFER_DESC desc;	//버퍼의 desc 생성
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));	//desc 주소 안의 데이터 초기화
	desc.Usage = usage;								//원하는 자원 용도 지정
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//자원 플래그(정점 버퍼)
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

	D3D11_SUBRESOURCE_DATA subData;	//정점 정보를 전달받을 서브데이터
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));	//초기화
	subData.pSysMem = vertices.data();	//서브 데이터에 정점 정보 전달

	HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &buffer);	//정점 버퍼 생성
	ASSERT(hr);
}