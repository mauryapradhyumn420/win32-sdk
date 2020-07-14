#include<windows.h>
#include"Myicon.h"
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

TCHAR szAppName[] = TEXT("MY ICON WINDOW");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wnd;
	MSG msg;
	HWND hwnd;

	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.cbSize = sizeof(wnd);
	wnd.cbClsExtra=0;
	wnd.cbWndExtra = 0;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = szAppName;
	wnd.lpszMenuName = NULL;
	wnd.hInstance = hInstance;
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hCursor = LoadCursor(NULL,IDC_HAND);
	wnd.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));
	wnd.hIconSm= LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wnd);

	hwnd = CreateWindow(szAppName, TEXT("MY ICON"), WS_ACTIVECAPTION | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		, CW_USEDEFAULT,HWND_DESKTOP,NULL,hInstance,NULL);

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
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	switch (iMsg)
	{
	case WM_CREATE:
		MessageBox(hwnd,szAppName,TEXT("WM_CREATE"),MB_OKCANCEL|MB_ICONINFORMATION|MB_SYSTEMMODAL);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd,&ps);
		SetBkColor(hdc, RGB(0, 0, 0));
		SetTextColor(hdc,RGB(255,0,0));
		DrawText(hdc,TEXT("MY ICON"),-1,&rc,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
		EndPaint(hwnd,&ps);
		break;

	default:
		break;
	}


	return (DefWindowProc(hwnd,iMsg,wParam,lParam));

}