#include "Window.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window(800, 600, L"My oop window");
	Window window2(1000, 200, L"Window 2");

	MSG msg;
	BOOL bRet;
	while (bRet = GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (bRet == -1) {
		return -1;
	}
	else {
		return (int)msg.wParam;
	}
}