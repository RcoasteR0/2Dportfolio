#include "stdafx.h"
#include "ViewFactory.h"

void ViewFactory::GenerateSRV(const wstring & path, ID3D11ShaderResourceView ** srv)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,			//자원을 읽을 디바이스
		path.c_str(),	//텍스쳐 이름
		nullptr,
		nullptr,
		srv,			//SRV 주소
		nullptr
	);
	ASSERT(hr);
}
