#include "Window.h"
#include "debug/WindowsMessageMap.h"
#include "debug/Exception.h"
#include <sstream>


// WindowClass

Window::WindowClass::WindowClass() : m_HInstance (GetModuleHandleW(NULL)) {
	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = MessageHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetHInstance();
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GetName();
	wc.hIconSm = NULL;

	RegisterClassExW(&wc);
}

Window::WindowClass::~WindowClass() {
	UnregisterClassW(GetName(), GetHInstance());
}

Window::WindowClass& Window::WindowClass::GetInstance() {
	static WindowClass wc;
	return wc;
}

const wchar_t* Window::WindowClass::GetName() const {
	return name;
}

const HINSTANCE Window::WindowClass::GetHInstance() const {
	return m_HInstance;
}


// Window

Window::Window(int width, int height, const wchar_t* name) {
	m_WindowRect.left = 0;
	m_WindowRect.right = width;
	m_WindowRect.top = 0;
	m_WindowRect.bottom = height;

	AdjustWindowRect(&m_WindowRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	m_HWnd = CreateWindowExW(
		WS_EX_LEFT, WindowClass::GetInstance().GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		100, 100, m_WindowRect.right - m_WindowRect.left, m_WindowRect.bottom - m_WindowRect.top,
		NULL, NULL, WindowClass::GetInstance().GetHInstance(), this);

	ShowWindow(m_HWnd, SW_SHOW);

	TRY_THROW(m_Renderer = new Renderer(m_HWnd));
}

Window::~Window() {
	delete m_Renderer;
	DestroyWindow(m_HWnd);
}

Renderer* Window::GetRenderer() const noexcept {
	return m_Renderer;
}

void Window::SetTitle(const wchar_t* title) {
	SetWindowTextW(m_HWnd, title);
}

LRESULT CALLBACK Window::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	//static WindowsMessageMap wmm;
	//OutputDebugString(wmm(uMsg, lParam, wParam));

	switch (uMsg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == 'F') {
			SetWindowText(hWnd, L"1");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F') {
			SetWindowText(hWnd, L"0");
		}
		break;
	case WM_CHAR:
		if (wParam == 'f') {
			SetWindowText(hWnd, L"Lowercase f");
		}
		break;
	case WM_LBUTTONDOWN:
	{
		const POINTS pts = MAKEPOINTS(lParam);
		std::wstringstream wss;
		wss << L"(" << pts.x << L"," << pts.y << L")" << L"\n";
		SetWindowText(hWnd, wss.str().c_str());
		break;
	}
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
}