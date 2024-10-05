#pragma once
/*
-direct X란?
비디오 게임 개발을 위해 ms에서 만든 라이브러리의 집합
그래픽 프로그래밍에 특화됨(GPU를 다루는 것이 핵심)

-desc란?
dx 내부에 원하는 명령을 전달하는 설명서
*/

class D3DEnumAdapterInfo;
class D3DEnumOutputInfo;

class Graphics : public Singleton<Graphics>
{
public:
	friend class Singleton<Graphics>;

	void Begin();
	void End();

	void SetViewport();
	Color GetClearColor() { return clearColor; }
	void SetBackBufferToRTV();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return deviceContext; }

	void Resize(const UINT& width, const UINT& height);
	void SetViewport(const UINT& width, const UINT& height);

private:
	void CreateSwapChain();
	void CreateRenderTargetView();
	void DeleteSurface();

private:			// 생성자, 소멸자
	Graphics();
	~Graphics();

	static Graphics* instance;

	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapeterInfo);
	void SetGPUInfo();

private:
	ID3D11Device* device = nullptr;					// 자원 생성
	ID3D11DeviceContext* deviceContext = nullptr;	// 디바이스 컨텍스트
	IDXGISwapChain* swapChain = nullptr;			// 더블 버퍼링
	ID3D11RenderTargetView* rtv = nullptr;			// 화면 효과
	D3D11_VIEWPORT viewport = { 0 };				// 화면 영역
	Color clearColor = 0xff000000;				// 색상

	UINT numerator;
	UINT denominator;

	UINT gpuMemorySize;
	wstring gpuDescription;

	vector<D3DEnumAdapterInfo *> adapterInfos;
	int selectedAdapterIndex;

	bool bVsync = true;
};

////////////////////////////////////////////////////////////////////////////

class D3DEnumAdapterInfo
{
public:
	//생성자, 소멸자
	D3DEnumAdapterInfo() = default;
	~D3DEnumAdapterInfo();

	UINT adapterOrdinal = 0;
	//GPU 정보와 메모리를 받는 com 인터페이스
	IDXGIAdapter1* adapter = nullptr;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	//모니터 정보
	D3DEnumOutputInfo* outputInfo = nullptr;

private:
	const D3DEnumAdapterInfo& operator = (const D3DEnumAdapterInfo& rhs);
};

class D3DEnumOutputInfo
{
public:
	//생성자, 소멸자
	D3DEnumOutputInfo() = default;
	~D3DEnumOutputInfo();

	//모니터 정보를 받는 com 인터페이스
	IDXGIOutput* output = nullptr;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	//FPS
	UINT numerator = 0;
	UINT denominator = 1;

private:
	const D3DEnumOutputInfo& operator = (const D3DEnumOutputInfo& rhs);
};