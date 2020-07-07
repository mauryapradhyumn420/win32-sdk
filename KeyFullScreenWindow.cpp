#include<Windows.h>				//Header file
#include<windowsx.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);			//Global function  declaration 

TCHAR szAppName[] = TEXT("FULLSCREEN WINDOW");				//Global variable
HWND ghwnd=NULL;											//Global variable
DWORD dwStyle;												//Global variable
bool gbFullScreen = false;									//Global variable
WINDOWPLACEMENT wpPrev = {sizeof(WINDOWPLACEMENT)};			//Global structure

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wnd;
	MSG msg;
	//int  iHeight, iWidth;
	RECT rc;
	BOOL bSPI;
	HWND hwnd;

	wnd.style = CS_HREDRAW | CS_VREDRAW;
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

	bSPI = SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	if (bSPI)
	{
		hwnd = CreateWindow(szAppName,
			TEXT("FULLSCREEN WINDOW"),
			WS_OVERLAPPEDWINDOW,
			(rc.right/2) - 300,
			(rc.bottom/2) - 300,
			600,
			600,
			NULL,
			NULL,
			hInstance,
			NULL
		);
		
		ghwnd = hwnd;

		ShowWindow(ghwnd,iCmdShow);
		UpdateWindow(ghwnd);

		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	}
	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ToggleFullScreen(void);

	switch (iMsg)
	{

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		HDC hdc;
		RECT rc;
		PAINTSTRUCT ps;
		HFONT hfont;
		
		
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0,0,0));
		SetTextColor(hdc,RGB(255,255,255));
		
		hfont=CreateFont(48, 18, 0, 20, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
		SelectFont(hdc, hfont);

		DrawText(hdc, TEXT("गुरुर ब्रह्मा गुरुर विष्णु , गुरुर देवो महेश्वरः , गुरुर साक्षात परम ब्रह्म , तस्मै श्री गुरुवे नमः"),-1,&rc, DT_SINGLELINE |DT_CENTER |DT_VCENTER);
		EndPaint(hwnd,&ps);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x46:
		case 0x66:
			ToggleFullScreen();
			break;
		default:  break;
		}
		break;
	default:
		return (DefWindowProc(hwnd, iMsg, wParam, lParam));
		break;
	}

	
}


void ToggleFullScreen()
{

	MONITORINFO mi = { sizeof(MONITORINFO) };

	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd,GWL_STYLE,(dwStyle & ~WS_OVERLAPPEDWINDOW));

				SetWindowPos(ghwnd,HWND_TOP,mi.rcMonitor.left, mi.rcMonitor.top, (mi.rcMonitor.right - mi.rcMonitor.left),( mi.rcMonitor.bottom - mi.rcMonitor.top),SWP_NOZORDER |SWP_FRAMECHANGED);
			    
			}


		}

		ShowCursor(FALSE);
		gbFullScreen = true;

	}
	
	else
	{
		SetWindowLong(ghwnd,GWL_STYLE,(dwStyle | WS_OVERLAPPEDWINDOW ));
		SetWindowPlacement(ghwnd,&wpPrev);
		SetWindowPos(ghwnd,HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER|SWP_NOZORDER|SWP_FRAMECHANGED);

		ShowCursor(TRUE);
		gbFullScreen = false;
	}

}
