#include<Windows.h>
#include"Myicon.h"

int iKey;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("COLOR KEY CHANGER");
 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance ,LPSTR lpszCmdLine ,int iCmdShow)
{
	WNDCLASSEX wnd;
	MSG msg;
	HWND hwnd;

	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.cbSize = sizeof(wnd);
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hCursor = LoadCursor(NULL,IDC_ARROW);
	wnd.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wnd.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = szAppName;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wnd);

	hwnd =CreateWindow(szAppName,
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
	
	ShowWindow(hwnd,iCmdShow);
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
	static HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;

	switch (iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case VK_SPACE:
			
			iKey++;
			if (iKey > 5)
				iKey =0;

			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		if (iKey == 0)
		{
			SetTextColor(hdc, RGB(255, 57, 34));
		}
		if (iKey == 1)
		{
			SetTextColor(hdc,RGB(255,0,0));
		}
		if (iKey == 2)
		{
			SetTextColor(hdc, RGB(0, 255, 0));
		}
		if(iKey==3)
		{
			SetTextColor(hdc, RGB(0, 0, 255));
		}
		if (iKey == 4)
		{
			SetTextColor(hdc, RGB(0, 47, 255));
		}
		if (iKey == 5)
		{
			SetTextColor(hdc, RGB(0, 28, 255));
		}
		DrawText(hdc,TEXT("COLOR CHANGER"),-1,&rc,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		EndPaint(hwnd,&ps);
		break;

	default:
		break;
	}

	return(DefWindowProc(hwnd,iMsg,wParam,lParam));


}