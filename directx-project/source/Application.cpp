#include "Window.h"

//LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//	switch (uMsg) {
//	case WM_CLOSE:
//		PostQuitMessage(69);
//		break;
//	case WM_KEYDOWN:
//		if (wParam == 'F') {
//			SetWindowText(hWnd, L"1");
//		}
//		break;
//	case WM_KEYUP:
//		if (wParam == 'F') {
//			SetWindowText(hWnd, L"0");
//		}
//		break;
//	case WM_CHAR:
//		if (wParam == 'f') {
//			SetWindowText(hWnd, L"Lowercase f");
//		}
//		break;
//	case WM_LBUTTONDOWN:
//	{
//		const POINTS pts = MAKEPOINTS(lParam);
//		std::wstringstream wss;
//		wss << L"(" << pts.x << L"," << pts.y << L")" << L"\n";
//		SetWindowText(hWnd, wss.str().c_str());
//		break;
//	}
//	default:
//		return DefWindowProc(hWnd, uMsg, wParam, lParam);
//		break;
//	}
//}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//const auto className = L"Application Class";

	//WNDCLASSEX wc{};
	//wc.cbSize = sizeof(WNDCLASSEX);
	//wc.style = CS_OWNDC;
	//wc.lpfnWndProc = WindowProc;
	//wc.hInstance = hInstance;
	//wc.lpszClassName = className;

	//RegisterClassEx(&wc);

	//HWND hWnd = CreateWindowExW(WS_EX_LEFT, className, L"My Window",
	//	WS_BORDER | WS_MINIMIZEBOX | WS_SYSMENU,
	//	200, 200, 800, 600,
	//	nullptr, nullptr, hInstance, nullptr);

	//if (hWnd == NULL)
	//{
	//	return -1;
	//}

	//ShowWindow(hWnd, SW_SHOW);

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