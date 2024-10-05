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

	//ÇÈ¼¿ ¼ÎÀÌ´õ ÄÄÆÄÀÏ
	CompileShader(path, entryName, "ps_5_0", &blob);

	//ÇÈ¼¿ ¼ÎÀÌ´õ »ý¼º
	HRESULT hr = DEVICE->CreatePixelShader
	(
		blob->GetBufferPointer(),	//¼ÎÀÌ´õ µ¥ÀÌÅÍ ÁÖ¼Ò
		blob->GetBufferSize(),		//¼ÎÀÌ´õ Å©±â
		nullptr,
		&shader						//ÀúÀåÇÒ ÇÈ¼¿ ¼ÎÀÌ´õ ÁÖ¼Ò
	);
	ASSERT(hr);
}

void PixelShader::Clear()
{
	//º¯¼ö ÃÊ±âÈ­
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void PixelShader::SetShader()
{
	DC->PSSetShader(shader, nullptr, 0);
}
