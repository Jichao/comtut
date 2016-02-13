#include "stdafx.h"
#include "sinkobj.h"
#include "../disptest/String_h.h"
#include "../disptest/string_i.c"

SinkObj::SinkObj()
{
	count_ = 0;
	typeInfo_ = nullptr;
}

SinkObj::~SinkObj()
{
	if (typeInfo_) {
		typeInfo_->Release();
	}
}

HRESULT STDMETHODCALLTYPE SinkObj::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IDispatch) {
		*ppvObject = (IDispatch*)this;
	}
	else if (riid == IID_IUnknown) {
		*ppvObject = (IDispatch*)this;
	}
	else if (riid == DIID__IStringEvent) {
		*ppvObject = (_IStringEvent*)this;
	}
	if (*ppvObject) {
		AddRef();
		return S_OK;
	}
	else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE SinkObj::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE SinkObj::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

HRESULT STDMETHODCALLTYPE SinkObj::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE SinkObj::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
	__RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	*ppTInfo = typeInfo_;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE SinkObj::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
	__RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
	16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE SinkObj::Invoke(/* [annotation][in] */ _In_ DISPID
	dispIdMember, /* [annotation][in] */ _In_ REFIID riid, /* [annotation][in] */ _In_ LCID lcid, /* [annotation][in] */
	_In_ WORD wFlags, /* [annotation][out][in] */ _In_ DISPPARAMS *pDispParams, /* [annotation][out] */ _Out_opt_ VARIANT
	*pVarResult, /* [annotation][out] */ _Out_opt_ EXCEPINFO *pExcepInfo, /* [annotation][out] */ _Out_opt_ UINT *puArgErr)
{
	if (dispIdMember == 1) {
		OnResult(pDispParams->rgvarg[0].bstrVal);
		return S_OK;
	}
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	auto hr = typeInfo_->Invoke((IDispatch*)this, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	return hr;
}

HRESULT SinkObj::OnResult(BSTR result)
{
	printf("concat result from callback : %S\n", result);
	return S_OK;
}

HRESULT SinkObj::ensureTypeInfo()
{
	ITypeLib* typeLib;
	auto hr = LoadRegTypeLib(LIBID_StringLib, 1, 0, 0, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = typeLib->GetTypeInfoOfGuid(DIID__IStringEvent, &typeInfo_);
	if (hr != S_OK) {
		return hr;
	}
	ITypeInfo2* typeInfo2 = NULL;
	typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
	typeInfo_ = typeInfo2;
	typeLib->Release();
	return S_OK;
}
