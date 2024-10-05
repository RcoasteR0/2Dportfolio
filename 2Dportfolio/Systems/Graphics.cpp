#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	SetGPUInfo();
	CreateSwapChain();
}

Graphics::~Graphics()
{
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}

void Graphics::SetGPUInfo()
{
	EnumerateAdapters();
}

void Graphics::CreateSwapChain()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(swapChain);

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	
	/*
	수직동기화: 프레임을 모니터 주사율에 맞춰준다
	화면 주사율보다 GPU에서 연산하는 프레임이 높으면 티어링 현상이 발생하기 때문에
	프레임과 화면 주사율을 맞춰줘야한다.
	*/
	if (bVsync)
	{
		//첫번째 외장 그래픽카드의 주사율을 가져온다
		desc.BufferDesc.RefreshRate.Numerator = adapterInfos[0]->outputInfo->numerator;
		desc.BufferDesc.RefreshRate.Denominator = adapterInfos[0]->outputInfo->denominator;
	}
	else
	{
		desc.BufferDesc.RefreshRate.Numerator = 144;
		desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferCount = 1;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = handle;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	desc.Flags = 0;

	//D2D에서 스왑체인을 사용
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	//디버그에서 사용할 플래그
#if defined(_DEBUG)
	//흐름 제어, 최적화 스킵
	creationFlags = D3DCOMPILE_PREFER_FLOW_CONTROL | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // definde(_DEBUG)

	vector<D3D_FEATURE_LEVEL> featureLevel
	{
		D3D_FEATURE_LEVEL_11_1,
		/*D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0*/
	};

	UINT maxVideoMemory = 0;
	for (UINT i = 0; i < adapterInfos.size(); i++)	//GPU 수만큼 반복
	{
		//DedicatedVideoMemory: GPU에서만 사용하는 순수 전용 메모리
		if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVideoMemory)	//가장 큰 GPU메모리를 가져온다
		{
			selectedAdapterIndex = i;
			maxVideoMemory = adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
		}
	}

	numerator = adapterInfos[0]->outputInfo->numerator;
	denominator = adapterInfos[0]->outputInfo->denominator;

	gpuMemorySize = adapterInfos[selectedAdapterIndex]->adapterDesc.DedicatedVideoMemory / 1024 / 1024;	//GPU메모리를 메가바이트로
	gpuDescription = adapterInfos[selectedAdapterIndex]->adapterDesc.Description;

	cout << "DedicatedVideoMemory : " << gpuMemorySize << endl;
	wcout << "GPU Description : " << gpuDescription << endl;

	cout << "Numerator : " << numerator << endl;
	cout << "Denominator : " << denominator << endl;

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		adapterInfos[selectedAdapterIndex]->adapter,
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		creationFlags,
		featureLevel.data(),
		featureLevel.size(),
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		nullptr,
		&deviceContext
	);
	ASSERT(hr);

	Resize(WinMaxWidth, WinMaxHeight);
}

void Graphics::EnumerateAdapters()
{
	IDXGIFactory1* factory;
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
		return;

	UINT index = 0;
	while (true)
	{
		//현재 GPU 정보
		IDXGIAdapter1* adapter;
		HRESULT hr = factory->EnumAdapters1(index, &adapter);

		if (hr == DXGI_ERROR_NOT_FOUND)
			break;

		ASSERT(hr);

		D3DEnumAdapterInfo* adapterInfo = new D3DEnumAdapterInfo();
		ZeroMemory(adapterInfo, sizeof(D3DEnumAdapterInfo));
		adapterInfo->adapterOrdinal = index;

		adapter->GetDesc1(&adapterInfo->adapterDesc);
		adapterInfo->adapter = adapter;

		EnumerateAdapterOutput(adapterInfo);
		adapterInfos.push_back(adapterInfo);

		++index;
	}

	SAFE_RELEASE(factory);
}

bool Graphics::EnumerateAdapterOutput(D3DEnumAdapterInfo * adapeterInfo)
{
	//현재 디스플레이 정보
	IDXGIOutput* output = nullptr;
	HRESULT hr = adapeterInfo->adapter->EnumOutputs(0, &output);

	if(DXGI_ERROR_NOT_FOUND == hr)
	return false;

	D3DEnumOutputInfo* outputInfo = new D3DEnumOutputInfo();
	ZeroMemory(outputInfo, sizeof(D3DEnumOutputInfo));

	//디스플레이의 desc 전달
	hr = output->GetDesc(&outputInfo->outputDesc);
	ASSERT(hr);

	//outputInfo에 디스플레이 정보 전달
	outputInfo->output = output;

	UINT numModes = 0;
	DXGI_MODE_DESC* displayModes = nullptr;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//색상포멧과 플래그 전달
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	ASSERT(hr);

	displayModes = new DXGI_MODE_DESC[numModes];
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes);
	ASSERT(hr);

	//디스플레이의 화면주사율 전달
	for (UINT i = 0; i < numModes; i++)
	{
		bool bCheck = true;
		bCheck &= displayModes[i].Width == WinMaxWidth;
		bCheck &= displayModes[i].Height == WinMaxHeight;

		if (bCheck == true)
		{
			outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
			outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
		}
	}

	//GPU 정보를 가진 클래스에 디스플레이 정보 전달
	adapeterInfo->outputInfo = outputInfo;
	SAFE_DELETE_ARRAY(displayModes);

	return true;
}

void Graphics::Resize(const UINT & width, const UINT & height)
{
	DeleteSurface();
	{
		HRESULT hr = swapChain->ResizeBuffers
		(
			0,
			width,
			height,
			DXGI_FORMAT_UNKNOWN,
			0
		);
	}
	CreateRenderTargetView();
	SetViewport(width, height);
}

void Graphics::CreateRenderTargetView()
{
	ID3D11Texture2D* backBuffer = nullptr;
	HRESULT hr = swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backBuffer
	);
	ASSERT(hr);

	hr = device->CreateRenderTargetView
	(
		backBuffer,
		nullptr,
		&rtv
	);
	ASSERT(hr);
	SAFE_RELEASE(backBuffer);
}

void Graphics::SetViewport(const UINT & width, const UINT & height)
{
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 0.0f;
}

void Graphics::Begin()
{
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);		//최종적으로 그려질 랜더를 설정
	deviceContext->RSSetViewports(1, &viewport);				//뷰포트 출력
	deviceContext->ClearRenderTargetView(rtv, clearColor);		//화면을 지운다
}

void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);	//백버퍼와 프론트버퍼를 교체
	assert(SUCCEEDED(hr));
}

void Graphics::SetViewport()
{
	deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::SetBackBufferToRTV()
{
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);
	deviceContext->ClearRenderTargetView(rtv, clearColor);
}

void Graphics::DeleteSurface()
{
	SAFE_RELEASE(rtv);
}

////////////////////////////////////////////////////////////////////////////

D3DEnumAdapterInfo::~D3DEnumAdapterInfo()
{
	SAFE_RELEASE(adapter);
	SAFE_DELETE(outputInfo);
}

D3DEnumOutputInfo::~D3DEnumOutputInfo()
{
	SAFE_RELEASE(output);
}
