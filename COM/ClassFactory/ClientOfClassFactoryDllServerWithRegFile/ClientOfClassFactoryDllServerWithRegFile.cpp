#include<windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

LRESULT CALLBACK WndProc(HWND ,UINT,WPARAM,LPARAM);

TCHAR szAppName[] = TEXT("Client Com");

ISum * pISum=NULL;
ISubtract *pISubtract=NULL;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	WNDCLASSEX wnd;
	MSG msg;
	HWND hwnd;
	HRESULT hr;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL,TEXT("COM Library can't Initialize \n Now Program Will Exit"),TEXT("COM Initialize failed "),MB_OK);
		exit(0);
	}

	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.cbSize = sizeof(wnd);
	wnd.cbWndExtra = 0;
	wnd.cbClsExtra = 0;
	wnd.lpfnWndProc = WndProc;
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hIcon = LoadIcon(NULL,IDI_ASTERISK);
	wnd.hCursor = LoadCursor(NULL,IDC_ARROW);
	wnd.hInstance = hInstance;
	wnd.hIconSm = NULL;
	wnd.lpszClassName = szAppName;
	wnd.lpszMenuName = NULL;

	RegisterClassEx(&wnd);

	hwnd = CreateWindow(szAppName,TEXT("COM CLASSFACTORY"),WS_OVERLAPPEDWINDOW,400,400,400,400,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd,iCmdShow);
	
	UpdateWindow(hwnd);

	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CoUninitialize();
	return ((int)msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	void SafeInterfaceRelease(void);
	HRESULT hr;
	int num1 = 25, num2 = 50, isum;
	TCHAR str[255];
	
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_ISum,
			(void * *)&pISum);

		if (FAILED(hr))
		{
			MessageBox(hwnd,TEXT("ISum Interface can not be Obtained"),TEXT("Error"),MB_OK);
			DestroyWindow(hwnd);
		}

		pISum->SumOfTwoInteger(num1,num2,&isum);
		wsprintf(str,TEXT("Addition of %d & %d is %d:"),num1,num2,isum);
		MessageBox(hwnd,str,TEXT("Answer of Addition"),MB_OK);

		hr=pISum->QueryInterface(IID_ISubtract,(void **) &pISubtract);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface can not be Obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISum->Release();
		pISum = NULL;

		pISubtract->SubtractionOfTwoInteger(num2,num1,&isum);
		pISubtract->Release();
		pISubtract = NULL;

		wsprintf(str, TEXT("Subtraction of %d & %d is %d:"), num2, num1, isum);
		MessageBox(hwnd, str, TEXT("Answer of Subtraction"), MB_OK);
		
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

void SafeInterfaceRelease(void)
{
	if (pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}

}


