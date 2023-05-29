#include "Window.h"
#include "Timer.h"
#include "Exception.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window window(800, 600, L"My window");
	Timer timer;

	MSG msg;
	try {
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
				window.GetRenderer()->ShowFrame();
			}
		}
	}
	catch (const Exception& e) {
		MessageBox(NULL, e.what(), L"Exception Window", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e) {
		MessageBoxA(NULL, e.what(), "Exception Window", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBox(NULL, L"Unknown Exception", L"Exception Window", MB_OK | MB_ICONEXCLAMATION);
	}
}