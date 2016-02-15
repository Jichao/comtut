#include "stdafx.h"
#include "CircleControlFactory.h"
#include "CircleControl.h"

/* [local] */ HRESULT STDMETHODCALLTYPE CircleControlFactory::CreateInstance(
	/* [annotation][unique][in] */ _In_opt_ IUnknown *pUnkOuter,
	/* [annotation][in] */ _In_ REFIID riid,
	/* [annotation][iid_is][out] */ _COM_Outptr_ void **ppvObject)
{
	CircleControl* obj = new CircleControl();
	auto hr = obj->QueryInterface(riid, ppvObject);
	if (S_OK != hr) {
		delete obj;
		*ppvObject = NULL;
		return hr;
	}
	obj->AddRef();
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleControlFactory::LockServer(/* [in] */ BOOL fLock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleControlFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IClassFactory || riid == IID_IUnknown) {
		*ppvObject = (IClassFactory*)this;
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE CircleControlFactory::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE CircleControlFactory::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}