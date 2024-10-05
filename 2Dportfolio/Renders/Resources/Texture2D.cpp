#include "stdafx.h"
#include "Texture2D.h"

using namespace DirectX;

vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath, D3DX11_IMAGE_LOAD_INFO * loadInfo)
	: filePath(filePath)
{
	Textures::Load(this, loadInfo);
}

Texture2D::~Texture2D()
{
}

D3D11_TEXTURE2D_DESC Texture2D::ReadPixel(DXGI_FORMAT readFormat, vector<D3DXCOLOR>* pixels)
{
	ID3D11Texture2D* srcTexture;
	view->GetResource((ID3D11Resource**)&srcTexture);

	return ReadPixel(srcTexture, readFormat, pixels);
}

D3D11_TEXTURE2D_DESC Texture2D::ReadPixel(ID3D11Texture2D * src, DXGI_FORMAT readFormat, vector<D3DXCOLOR>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	src->GetDesc(&srcDesc);

	//2D 텍스쳐 속성 정의
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
	desc.Width = srcDesc.Width;
	desc.Height = srcDesc.Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = readFormat;
	desc.SampleDesc = srcDesc.SampleDesc;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.Usage = D3D11_USAGE_STAGING;

	//2D 텍스쳐 생성
	ID3D11Texture2D* texture;
	ASSERT(DEVICE->CreateTexture2D(&desc, nullptr, &texture));			//texture에 desc 전달
	ASSERT(D3DX11LoadTextureFromTexture(DC, src, nullptr, texture));	//texture에 src 전달

	//픽셀 색생 불러오기
	UINT* colors = new UINT[desc.Width * desc.Height];
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(texture, 0, D3D11_MAP_READ, NULL, &subResource);
	{
		memcpy(colors, subResource.pData, sizeof(UINT) * desc.Width * desc.Height);	//색상값 colors에 전달
	}
	DC->Unmap(texture, 0);

	//색상값 벡터에 저장
	for (UINT y = 0; y < desc.Height; y++)
	{
		for (UINT x = 0; x < desc.Width; x++)
		{
			UINT index = desc.Width * y + x;

			float f = 1.0f / 255.0f;

			float b = f * (float)((0x000000FF & colors[index]) >> 0);
			float g = f * (float)((0x0000FF00 & colors[index]) >> 8);
			float r = f * (float)((0x00FF0000 & colors[index]) >> 16);
			float a = f * (float)((0xFF000000 & colors[index]) >> 24);

			pixels->push_back(D3DXCOLOR(r, g, b, a));
		}
	}

	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(texture);

	return desc;
}

void Texture2D::SaveFile(wstring filePath)
{
	ID3D11Texture2D* srcTexture;
	view->GetResource((ID3D11Resource**)&srcTexture);

	SaveFile(filePath, srcTexture);
}

void Texture2D::SaveFile(wstring filePath, ID3D11Texture2D * originalTex, vector<D3DXCOLOR>& pixels, UINT width, UINT height)
{
	view->GetResource((ID3D11Resource**)&originalTex);
	D3D11_TEXTURE2D_DESC originalDesc;
	originalTex->GetDesc(&originalDesc);

	//2D 텍스쳐 속성 정의
	ID3D11Texture2D* srcTexture;
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));
	destDesc.Width = width;
	destDesc.Height = height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = originalDesc.Format;
	destDesc.SampleDesc = originalDesc.SampleDesc;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	destDesc.Usage = D3D11_USAGE_STAGING;

	//2D 텍스쳐 생성
	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &srcTexture);
	ASSERT(hr);

	//색상값 불러오기
	UINT* rawPixels = new UINT[width * height];
	for (UINT y = 0; y < height; y++)
	{
		for (UINT x = 0; x < width; x++)
		{
			UINT index = width * y + x;

			rawPixels[index] = pixels[index];
		}
	}

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(srcTexture, 0, D3D11_MAP_WRITE, NULL, &subResource);
	{
		memcpy(subResource.pData, rawPixels, sizeof(UINT) * width * height);
	}
	DC->Unmap(srcTexture, 0);

	SAFE_DELETE_ARRAY(rawPixels);

	SaveFile(filePath, srcTexture);
}

void Texture2D::SaveFile(wstring file, ID3D11Texture2D * src)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	src->GetDesc(&srcDesc);

	ID3D11Texture2D* dest;
	D3D11_TEXTURE2D_DESC destDesc;
	ZeroMemory(&destDesc, sizeof(D3D11_TEXTURE2D_DESC));
	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	destDesc.SampleDesc = srcDesc.SampleDesc;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	destDesc.Usage = D3D11_USAGE_STAGING;

	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &dest);
	ASSERT(hr);

	//텍스쳐 2D텍스쳐로 불러오기
	hr = D3DX11LoadTextureFromTexture(DC, src, nullptr, dest);
	ASSERT(hr);

	//확장자명
	wstring ext = Path::GetExtension(file);
	transform(ext.begin(), ext.end(), ext.begin(), toupper);

	if (ext == L"BMP")
		hr = D3DX11SaveTextureToFile(DC, dest, D3DX11_IFF_BMP, file.c_str());	//확장자명이 BMP일때 BMP로 저장
	else
		hr = D3DX11SaveTextureToFile(DC, dest, D3DX11_IFF_PNG, file.c_str());	//PNG로 저장

	ASSERT(hr);

	SAFE_RELEASE(dest);
}

ID3D11Texture2D * Texture2D::GetTexture()
{
	ID3D11Texture2D* texture;
	view->GetResource((ID3D11Resource**)&texture);

	return texture;
}

void Textures::Create()
{
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.view);
}

void Textures::Load(Texture2D * texture, D3DX11_IMAGE_LOAD_INFO * loadInfo)
{
	HRESULT hr;

	TexMetadata metaData;
	wstring ext = Path::GetExtension(texture->filePath);

	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		ASSERT(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		ASSERT(hr);
	}
	else if (ext == L"hdr")
	{
		assert(false);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		ASSERT(hr);
	}

	UINT width = metaData.width;
	UINT height = metaData.height;

	if (loadInfo != nullptr)
	{
		width = loadInfo->Width;
		height = loadInfo->Height;

		metaData.width = loadInfo->Width;
		metaData.height = loadInfo->Height;
	}

	TextureDesc desc;
	desc.file = texture->filePath;
	desc.width = width;
	desc.height = height;

	TextureDesc exist;
	bool bExist = false;
	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	if (bExist == true)
	{
		texture->metaData = exist.metaData;
		texture->view = exist.view;
	}
	else
	{
		ScratchImage image;

		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			ASSERT(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			ASSERT(hr);
		}
		else if (ext == L"hdr")
		{
			assert(false);
		}
		else
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			ASSERT(hr);
		}

		ID3D11ShaderResourceView* view;

		hr = CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), metaData, &view);
		ASSERT(hr);

		desc.file = texture->filePath;
		desc.width = metaData.width;
		desc.height = metaData.height;
		desc.view = view;
		desc.metaData = metaData;

		texture->view = view;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
}
