#include "Renderer.h"
#include "debug/Exception.h"
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
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = NULL;

	UINT flags = NULL;
#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DXGI_HR_CALL(D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&m_pSwapChain,
		&m_pDevice,
		NULL,
		&m_pDeviceContext
	));

	ID3D11Resource* backBuffer;
	DXGI_HR_CALL(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer)));
	if (backBuffer != nullptr) {
		m_pDevice->CreateRenderTargetView(backBuffer, NULL, &m_pRenderTargetView);
		backBuffer->Release();
	}
	else {
		m_pRenderTargetView = nullptr;
	}
}

Renderer::~Renderer() {}

void Renderer::ClearRenderTargetView() {
	FLOAT color[4]{ 0.9f, 0.9f, 0.0f, 1.0f };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), color);
}

void Renderer::ShowFrame() {
	DXGI_HR_CALL(m_pSwapChain->Present(1u, 0u));
}

void Renderer::DrawTriangle() {
	struct Vertex {
		float x;
		float y;
	};
	
	const Vertex vertices[]{
		{ -0.5f, -0.5f },
		{  0.0f,  0.5f },
		{  0.5f, -0.5f }
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0u;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertices;
	data.SysMemPitch = 0u;
	data.SysMemSlicePitch = 0u;

	DXGI_HR_CALL(m_pDevice->CreateBuffer(&bufferDesc, &data, &pVertexBuffer));

	UINT stride = sizeof(Vertex);
	UINT offset = 0u;
	DXGI_CALL(m_pDeviceContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset));

	DXGI_CALL(m_pDeviceContext->Draw(3u, 0u));
}