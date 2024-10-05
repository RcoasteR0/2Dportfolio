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
	��������ȭ: �������� ����� �ֻ����� �����ش�
	ȭ�� �ֻ������� GPU���� �����ϴ� �������� ������ Ƽ� ������ �߻��ϱ� ������
	�����Ӱ� ȭ�� �ֻ����� ��������Ѵ�.
	*/
	if (bVsync)
	{
		//ù��° ���� �׷���ī���� �ֻ����� �����´�
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

	//D2D���� ����ü���� ���
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	//����׿��� ����� �÷���
#if defined(_DEBUG)
	//�帧 ����, ����ȭ ��ŵ
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
	for (UINT i = 0; i < adapterInfos.size(); i++)	//GPU ����ŭ �ݺ�
	{
		//DedicatedVideoMemory: GPU������ ����ϴ� ���� ���� �޸�
		if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVideoMemory)	//���� ū GPU�޸𸮸� �����´�
		{
			selectedAdapterIndex = i;
			maxVideoMemory = adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
		}
	}

	numerator = adapterInfos[0]->outputInfo->numerator;
	denominator = adapterInfos[0]->outputInfo->denominator;

	gpuMemorySize = adapterInfos[selectedAdapterIndex]->adapterDesc.DedicatedVideoMemory / 1024 / 1024;	//GPU�޸𸮸� �ް�����Ʈ��
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
		//���� GPU ����
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
	//���� ���÷��� ����
	IDXGIOutput* output = nullptr;
	HRESULT hr = adapeterInfo->adapter->EnumOutputs(0, &output);

	if(DXGI_ERROR_NOT_FOUND == hr)
	return false;

	D3DEnumOutputInfo* outputInfo = new D3DEnumOutputInfo();
	ZeroMemory(outputInfo, sizeof(D3DEnumOutputInfo));

	//���÷����� desc ����
	hr = output->GetDesc(&outputInfo->outputDesc);
	ASSERT(hr);

	//outputInfo�� ���÷��� ���� ����
	outputInfo->output = output;

	UINT numModes = 0;
	DXGI_MODE_DESC* displayModes = nullptr;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//��������� �÷��� ����
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	ASSERT(hr);

	displayModes = new DXGI_MODE_DESC[numModes];
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes);
	ASSERT(hr);

	//���÷����� ȭ���ֻ��� ����
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

	//GPU ������ ���� Ŭ������ ���÷��� ���� ����
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
	deviceContext->OMSetRenderTargets(1, &rtv, nullptr);		//���������� �׷��� ������ ����
	deviceContext->RSSetViewports(1, &viewport);				//����Ʈ ���
	deviceContext->ClearRenderTargetView(rtv, clearColor);		//ȭ���� �����
}

void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);	//����ۿ� ����Ʈ���۸� ��ü
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
