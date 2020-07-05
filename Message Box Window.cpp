#include<windows.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT ,WPARAM,LPARAM);

TCHAR szAppName[] = TEXT("My Window");

FILE *gfilep;
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdLine ,int iCmdShow)
{
	gfilep = fopen("source_log.txt","w+");
	if (gfilep == NULL)
		exit(0);

	HWND hwnd;
	MSG msg;
	WNDCLASSEX wnd;
	
	fprint_s(gfilep,"Member Inisalization of Class WNDCLASSEX\n");
	
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.cbWndExtra = 0;
	wnd.cbClsExtra = 0;
	wnd.lpfnWndProc = WndProc;
	wnd.hInstance = hInstance;
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = szAppName;
	wnd.hIconSm = NULL;
	wnd.cbSize = sizeof(WNDCLASSEX);

	fprint_s(gfilep, "Registeration of Class WNDCLASSEX\n");

	RegisterClassEx(&wnd);

	MessageBox(NULL,szAppName,TEXT("Register Succes"),MB_OK);

	fprint_s(gfilep, "Creating Window\n");

	hwnd = CreateWindow(
		szAppName,
		TEXT("MY WINDOWS"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
			);

	fprint_s(gfilep, "Show Window\n");

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
	switch (iMsg)
	{
	case WM_DESTROY:
		MessageBox(hwnd,szAppName,TEXT("BYE BYE WINDOW"),MB_OK);
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN :
		MessageBox(hwnd, szAppName, TEXT("Left Button is Pressed"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		MessageBox(hwnd, szAppName, TEXT("Right Button is Pressed"), MB_OK);
		break;
    
	} 

	return (DefWindowProc(hwnd,iMsg,wParam,lParam));




}