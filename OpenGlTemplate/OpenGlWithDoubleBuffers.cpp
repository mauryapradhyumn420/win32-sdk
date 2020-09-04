#include<windows.h>				//Header file
#include<windowsx.h>

#include<stdio.h>
#include<gl/gl.h>

#pragma comment(lib,"Opengl32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);			//Global function  declaration 

TCHAR szAppName[] = TEXT("FULLSCREEN WINDOW");				//Global variable
HWND ghwnd = NULL;											//Global variable
DWORD dwStyle;												//Global variable
bool gbActiveWindow = false, gbFullScreen = false;									//Global variable
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };			//Global structure
MONITORINFO mi = { sizeof(MONITORINFO) };
HDC ghdc = NULL;
HGLRC ghrc = NULL;
FILE* gFile;

void Initialize(void);
void Display(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wnd;
	MSG msg;
	//int  iHeight, iWidth;
	bool bDone=false;
	HWND hwnd;

	fopen_s(&gFile, "log.txt", "w+");

	if (gFile == NULL)
		exit(0);

	wnd.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wnd.cbSize = sizeof(wnd);
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = szAppName;
	wnd.hInstance = hInstance;
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wnd);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW
		, szAppName,
		TEXT("FULLSCREEN WINDOW"),
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
		100,
		100,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ghwnd = hwnd;

	Initialize();

	ShowWindow(ghwnd, iCmdShow);

	//UpdateWindow(ghwnd);

	fprintf(gFile, "ShowWindow\n");

	SetForegroundWindow(hwnd);

	fprintf(gFile, "SetForeGround\n");

	SetFocus(hwnd);

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;

			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{
			if (gbActiveWindow == true)
			{
				Display();

			}

		}

	}


	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ToggleFullScreen(void);
	void Resize(int, int);
	void Uninitialize(void);

	switch (iMsg)
	{

	case WM_DESTROY:
		Uninitialize();
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		fprintf(gFile, "WM_CLOSE\n");
		DestroyWindow(hwnd);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;

		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;
		default:  break;
		}
		break;

	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;

	case WM_ERASEBKGND:
		return 0;

	case WM_PAINT:
		Display();
		break;
	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;

	default:
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

}


void ToggleFullScreen()
{



	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & ~WS_OVERLAPPEDWINDOW));

				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, (mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top), SWP_NOZORDER | SWP_FRAMECHANGED);
				fprintf(gFile, "Fullscreen\n");
			}


		}

		ShowCursor(TRUE);
		gbFullScreen = true;

	}

	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}

}




void Initialize()
{
	PIXELFORMATDESCRIPTOR pfd;
	int  iPixelFormatIndex;

	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cBlueBits = 8;
	pfd.cGreenBits = 8;
	pfd.cAlphaBits = 8;

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		fprintf(gFile, "ERROR   IN iPixelFormatIndex\n");
		DestroyWindow(ghwnd);

	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		fprintf(gFile, "ERROR IN SetPixelFormat\n");
		DestroyWindow(ghwnd);

	}

	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL)
	{
		fprintf(gFile, "ERROR IN ghrc\n");
		DestroyWindow(ghwnd);

	}

	if (wglMakeCurrent(ghdc, ghrc) == NULL)
	{
		fprintf(gFile, "ERROR IN MakeCurrent\n");
		DestroyWindow(ghwnd);

	}

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	//Resize(WIN_WIDTH,WIN_HEIGHT);
}

void Resize(int iWidth, int iHeight)
{
	if (iHeight == 0)
		iHeight = 1;

	glViewport(0, 0, (GLsizei)iWidth, (GLsizei)iHeight);
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	SwapBuffers(ghdc);

}


void  Uninitialize()
{

	if (gbFullScreen == true)
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(FALSE);
		gbFullScreen = false;

		fprintf(gFile, "\nUnitisalize FULLSCREEN==FALSE");
	}

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
		fprintf(gFile, "\nUnitisalize GetCurrentContext");

	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		fprintf(gFile, "\nUnitisalize DeleteContext");

	}

	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gFile, "\nUnitisalize ReleaseDC");

	}

	if (gFile)
	{
		fprintf(gFile, "\nUnitisalize fclose");
		fclose(gFile);
	}

}