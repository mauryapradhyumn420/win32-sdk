#include<windows.h>
#include"ClassFactoryDllServerWithRegFile.h"


long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

class CSumSubtract : public ISum, ISubtract
{
private:
	long m_cRef;
public:

	CSumSubtract();
	~CSumSubtract();

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG  __stdcall AddRef(void);
	ULONG  __stdcall Release (void);
	
	HRESULT __stdcall SumOfTwoInteger(int ,int,int *);
	HRESULT __stdcall SubtractionOfTwoInteger(int,int,int *);

};

class CSumSubtractClassFactory : public IClassFactory
{
private:
	long m_cRef;
public:

	CSumSubtractClassFactory();
	~CSumSubtractClassFactory();

	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG  __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall LockServer(BOOL);
	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void ** );

};


BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;

	}
	return (TRUE);
}

CSumSubtract :: CSumSubtract(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);

}

CSumSubtract::~CSumSubtract(void)
{
	  InterlockedDecrement(&glNumberOfActiveComponents);

}

HRESULT CSumSubtract :: QueryInterface(REFIID riid,void ** ppv) 
{
	if (riid == IID_IUnknown)
		*ppv = static_cast <ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast <ISubtract *>(this);
	else
	{
		*ppv = NULL;
		return (E_NOINTERFACE);
	}

	reinterpret_cast <IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtract ::AddRef(void)
{
 
	InterlockedIncrement(&m_cRef);
	return (m_cRef);
}

ULONG CSumSubtract ::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}


HRESULT CSumSubtract :: SumOfTwoInteger(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}

HRESULT CSumSubtract :: SubtractionOfTwoInteger(int num1, int num2, int *pSub)
{
	*pSub = num1 - num2;
	return(S_OK);
}

CSumSubtractClassFactory::CSumSubtractClassFactory()
{
	m_cRef = 1;
}

CSumSubtractClassFactory::~CSumSubtractClassFactory()
{
	//Code

}

HRESULT CSumSubtractClassFactory :: QueryInterface(REFIID refiid, void ** ppv)
{
	if (refiid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (refiid == IID_IClassFactory)
		*ppv = static_cast <IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast <IUnknown *> (*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtractClassFactory :: AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory :: Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete (this);
		return(0);
	}
	return(S_OK);
}

HRESULT CSumSubtractClassFactory :: CreateInstance(IUnknown *pUnkOuter, REFIID refiid, void **ppv)
{

	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter!=NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}

	pCSumSubtract = new (CSumSubtract);
	if (pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtract->QueryInterface(refiid,ppv);
	pCSumSubtract->Release();
	return(hr);
}

HRESULT CSumSubtractClassFactory :: LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedDecrement(&glNumberOfServerLocks);
	else
		InterlockedIncrement(&glNumberOfServerLocks);

	return(S_OK);
}

HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID refiid,void **ppv)
{
	CSumSubtractClassFactory *pCSumSubtractClassFactory=NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return (CLASS_E_CLASSNOTAVAILABLE);

	pCSumSubtractClassFactory = new CSumSubtractClassFactory;

	if (pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(refiid,ppv);
	pCSumSubtractClassFactory->Release();
	return(hr);
}

HRESULT __stdcall DllCanUnloadNow()
{

	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);

}



