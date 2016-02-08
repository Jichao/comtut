#include "stdafx.h"
#include "StringObjFactory.h"
#include "StringObj.h"

/* [local] */ HRESULT STDMETHODCALLTYPE StringObjFactory::CreateInstance(
	/* [annotation][unique][in] */ _In_opt_ IUnknown *pUnkOuter,
	/* [annotation][in] */ _In_ REFIID riid,
	/* [annotation][iid_is][out] */ _COM_Outptr_ void **ppvObject)
{
	StringObj* obj = new StringObj();
	auto hr = obj->QueryInterface(riid, ppvObject);
	if (S_OK != hr) {
		delete obj;
		*ppvObject = NULL;
		return hr;
	}
	obj->AddRef();
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE StringObjFactory::LockServer(/* [in] */ BOOL fLock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE StringObjFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IClassFactory || riid == IID_IUnknown) {
		*ppvObject = (IClassFactory*)this;
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE StringObjFactory::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE StringObjFactory::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}