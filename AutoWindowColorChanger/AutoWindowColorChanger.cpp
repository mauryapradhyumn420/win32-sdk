#include<Windows.h>
#include"Myicon.h"
#define TIMER 1108

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("COLOR KEY CHANGER");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wnd;
	MSG msg;
	HWND hwnd;

	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.cbSize = sizeof(wnd);
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wnd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = szAppName;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wnd);

	hwnd = CreateWindow(szAppName,
		TEXT("COLOR CHANGER"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
RECT rc;
PAINTSTRUCT ps;
static HDC hdc;
static int iFlag,r=0,g=0,b=220,iColor=0;
static HBRUSH hBrush[8];
		
	switch (iMsg)
	{
	case WM_CREATE:
		for(iFlag=0;iFlag<8;iFlag++)
		{
		if(iFlag%2==0)
			{
			r=r+95;		
			b=r-30;
			}
		else
			{
			g=g+60;
			r=r-50;	
			}		
		hBrush[iFlag]=CreateSolidBrush(RGB(r,g,b));
		
		}
		
		SetTimer(hwnd,TIMER,4000,NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_TIMER:
		KillTimer(hwnd,TIMER);
		InvalidateRect(hwnd, NULL, TRUE);		
		break;
	case WM_PAINT:
		if(iFlag>=8)
			iFlag=0;

		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc,&rc,hBrush[iFlag]);
		EndPaint(hwnd, &ps);
		SetTimer(hwnd,TIMER,4000,NULL);
		++iFlag;
	
		break;
	
	default:
		break;
	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));


}