#include "stdafx.h"
#include <initguid.h>
#include "base/trace.h"
#include "base/ConnectionPointImpl.h"
#include "base/IEnumConnectionPointsImpl.h"
#include "base/ComPtr.h"
#include "book_h.h"
#include "book_i.c"
#include "section.h"

static const WCHAR kStreamName[] = L"CONTENTS";

namespace {
	bool FileExists(LPCWSTR szPath)
	{
		DWORD dwAttrib = GetFileAttributes(szPath);

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
}


Section::Section()
{
	typeInfo_ = nullptr;
}

Section::~Section()
{
	if (typeInfo_) {
		typeInfo_->Release();
	}

}

HRESULT STDMETHODCALLTYPE Section::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IDispatch) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IUnknown) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_ISection) {
		*ppvObject = (ISection*)this;
	} else if (riid == IID_IPersistStreamInit) {
		*ppvObject = (IPersistStreamInit*)this;
	} else if (riid == IID_IPersistStream) {
		*ppvObject = (IPersistStream*)this;
	}
	if (*ppvObject) {
		AddRef();
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE Section::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE Section::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

HRESULT STDMETHODCALLTYPE Section::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Section::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
	__RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	*ppTInfo = typeInfo_;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Section::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
	__RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
	16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE Section::Invoke(/* [annotation][in] */ _In_ DISPID
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

HRESULT STDMETHODCALLTYPE Section::GetClassID(/* [out] */ __RPC__out CLSID *pClassID)
{
	*pClassID = CLSID_Section;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Section::IsDirty(void)
{
	return dirty_ ? S_OK : S_FALSE;
}

HRESULT STDMETHODCALLTYPE Section::Load(/* [unique][in] */ __RPC__in_opt IStream *pStm)
{
	auto hr = sectionName_.readFromStream(pStm);
	if (FAILED(hr))
		return hr;
	hr = content_.readFromStream(pStm);
	if (FAILED(hr))
		return hr;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Section::Save(/* [unique][in] */ __RPC__in_opt IStream *pStm, /* [in] */ BOOL fClearDirty)
{
	auto hr = sectionName_.writeToStream(pStm);
	if (FAILED(hr))
		return hr;
	hr = content_.writeToStream(pStm);
	if (FAILED(hr))
		return hr;
	if (fClearDirty) {
		dirty_ = false;
	}
	pStream_ = NULL;
	return hr;
}

HRESULT STDMETHODCALLTYPE Section::GetSizeMax(/* [out] */ __RPC__out ULARGE_INTEGER *pcbSize)
{
	pcbSize->QuadPart =  (sectionName_.Length() + 1 + content_.Length() + 1) * 2;
	return S_OK;
}



HRESULT Section::ensureTypeInfo()
{
	ITypeLib* typeLib;
	auto hr = LoadRegTypeLib(LIBID_BookLibrary, 1, 0, 0, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = typeLib->GetTypeInfoOfGuid(IID_ISection, &typeInfo_);
	if (hr != S_OK) {
		return hr;
	}
	ITypeInfo2* typeInfo2 = NULL;
	typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
	typeInfo_ = typeInfo2;
	typeLib->Release();
	return S_OK;
}

HRESULT Section::get_name(BSTR* value)
{
	*value = sectionName_.Clone();
	return S_OK;
}

HRESULT Section::put_name(BSTR value)
{
	sectionName_ = value;
	return S_OK;
}

HRESULT Section::get_content(BSTR* value)
{
	*value = content_.Clone();
	return S_OK;
}

HRESULT Section::put_content(BSTR value)
{
	content_ = value;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Section::InitNew(void)
{
	return S_OK;
}

