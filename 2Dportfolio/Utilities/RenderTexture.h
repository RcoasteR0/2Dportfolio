#pragma once

class RenderTexture
{
public:
	RenderTexture();
	~RenderTexture();

	void Initialize();

	ID3D11ShaderResourceView* GetSRV() { return shaderResourceView; }
	void RenderToTexture();

	void SaveTexture(const wstring& path);

private:
	ID3D11Texture2D* renderTargetTexture = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11ShaderResourceView* shaderResourceView = nullptr;
};
