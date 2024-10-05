#pragma once

class IShader
{
public:
	//생성자, 소멸자
	IShader();
	virtual ~IShader() = default;
	
	//셰이더 생성
	virtual void Create(const wstring path, const string entryName) = 0;
	//초기화
	virtual void Clear() = 0;
	//셰이더 사용 설정
	virtual void SetShader() = 0;

protected:
	//셰이더 컴파일
	void CompileShader(wstring path, string entryName, string profile, ID3DBlob ** blob);

	wstring path = L"";
	string entryName = "";
	string profile = "";

private:
	//오류 확인
	void CheckShaderError(HRESULT hr, ID3DBlob* error);
};