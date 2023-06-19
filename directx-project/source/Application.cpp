#include "Window.h"
#include "debug/Exception.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	try {
		Window window(800, 600, L"My window");

		MSG msg;

		while (true) {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					return static_cast<int>(msg.wParam);
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				window.GetRenderer()->ClearRenderTargetView();
				window.GetRenderer()->DrawTriangle();
				window.GetRenderer()->ShowFrame();
			}
		}
		return 0;
	}
	catch (const Exception& e) {
		MessageBox(NULL, e.what(), e.GetExceptionType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e) {
		MessageBoxA(NULL, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBox(NULL, L"Unknown Exception", L"Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
}