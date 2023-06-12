#include "Renderer.h"
#include "Exception.h"
#include <comdef.h>

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd;
	scd.BufferDesc.Width = 0;
	scd.BufferDesc.Height = 0;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = NULL;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = NULL;

	HRESULT res = D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_PSwapChain,
		&m_PDevice,
		NULL,
		&m_PDeviceContext
	);

	if (res != S_OK) {
		THROWHREXCEPT(res);
	}

	ID3D11Resource* backBuffer;
	m_PSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer));
	if (backBuffer != nullptr) {
		m_PDevice->CreateRenderTargetView(backBuffer, NULL, &m_PRenderTargetView);
		backBuffer->Release();
	}
	else {
		m_PRenderTargetView = nullptr;
	}
}

Renderer::~Renderer() {
	if (m_PSwapChain != nullptr) {
		m_PSwapChain->Release();
	}
	if (m_PDevice != nullptr) {
		m_PDevice->Release();
	}
	if (m_PDeviceContext != nullptr) {
		m_PDeviceContext->Release();
	}
	if (m_PRenderTargetView != nullptr) {
		m_PRenderTargetView->Release();
	}
}

void Renderer::ClearRenderTargetView() {
	FLOAT color[4]{ 0.9f, 0.9f, 0.0f, 1.0f };
	m_PDeviceContext->ClearRenderTargetView(m_PRenderTargetView, color);
}

void Renderer::ShowFrame() {
	m_PSwapChain->Present(1u, 0u);
}