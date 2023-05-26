#pragma once
#include <Windows.h>

class Window {
private:
	class WindowClass {
	public:
		static WindowClass& GetInstance();
		const wchar_t* GetName() const;
		const HINSTANCE GetHInstance() const;

	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;

		static constexpr const wchar_t* name = L"DirectX learning window class";
		HINSTANCE m_HInstance;
	};

public:
	Window(int width, int height, const wchar_t* name);
	~Window();

	Window() = delete;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void SetTitle(const wchar_t* title);

private:
	static LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	RECT m_WindowRect;
	HWND m_HWnd;
};