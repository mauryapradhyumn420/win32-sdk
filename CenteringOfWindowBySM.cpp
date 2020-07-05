#include<windows.h>							//Header File

LRESULT CALLBACK WndProc(HWND ,UINT ,WPARAM,LPARAM);   //Function Prototype

TCHAR szAppName[] = TEXT("CENTER MY WINDOW");     //

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)			//main() Function	
{
	WNDCLASSEX wnd;							//WNDCLASSEX Structure With 12 Member
	HWND hwnd;								//Handle to Window
	MSG msg;								//MSG Structure With 6 Member
	int iHeight, iWidth;

	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.cbSize = sizeof(wnd);
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hIcon = LoadIcon(NULL,IDI_EXCLAMATION);
	wnd.hInstance = hInstance;
	wnd.hCursor = LoadCursor(NULL,IDC_ARROW);
	wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wnd.hIconSm = LoadIcon(NULL,IDI_EXCLAMATION);
	wnd.lpfnWndProc = WndProc;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = szAppName;

	RegisterClassEx(&wnd);
	iHeight = GetSystemMetrics(SM_CYSCREEN);
	iWidth = GetSystemMetrics(SM_CXSCREEN);



	hwnd=CreateWindow(
		szAppName,
		TEXT("CENTERING WINDOW"),
		WS_OVERLAPPEDWINDOW,
		(iWidth/2)-(400/2),
		(iHeight/4), 
		400,
		400,
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

LRESULT CALLBACK WndProc(HWND hwnd ,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_DESTROY:
			PostQuitMessage(0);
	
	}

	return (DefWindowProc(hwnd,iMsg,wParam,lParam));

}
