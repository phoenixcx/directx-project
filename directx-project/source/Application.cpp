#include "Window.h"
#include "Timer.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Window window(800, 600, L"My window");
	Timer timer;

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
			window.GetRenderer()->ShowFrame();
		}
	}
}
