#pragma once

#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>

class Renderer {
public:
	Renderer(HWND hWnd);
	~Renderer();

	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer operator=(const Renderer&) = delete;

	void ClearRenderTargetView();
	void ShowFrame();

private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
};