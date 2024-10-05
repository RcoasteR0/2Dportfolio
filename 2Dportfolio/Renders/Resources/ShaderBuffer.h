#pragma once

#include "stdafx.h"

class ShaderBuffer
{
public:
	//VS에 상수버퍼 전달
	void SetVSBuffer(UINT slot)
	{
		MapData(data, dataSize);

		DC->VSSetConstantBuffers(slot, 1, &buffer);
	}

	//PS에 상수버퍼 전달
	void SetPSBuffer(UINT slot)
	{
		MapData(data, dataSize);

		DC->PSSetConstantBuffers(slot, 1, &buffer);
	}

protected:
	ShaderBuffer(void* data, UINT dataSize)
		: data(data), dataSize(dataSize)
	{
		//상수버퍼 정의
		desc.Usage = D3D11_USAGE_DYNAMIC;				//동적 용도
		desc.ByteWidth = dataSize;						//데이터 크기
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	//용도 플래그
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	//CPU 쓰기 플래그
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		//상수버퍼 생성
		HRESULT hr = DEVICE->CreateBuffer(&desc, NULL, &buffer);
		assert(SUCCEEDED(hr));
	}

	virtual ~ShaderBuffer()
	{
		SAFE_RELEASE(buffer);
	}

private:
	//상수버퍼 자원 갱신
	void MapData(void* data, UINT dataSize)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;

		HRESULT hr = DC->Map
		(
			buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource
		);
		memcpy(subResource.pData, data, dataSize);
		DC->Unmap(buffer, 0);
	}

	D3D11_BUFFER_DESC desc;
	ID3D11Buffer* buffer;

	void* data;
	UINT dataSize;
};