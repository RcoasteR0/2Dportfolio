#pragma once

class IndexBuffer
{
public:
	//생성자, 소멸자
	IndexBuffer();
	~IndexBuffer();

	//인덱스 버퍼 설정 함수
	void Create(const vector<UINT>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

	//변수 반환
	ID3D11Buffer * GetResource() { return buffer; }
	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

	//IA에 인덱스 버퍼 전달
	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;
	UINT stride = 0;
	UINT offset = 0;
	UINT count = 0;
};
