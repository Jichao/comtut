#include "stdafx.h"
#include "MathFactory.h"
#include "Math.h"
#include "IMath.h"

/* [local] */ HRESULT STDMETHODCALLTYPE MathFactory::CreateInstance(
	/* [annotation][unique][in] */ _In_opt_ IUnknown *pUnkOuter,
	/* [annotation][in] */ _In_ REFIID riid,
	/* [annotation][iid_is][out] */ _COM_Outptr_ void **ppvObject)
{
	Math* obj = new Math();
	auto hr = obj->QueryInterface(riid, ppvObject);
	if (S_OK != hr) {
		delete obj;
		*ppvObject = NULL;
		return hr;
	}
	obj->AddRef();
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE MathFactory::LockServer(/* [in] */ BOOL fLock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE MathFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IClassFactory || riid == IID_IUnknown) {
		*ppvObject = (IClassFactory*)this;
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE MathFactory::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE MathFactory::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}