/**
* Entry point Game Main function included
*
* Mike Nielsen
* 2017
*/

#include "stdneva.h"


#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


#ifdef WIN32
#include "window\win32window.h"
#include "renderer\direct3d11\direct3d11graphics.h"
#include "renderer\direct3d11\direct3d11camera.h"


static long __stdcall WindowProc(HWND hwnd, unsigned int msg, unsigned int wParam, long lParam);


/*----------------------------------------------
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	{
		/* Windows init */
		const char* name = "Neva";
		const char* description = "Neva Game";
		float width = 1200.0f;
		float height = 600.0f;

		Window::Win32Window* win32Window = new Window::Win32Window();
		win32Window->Setup(name, description, width, height, hInstance, pCmdLine, nCmdShow);

		/* Direct3D11Renderer init */
		float depthPlane = 1000.0f;
		float nearPlane = 0.03f;
		bool vysnc = true;
		bool fullscreen = false;

		Direct3D11::Direct3D11Renderer* directX11renderer = new Direct3D11::Direct3D11Renderer();
		directX11renderer->Setup(width, height, vysnc, win32Window->GetWindowHandle(), fullscreen, nearPlane, depthPlane);

		/* Direct3D11Camera init */

		Direct3D11::Direct3D11Camera* directX11Camera = new Direct3D11::Direct3D11Camera();
		directX11Camera->SetPosition(0.0f, 0.0f, -10.0f);

		MSG msg;
		bool done;
		// Initialize the message structure.
		ZeroMemory(&msg, sizeof(MSG));

		// Loop until there is a quit message from the window or the user.
		done = false;
		while (!done)
		{
			// Handle the windows messages.
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// If windows signals to end the application then exit out.
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				// begin frame
				directX11renderer->BeginScene(1.0f, 0.0f, 0.8f, 1.0f);


				// end frame
				directX11renderer->EndScene();
			}
		}
	}

	printf("Done! \n");

	_CrtDumpMemoryLeaks();

	
	return 0;
}

#endif // WIN32

