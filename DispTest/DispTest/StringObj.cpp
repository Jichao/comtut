#include "stdafx.h"
#include "StringObj.h"
#include "String_h.h"
#include "string_i.c"
#include "trace.h"
#include "ConnectionPointImpl.h"
#include "IEnumConnectionPointsImpl.h"

StringObj::StringObj()
{
	count_ = 0;
	typeInfo_ = nullptr;
	initConnectionMap();
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
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IString) {
		*ppvObject = (IString*)this;
	} else if (riid == IID_IConnectionPointContainer) {
		*ppvObject = (IConnectionPointContainer*)this;
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
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	auto hr = typeInfo_->Invoke((IDispatch*)this, dispIdMember, wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
	return hr;
}

/* [id][helpstring] */ HRESULT STDMETHODCALLTYPE StringObj::Concat(/* [in] */ BSTR str1, /* [in] */ BSTR
	str2, /* [retval][out] */ BSTR *result)
{
	auto len = SysStringLen(str1) + SysStringLen(str2) + 1;
	WCHAR* buff = new WCHAR[len];
	StringCchCopy(buff, len, str1);
	StringCchCat(buff, len, str2);
	*result = SysAllocString(buff);
	fireOnResult(*result);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE StringObj::EnumConnectionPoints(/* [out] */ __RPC__deref_out_opt IEnumConnectionPoints **ppEnum)
{
	*ppEnum = new IEnumConnectionPointsImpl(connectionPoints_);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE StringObj::FindConnectionPoint(/* [in] */ __RPC__in REFIID riid,
	/* [out] */ __RPC__deref_out_opt IConnectionPoint **ppCP)
{
	auto iter = std::find_if(connectionPoints_.begin(), connectionPoints_.end(), [&riid](IConnectionPoint* pCP) {
		IID iid;
		pCP->GetConnectionInterface(&iid);
		return InlineIsEqualGUID(riid, iid);
	});
	if (iter == connectionPoints_.end()) {
		return E_NOINTERFACE;
	} else {
		(*iter)->AddRef();
		*ppCP = *iter;
		return S_OK;
	}
}

HRESULT StringObj::ensureTypeInfo()
{
	ITypeLib* typeLib;
	auto hr = LoadRegTypeLib(LIBID_StringLib, 1, 0, 0, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = typeLib->GetTypeInfoOfGuid(IID_IString, &typeInfo_);
	if (hr != S_OK) {
		return hr;
	}
	ITypeInfo2* typeInfo2 = NULL;
	typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
	typeInfo_ = typeInfo2;
	typeLib->Release();
	return S_OK;
}

void StringObj::initConnectionMap()
{
	connectionPoints_.push_back(new ConnectionPointImpl<_IStringEvent>(DIID__IStringEvent, this));
}

void StringObj::fireOnResult(BSTR result)
{
	IConnectionPoint* cp = nullptr;
	auto hr = FindConnectionPoint(DIID__IStringEvent, &cp);
	if (SUCCEEDED(hr) && cp) {
		IEnumConnections* ec = nullptr;
		hr = cp->EnumConnections(&ec);
		if (SUCCEEDED(hr) && ec) {
			CONNECTDATA cd;
			ULONG fetched = 0;
			while (SUCCEEDED(ec->Next(1, &cd, &fetched)) && fetched == 1) {
				DISPPARAMS params = { 0 };
				VARIANT arg1;
				VariantInit(&arg1);
				arg1.vt = VT_BSTR;
				arg1.bstrVal = result;
				VARIANTARG args[] = { arg1 };
				params.cArgs = 1;
				params.cNamedArgs = 0;
				params.rgvarg = args;
				VARIANT var;
				VariantInit(&var);
				IDispatch* disp = nullptr;
				hr = cd.pUnk->QueryInterface(IID_IDispatch, (void**)&disp);
				if (SUCCEEDED(hr)) {
					disp->Invoke(1, IID_NULL, 0, INVOKE_FUNC, &params, &var, NULL, NULL);
				}
			}
		}
	}
}
