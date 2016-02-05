#include "stdafx.h"
#include "StringObj.h"
#include "String_h.h"
#include "string_i.c"
#include "trace.h"
StringObj::StringObj()
{
    count_ = 0;
    typeInfo_ = nullptr;
}


StringObj::~StringObj()
{
    if (typeInfo_) {
        typeInfo_->Release();
    }
}

HRESULT STDMETHODCALLTYPE StringObj::QueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;
    if (riid == IID_IDispatch) {
        *ppvObject = (IDispatch*)this;
    } else if (riid == IID_IUnknown) {
        *ppvObject = (IUnknown*)this;
    } else if (riid == IID_IString) {
        *ppvObject = (IString*)this;
    }
    if (*ppvObject) {
		AddRef();
        return S_OK;
    } else {
        return E_NOINTERFACE;
    }
}

ULONG STDMETHODCALLTYPE StringObj::AddRef(void)
{
    return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE StringObj::Release(void)
{
    LONG count = InterlockedDecrement(&count_);
    if (count == 0) {
        delete this;
    }
    return count;
}

HRESULT STDMETHODCALLTYPE StringObj::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
    *pctinfo = 1;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE StringObj::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
        __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	TRACE("GetTypeInfo\n");
    if (FAILED(ensureTypeInfo())) {
        return E_FAIL;
    }
    *ppTInfo = typeInfo_;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE StringObj::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
        __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
                16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
	TRACE("GetIDsOfNames\n");
    if (FAILED(ensureTypeInfo())) {
        return E_FAIL;
    }
    return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE StringObj::Invoke(/* [annotation][in] */ _In_ DISPID
        dispIdMember, /* [annotation][in] */ _In_ REFIID riid, /* [annotation][in] */ _In_ LCID lcid, /* [annotation][in] */
        _In_ WORD wFlags, /* [annotation][out][in] */ _In_ DISPPARAMS *pDispParams, /* [annotation][out] */ _Out_opt_ VARIANT
        *pVarResult, /* [annotation][out] */ _Out_opt_ EXCEPINFO *pExcepInfo, /* [annotation][out] */ _Out_opt_ UINT *puArgErr)
{
	//if (dispIdMember == 1 && wFlags == DISPATCH_METHOD) {
	//	BSTR keke = nullptr;
	//	auto hr =  Concat(pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal, &keke);
	//	TRACE("result type = %d\n", pVarResult->vt);
	//	pVarResult->vt = VT_BSTR;
	//	pVarResult->bstrVal = keke;
	//	return hr;
	//}
	TRACE("Invoke\n");
    if (FAILED(ensureTypeInfo())) {
        return E_FAIL;
    }
	pVarResult->vt = VT_BSTR | VT_BYREF;
	TRACE("dispinvoke %d typeinfo %x\n", dispIdMember, typeInfo_);
    auto hr =  DispInvoke(this, typeInfo_, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	TRACE("dispinvoke %x\n", hr);
	return hr;
}

/* [id][helpstring] */ HRESULT STDMETHODCALLTYPE StringObj::Concat(/* [in] */ BSTR str1, /* [in] */ BSTR
        str2, /* [retval][out] */ BSTR *result)
{
	auto len = SysStringLen(str1) + SysStringLen(str2) + 1;
	WCHAR* buff = new WCHAR[len];
	StringCchCopy(buff, len, str1);
	StringCchCat(buff, len, str2);
	TRACE(L"Concat buff %s\n", buff);
	*result = SysAllocString(buff);
	return S_OK;
}

HRESULT StringObj::ensureTypeInfo()
{
	TRACE("ensureTypeInfo\n");
    ITypeLib* typeLib;
    auto hr = LoadRegTypeLib(LIBID_StringLib, 1, 0, 0, &typeLib);
    if (hr != S_OK) {
		TRACE("LoadRegTypeLib failed\n");
        return hr;
    }
		TRACE("LoadRegTypeLib suceeded\n");
    hr = typeLib->GetTypeInfoOfGuid(CLSID_StringObj, &typeInfo_);
    if (hr != S_OK) {
		TRACE("GetTypeInfoOfGuid failed\n");
        return hr;
    }
	TRACE("GetTypeInfoOfGuid suceeded\n");
    typeInfo_->AddRef();
    //typeLib->Release();
    return S_OK;
}
