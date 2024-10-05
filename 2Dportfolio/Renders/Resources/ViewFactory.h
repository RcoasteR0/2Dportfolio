#pragma once

class ViewFactory
{
public:
	static void GenerateSRV(const wstring& path, ID3D11ShaderResourceView** srv);
};
