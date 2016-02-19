#include "stdafx.h"
#include "CircleControlFactory.h"
#include "CircleAvatar.h"

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatarFactory::CreateInstance(
	/* [annotation][unique][in] */ _In_opt_ IUnknown *pUnkOuter,
	/* [annotation][in] */ _In_ REFIID riid,
	/* [annotation][iid_is][out] */ _COM_Outptr_ void **ppvObject)
{
	CircleAvatar* obj = new CircleAvatar();
	auto hr = obj->QueryInterface(riid, ppvObject);
	if (S_OK != hr) {
		delete obj;
		*ppvObject = NULL;
		return hr;
	}
	obj->AddRef();
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatarFactory::LockServer(/* [in] */ BOOL fLock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatarFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IClassFactory || riid == IID_IUnknown) {
		*ppvObject = (IClassFactory*)this;
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE CircleAvatarFactory::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE CircleAvatarFactory::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}