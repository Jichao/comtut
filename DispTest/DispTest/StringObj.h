#pragma once

#include "String_h.h"
#include <map>

class StringObj : public IString, public IConnectionPointContainer
{
public:
	StringObj();
	~StringObj();
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

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

	virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE Concat(
		/* [in] */ BSTR str1,
		/* [in] */ BSTR str2,
		/* [retval][out] */ BSTR *result);

	virtual HRESULT STDMETHODCALLTYPE EnumConnectionPoints(
		/* [out] */ __RPC__deref_out_opt IEnumConnectionPoints **ppEnum);

	virtual HRESULT STDMETHODCALLTYPE FindConnectionPoint(
		/* [in] */ __RPC__in REFIID riid,
		/* [out] */ __RPC__deref_out_opt IConnectionPoint **ppCP);


private:
	HRESULT ensureTypeInfo();
	void initConnectionMap();
	void fireOnResult(BSTR result);

private:
	std::vector<IConnectionPoint*> connectionPoints_;
	ITypeInfo* typeInfo_;
	volatile long count_;
	IConnectionPoint* icp_;
};

