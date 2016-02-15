#pragma once

#include "CircleControl_h.h"

class CircleControl : public ICircleControl, public IOleInPlaceObject, public IOleInPlaceActiveObject, public IViewObject2
{
public:
	CircleControl();
	~CircleControl();
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

	virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Radius(
		/* [retval][out] */ float *ReturnVal);

	virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Radius(
		/* [in] */ float Value);

	virtual HRESULT STDMETHODCALLTYPE InPlaceDeactivate(void);

	virtual HRESULT STDMETHODCALLTYPE UIDeactivate(void);

	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE SetObjectRects(
		/* [in] */ __RPC__in LPCRECT lprcPosRect,
		/* [in] */ __RPC__in LPCRECT lprcClipRect);

	virtual HRESULT STDMETHODCALLTYPE ReactivateAndUndo(void);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE TranslateAccelerator(
		/* [annotation][in] */
		_In_opt_  LPMSG lpmsg);

	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE OnFrameWindowActivate(
		/* [in] */ BOOL fActivate);

	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE OnDocWindowActivate(
		/* [in] */ BOOL fActivate);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE ResizeBorder(
		/* [annotation][in] */
		_In_  LPCRECT prcBorder,
		/* [annotation][unique][in] */
		_In_  IOleInPlaceUIWindow *pUIWindow,
		/* [annotation][in] */
		_In_  BOOL fFrameWindow);

	virtual HRESULT STDMETHODCALLTYPE EnableModeless(
		/* [in] */ BOOL fEnable);
	virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow(
		/* [out] */ __RPC__deref_out_opt HWND *phwnd);

	virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(
		/* [in] */ BOOL fEnterMode);
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
		_In_opt_  BOOL(STDMETHODCALLTYPE *pfnContinue)(
		ULONG_PTR dwContinue),
		/* [annotation][in] */
		_In_  ULONG_PTR dwContinue);

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
		_Outptr_  LOGPALETTE **ppColorSet);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Freeze(
		/* [annotation][in] */
		_In_  DWORD dwDrawAspect,
		/* [annotation][in] */
		_In_  LONG lindex,
		/* [annotation][unique][in] */
		_Null_  void *pvAspect,
		/* [annotation][out] */
		_Out_  DWORD *pdwFreeze);

	virtual HRESULT STDMETHODCALLTYPE Unfreeze(
		/* [in] */ DWORD dwFreeze);

	virtual HRESULT STDMETHODCALLTYPE SetAdvise(
		/* [in] */ DWORD aspects,
		/* [in] */ DWORD advf,
		/* [unique][in] */ __RPC__in_opt IAdviseSink *pAdvSink);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetAdvise(
		/* [annotation][unique][out] */
		_Out_opt_  DWORD *pAspects,
		/* [annotation][unique][out] */
		_Out_opt_  DWORD *pAdvf,
		/* [annotation][out] */
		_Outptr_  IAdviseSink **ppAdvSink);

	virtual HRESULT STDMETHODCALLTYPE GetExtent(
		/* [in] */ DWORD dwDrawAspect,
		/* [in] */ LONG lindex,
		/* [unique][in] */ __RPC__in_opt DVTARGETDEVICE *ptd,
		/* [out] */ __RPC__out LPSIZEL lpsizel);

private:
	HRESULT ensureTypeInfo();

private:
	ITypeInfo* typeInfo_;
	volatile long count_;
	float radius_;
	HWND hwnd_;
};

