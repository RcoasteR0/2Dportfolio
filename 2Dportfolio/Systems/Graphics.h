#pragma once
/*
-direct X��?
���� ���� ������ ���� ms���� ���� ���̺귯���� ����
�׷��� ���α׷��ֿ� Ưȭ��(GPU�� �ٷ�� ���� �ٽ�)

-desc��?
dx ���ο� ���ϴ� ����� �����ϴ� ����
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

private:			// ������, �Ҹ���
	Graphics();
	~Graphics();

	static Graphics* instance;

	void EnumerateAdapters();
	bool EnumerateAdapterOutput(D3DEnumAdapterInfo* adapeterInfo);
	void SetGPUInfo();

private:
	ID3D11Device* device = nullptr;					// �ڿ� ����
	ID3D11DeviceContext* deviceContext = nullptr;	// ����̽� ���ؽ�Ʈ
	IDXGISwapChain* swapChain = nullptr;			// ���� ���۸�
	ID3D11RenderTargetView* rtv = nullptr;			// ȭ�� ȿ��
	D3D11_VIEWPORT viewport = { 0 };				// ȭ�� ����
	Color clearColor = 0xff000000;				// ����

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
	//������, �Ҹ���
	D3DEnumAdapterInfo() = default;
	~D3DEnumAdapterInfo();

	UINT adapterOrdinal = 0;
	//GPU ������ �޸𸮸� �޴� com �������̽�
	IDXGIAdapter1* adapter = nullptr;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	//����� ����
	D3DEnumOutputInfo* outputInfo = nullptr;

private:
	const D3DEnumAdapterInfo& operator = (const D3DEnumAdapterInfo& rhs);
};

class D3DEnumOutputInfo
{
public:
	//������, �Ҹ���
	D3DEnumOutputInfo() = default;
	~D3DEnumOutputInfo();

	//����� ������ �޴� com �������̽�
	IDXGIOutput* output = nullptr;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	//FPS
	UINT numerator = 0;
	UINT denominator = 1;

private:
	const D3DEnumOutputInfo& operator = (const D3DEnumOutputInfo& rhs);
};