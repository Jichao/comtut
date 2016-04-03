#pragma once

#include "viewserver_h.h"
#include "base/ComPtr.h"
#include "base/ComBSTR.h"
#include <map>

class ViewServer : public IViewServer, public IViewObject2
{
public:
	ViewServer();
	~ViewServer();

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

	//IViewServer
	HRESULT STDMETHODCALLTYPE get_color(COLORREF* retValue) override;
	HRESULT	STDMETHODCALLTYPE put_color(COLORREF value) override;

	        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [annotation][in] */ 
            _In_  DWORD dwDrawAspect,
            /* [annotation][in] */ 
            _In_  LONG lindex,
            /* [annotation][unique][in] */ 
            _Null_  void *pvAspect,
            /* [annotation][unique][in] */ 
            _In_opt_  DVTARGETDEVICE *ptd,
            /* [annotation][in] */ 
            _In_opt_  HDC hdcTargetDev,
            /* [annotation][in] */ 
            _In_  HDC hdcDraw,
            /* [annotation][in] */ 
            _In_opt_  LPCRECTL lprcBounds,
            /* [annotation][unique][in] */ 
            _In_opt_  LPCRECTL lprcWBounds,
            /* [annotation][in] */ 
            _In_opt_  BOOL ( STDMETHODCALLTYPE *pfnContinue )( 
                ULONG_PTR dwContinue),
            /* [annotation][in] */ 
            _In_  ULONG_PTR dwContinue) override;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetColorSet( 
            /* [annotation][in] */ 
            _In_  DWORD dwDrawAspect,
            /* [annotation][in] */ 
            _In_  LONG lindex,
            /* [annotation][unique][in] */ 
            _Null_  void *pvAspect,
            /* [annotation][unique][in] */ 
            _In_opt_  DVTARGETDEVICE *ptd,
            /* [annotation][in] */ 
            _In_opt_  HDC hicTargetDev,
            /* [annotation][out] */ 
            _Outptr_  LOGPALETTE **ppColorSet) override;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE Freeze( 
            /* [annotation][in] */ 
            _In_  DWORD dwDrawAspect,
            /* [annotation][in] */ 
            _In_  LONG lindex,
            /* [annotation][unique][in] */ 
            _Null_  void *pvAspect,
            /* [annotation][out] */ 
            _Out_  DWORD *pdwFreeze) override;
        
        virtual HRESULT STDMETHODCALLTYPE Unfreeze( 
            /* [in] */ DWORD dwFreeze) override;
        
        virtual HRESULT STDMETHODCALLTYPE SetAdvise( 
            /* [in] */ DWORD aspects,
            /* [in] */ DWORD advf,
            /* [unique][in] */ __RPC__in_opt IAdviseSink *pAdvSink) override;
        
        virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetAdvise( 
            /* [annotation][unique][out] */ 
            _Out_opt_  DWORD *pAspects,
            /* [annotation][unique][out] */ 
            _Out_opt_  DWORD *pAdvf,
            /* [annotation][out] */ 
            _Outptr_  IAdviseSink **ppAdvSink) override;

		virtual HRESULT STDMETHODCALLTYPE GetExtent(
			/* [in] */ DWORD dwDrawAspect,
			/* [in] */ LONG lindex,
			/* [unique][in] */ __RPC__in_opt DVTARGETDEVICE *ptd,
			/* [out] */ __RPC__out LPSIZEL lpsizel) override;
 

private:
	HRESULT ensureTypeInfo();

private:
	ITypeInfo* typeInfo_;
	bool dirty_;
	volatile long count_;
	COLORREF color_;
};
