#pragma once

#include "book_h.h"
#include "base/ComPtr.h"
#include "base/ComBSTR.h"
#include <map>

class Section : public ISection, public IPersistStreamInit, public IPersistStream
{
public:
	Section();
	~Section();

	//IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	//IDispatch
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
		/* [out] */ __RPC__out UINT *pctinfo);

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo);

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
		/* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [annotation][in] */
		_In_  DISPID dispIdMember,
		/* [annotation][in] */
		_In_  REFIID riid,
		/* [annotation][in] */
		_In_  LCID lcid,
		/* [annotation][in] */
		_In_  WORD wFlags,
		/* [annotation][out][in] */
		_In_  DISPPARAMS *pDispParams,
		/* [annotation][out] */
		_Out_opt_  VARIANT *pVarResult,
		/* [annotation][out] */
		_Out_opt_  EXCEPINFO *pExcepInfo,
		/* [annotation][out] */
		_Out_opt_  UINT *puArgErr);

	//IPersistStream
	virtual HRESULT STDMETHODCALLTYPE GetClassID(
		/* [out] */ __RPC__out CLSID *pClassID);

	virtual HRESULT STDMETHODCALLTYPE IsDirty(void) override;

	virtual HRESULT STDMETHODCALLTYPE Load(
		/* [unique][in] */ __RPC__in_opt IStream *pStm) override;

	virtual HRESULT STDMETHODCALLTYPE Save(
		/* [unique][in] */ __RPC__in_opt IStream *pStm,
		/* [in] */ BOOL fClearDirty) override;

	virtual HRESULT STDMETHODCALLTYPE GetSizeMax(
		/* [out] */ __RPC__out ULARGE_INTEGER *pcbSize) override;

	virtual HRESULT STDMETHODCALLTYPE InitNew(void) override;

	//ISection
	HRESULT STDMETHODCALLTYPE get_name(BSTR* value) override;
	HRESULT STDMETHODCALLTYPE put_name(BSTR value) override;
	HRESULT STDMETHODCALLTYPE get_content(BSTR* value) override;
	HRESULT STDMETHODCALLTYPE put_content(BSTR value) override;

private:
	HRESULT ensureTypeInfo();

private:
	ITypeInfo* typeInfo_;
	bool dirty_;
	long volatile count_;
	ComPtr<IStream> pStream_;
	ComBSTR sectionName_;
	ComBSTR content_;
};
