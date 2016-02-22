#include "stdafx.h"
#include "PolyObjFactory.h"
#include "PolyObj.h"

/* [local] */ HRESULT STDMETHODCALLTYPE PolylineObjFactory::CreateInstance(
	/* [annotation][unique][in] */ _In_opt_ IUnknown *pUnkOuter,
	/* [annotation][in] */ _In_ REFIID riid,
	/* [annotation][iid_is][out] */ _COM_Outptr_ void **ppvObject)
{
	LICINFO licInfo;
	GetLicInfo(&licInfo);
	if (!licInfo.fLicVerified) {
		return CLASS_E_NOTLICENSED;
	}
	PolylineObj* obj = new PolylineObj();
	auto hr = obj->QueryInterface(riid, ppvObject);
	if (S_OK != hr) {
		delete obj;
		*ppvObject = NULL;
		return hr;
	}
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE PolylineObjFactory::LockServer(/* [in] */ BOOL fLock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObjFactory::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IClassFactory || riid == IID_IUnknown) {
		*ppvObject = (IClassFactory*)this;
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE PolylineObjFactory::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE PolylineObjFactory::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

HRESULT STDMETHODCALLTYPE PolylineObjFactory::GetLicInfo(/* [out][in] */ __RPC__inout LICINFO *pLicInfo)
{
	if (!pLicInfo)
		return E_POINTER;
	pLicInfo->cbLicInfo = sizeof(LICINFO);
	pLicInfo->fLicVerified = TRUE;
	pLicInfo->fRuntimeKeyAvail = FALSE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObjFactory::RequestLicKey(
	/* [in] */ DWORD dwReserved,
	/* [out] */ __RPC__deref_out_opt BSTR *pBstrKey)
{
	return E_NOTIMPL;
}

/* [local] */ HRESULT STDMETHODCALLTYPE PolylineObjFactory::CreateInstanceLic(
	/* [in] */ IUnknown *pUnkOuter,
	/* [in] */ IUnknown *pUnkReserved,
	/* [in] */ REFIID riid,
	/* [in] */ BSTR bstrKey,
	/* [iid_is][out] */ PVOID *ppvObj)
{
	return E_NOTIMPL;
}
