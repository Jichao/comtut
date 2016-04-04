#pragma once

#include "Polyline_h.h"
#include "base/ComPtr.h"
#include <map>

struct PolylineInfo {
	int version;
	COLORREF color;
	int lineStyle;
	int pointCount;
};

class PolylineObj : public IPolyline, public IConnectionPointContainer, public IPersistFile, public IProvideClassInfo2
{
public:
	PolylineObj();
	~PolylineObj();
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

	virtual HRESULT STDMETHODCALLTYPE EnumConnectionPoints(
		/* [out] */ __RPC__deref_out_opt IEnumConnectionPoints **ppEnum);

	virtual HRESULT STDMETHODCALLTYPE FindConnectionPoint(
		/* [in] */ __RPC__in REFIID riid,
		/* [out] */ __RPC__deref_out_opt IConnectionPoint **ppCP);

	virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Color(
		/* [in] */ COLORREF value);

	virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Color(
		/* [retval][out] */ COLORREF *retValue);

	virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Points(
		/* [in] */ SAFEARRAY * values);

	virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Points(
		/* [retval][out] */ SAFEARRAY * *retValues);

	virtual HRESULT STDMETHODCALLTYPE GetClassID(
		/* [out] */ __RPC__out CLSID *pClassID);

	virtual HRESULT STDMETHODCALLTYPE IsDirty(void);

	virtual HRESULT STDMETHODCALLTYPE Load(
		/* [in] */ __RPC__in LPCOLESTR pszFileName,
		/* [in] */ DWORD dwMode);

	virtual HRESULT STDMETHODCALLTYPE Save(
		/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName,
		/* [in] */ BOOL fRemember);

	virtual HRESULT STDMETHODCALLTYPE SaveCompleted(
		/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName);

	virtual HRESULT STDMETHODCALLTYPE GetCurFile(
		/* [out] */ __RPC__deref_out_opt LPOLESTR *ppszFileName);

	virtual HRESULT STDMETHODCALLTYPE GetGUID(
		/* [in] */ DWORD dwGuidKind,
		/* [out] */ __RPC__out GUID *pGUID);

	virtual HRESULT STDMETHODCALLTYPE GetClassInfo(
		/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTI);
private:
	HRESULT ensureTypeInfo();
	HRESULT ensureClassInfo();
	void initConnectionMap();
	void fireOnResult(BSTR result);

private:
	std::vector<IConnectionPoint*> connectionPoints_;
	std::vector<POINT> points_;
	ITypeInfo* typeInfo_;
	ITypeInfo* classInfo_;
	PolylineInfo lineInfo_;
	bool dirty_;
	volatile long count_;
	std::wstring filePath_;
	IConnectionPoint* icp_;
	ComPtr<IStorage> pStorage_;
	ComPtr<IStream> pStream_;
};

