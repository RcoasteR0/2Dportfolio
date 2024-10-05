#include "stdafx.h"
#include "ViewFactory.h"

void ViewFactory::GenerateSRV(const wstring & path, ID3D11ShaderResourceView ** srv)
{
	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,			//�ڿ��� ���� ����̽�
		path.c_str(),	//�ؽ��� �̸�
		nullptr,
		nullptr,
		srv,			//SRV �ּ�
		nullptr
	);
	ASSERT(hr);
}
