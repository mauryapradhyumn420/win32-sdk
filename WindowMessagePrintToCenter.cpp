#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("My Window");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wnd;

	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.cbSize = sizeof(wnd);
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = szAppName;
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hCursor = LoadCursor(NULL,IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wnd.hIconSm = LoadIcon(NULL,IDI_EXCLAMATION);
	wnd.hInstance = hInstance;

	RegisterClassEx(&wnd);

	hwnd=CreateWindow(szAppName,
		TEXT("PAINT WINDOW"),
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

	return((int)msg.wParam);
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;

	switch (iMsg)
	{
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		GetClientRect(hwnd,&rc);
		hdc=BeginPaint(hwnd,&ps);
	//	hdc = GetDC(hwnd);		optional to BeginPaint
	
		SetBkColor(hdc,RGB(0,0,0));
		SetTextColor(hdc, RGB(0, 255, 0));
		DrawText(hdc,TEXT("India is my country"),-1,&rc,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		
		//ReleaseDC(hwnd, hdc);		optional to EndPaint
		break;
	}


	return(DefWindowProc(hwnd,iMsg,wParam,lParam));



}