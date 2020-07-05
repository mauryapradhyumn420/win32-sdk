#include<windows.h>
#include<stdio.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szAppName[] = TEXT("WINDOW LOG");

FILE *gpFile = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	RECT rc;
	HWND hwnd;
	WNDCLASSEX wnd;
	MSG msg;
	long int  iHeight, iWidth;
	BOOL bSpi;
	fopen_s(&gpFile, "WindowLog.txt", "w");
	if (gpFile==NULL)
	{
		MessageBox(NULL,TEXT("ERROR IN FILE OPENING"), szAppName,MB_OKCANCEL);
		exit(0);
	}

	fprintf(gpFile,"WNDCLASSEX DECLARATION\n");

	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.cbSize = sizeof(wnd);
	wnd.cbWndExtra = 0;
	wnd.cbClsExtra = 0;
	wnd.lpfnWndProc = WndProc;
	wnd.lpszClassName = szAppName;
	wnd.lpszMenuName = NULL;
	wnd.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wnd.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wnd.hCursor = LoadCursor(NULL,IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hInstance = hInstance;

	fprintf_s(gpFile, "WNDCLASSEX REGISTERATION\n");

	RegisterClassEx(&wnd);

	fprintf_s(gpFile, "CREATE WINDOW\n");

	bSpi=SystemParametersInfo(SPI_GETWORKAREA,0,&rc,0);
	

	iHeight = rc.bottom;
	iWidth = rc.right;
	if(bSpi)
	fprintf_s(gpFile, "top=%ld bottom=%ld left=%ld right=%ld \n", rc.top, rc.bottom, rc.left, rc.right);

	hwnd=CreateWindow(szAppName,
		TEXT("LOG Window"),
		WS_OVERLAPPEDWINDOW,
		(iWidth/2)-300,
		(iHeight/ 2) - 300,
		600,
		600,
		NULL,
		NULL,
		hInstance,
		NULL);

	fprintf_s(gpFile, "SHOW AND UPDATE WINDOW\n");

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	fprintf_s(gpFile, "RETURN WAPRAM\n");
	fclose(gpFile);
	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)	
	{
	case WM_DESTROY:
		fprintf_s(gpFile, "WM_DESTROY");
		PostQuitMessage(0);

	}
	//fprintf_s(gpFile, "DEFWINDOWPROC \n");
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));

	
}