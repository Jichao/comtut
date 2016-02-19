// CircleAvatar.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CircleAvatar.h"
#include "CircleAvatar_h.h"
#include "CircleAvatar_i.c"
#include "WindowImpl.h"
#include "trace.h"

extern HMODULE g_hMod;
CircleAvatar::CircleAvatar()
{
    count_ = 0;
    typeInfo_ = nullptr;
	hwnd_ = NULL;
	filePath_ = nullptr;
}

CircleAvatar::~CircleAvatar()
{
    if (typeInfo_) {
        typeInfo_->Release();
    }
}

HRESULT STDMETHODCALLTYPE CircleAvatar::QueryInterface(REFIID riid, void **ppvObject)
{
	MessageBox(NULL, NULL, NULL, NULL);
	WCHAR guid[MAX_PATH];
	StringFromGUID2(riid, guid, MAX_PATH);
	TRACE("queryinterface %s\n", guid);
    *ppvObject = NULL;
    if (riid == IID_IDispatch) {
        *ppvObject = (IDispatch*)this;
    } else if (riid == IID_IUnknown) {
        *ppvObject = (IDispatch*)this;
    } else if (riid == IID_ICircleAvatar) {
        *ppvObject = (ICircleAvatar*)this;
    } else if (riid == IID_IOleInPlaceObject) {
        *ppvObject = (IOleInPlaceObject*)this;
    } else if (riid == IID_IOleInPlaceActiveObject) {
        *ppvObject = (IOleInPlaceActiveObject*)this;
    } else if (riid == IID_IViewObject2) {
        *ppvObject = (IViewObject2*)this;
    }
    if (*ppvObject) {
        AddRef();
        return S_OK;
    } else {
        return E_NOINTERFACE;
    }
}

ULONG STDMETHODCALLTYPE CircleAvatar::AddRef(void)
{
    return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE CircleAvatar::Release(void)
{
    LONG count = InterlockedDecrement(&count_);
    if (count == 0) {
        delete this;
    }
    return count;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
    *pctinfo = 1;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
        __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
    if (FAILED(ensureTypeInfo())) {
        return E_FAIL;
    }
    *ppTInfo = typeInfo_;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
        __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
                16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
    if (FAILED(ensureTypeInfo())) {
        return E_FAIL;
    }
    return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatar::Invoke(/* [annotation][in] */ _In_ DISPID
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

/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE CircleAvatar::get_Radius(/* [retval][out] */ float *ReturnVal)
{
    *ReturnVal = radius_;
    return S_OK;
}

/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE CircleAvatar::put_Radius(/* [in] */ float Value)
{
    radius_ = Value;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::InPlaceDeactivate(void)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::UIDeactivate(void)
{
    return S_OK;

}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE CircleAvatar::SetObjectRects(/* [in] */ __RPC__in LPCRECT
        lprcPosRect, /* [in] */ __RPC__in LPCRECT lprcClipRect)
{

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::ReactivateAndUndo(void)
{

    return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatar::TranslateAccelerator(/* [annotation][in] */ _In_opt_ LPMSG lpmsg)
{
    TranslateAccelerator(lpmsg);
    return S_OK;
}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE CircleAvatar::OnFrameWindowActivate(/* [in] */ BOOL fActivate)
{

    return S_OK;
}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE CircleAvatar::OnDocWindowActivate(/* [in] */ BOOL fActivate)
{

    return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatar::ResizeBorder(/* [annotation][in] */ _In_ LPCRECT prcBorder,
        /* [annotation][unique][in] */ _In_ IOleInPlaceUIWindow *pUIWindow,
        /* [annotation][in] */ _In_ BOOL fFrameWindow)
{

    return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::EnableModeless(/* [in] */ BOOL fEnable)
{
    return S_OK;
}

/* [input_sync] */ HRESULT STDMETHODCALLTYPE CircleAvatar::GetWindow(/* [out] */ __RPC__deref_out_opt HWND *phwnd)
{
	if (!hwnd_) {
		WindowImpl::registerClass(g_hMod);
		hwnd_ = WindowImpl::GetWindow();
	}
	*phwnd = hwnd_;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::ContextSensitiveHelp(/* [in] */ BOOL fEnterMode)
{
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatar::Draw(
    /* [annotation][in] */ _In_ DWORD dwDrawAspect,
    /* [annotation][in] */ _In_ LONG lindex,
    /* [annotation][unique][in] */ _Null_ void *pvAspect,
    /* [annotation][unique][in] */ _In_opt_ DVTARGETDEVICE *ptd,
    /* [annotation][in] */ _In_opt_ HDC hdcTargetDev,
    /* [annotation][in] */ _In_ HDC hdcDraw,
    /* [annotation][in] */ _In_opt_ LPCRECTL lprcBounds,
    /* [annotation][unique][in] */ _In_opt_ LPCRECTL lprcWBounds,
    /* [annotation][in] */ _In_opt_ BOOL(STDMETHODCALLTYPE *pfnContinue)(ULONG_PTR dwContinue),
    /* [annotation][in] */ _In_ ULONG_PTR dwContinue)
{
	using namespace Gdiplus;
	Graphics g(hdcDraw);
	SolidBrush redBrush(Color::Red);
	Rect rc(
		lprcBounds->left, lprcBounds->right,
		lprcBounds->right - lprcBounds->left,
		lprcBounds->bottom - lprcBounds->top);
	g.FillEllipse(&redBrush, rc);
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatar::GetColorSet(/* [annotation][in] */ _In_ DWORD dwDrawAspect,
        /* [annotation][in] */ _In_ LONG lindex,
        /* [annotation][unique][in] */ _Null_ void *pvAspect,
        /* [annotation][unique][in] */ _In_opt_ DVTARGETDEVICE *ptd,
        /* [annotation][in] */ _In_opt_ HDC hicTargetDev,
        /* [annotation][out] */ _Outptr_ LOGPALETTE **ppColorSet)
{
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatar::Freeze(/* [annotation][in] */ _In_ DWORD
        dwDrawAspect, /* [annotation][in] */ _In_ LONG lindex, /* [annotation][unique][in] */ _Null_ void
        *pvAspect, /* [annotation][out] */ _Out_ DWORD *pdwFreeze)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::Unfreeze(/* [in] */ DWORD dwFreeze)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::SetAdvise(/* [in] */ DWORD aspects, /* [in] */ DWORD advf, /* [unique][in] */
        __RPC__in_opt IAdviseSink *pAdvSink)
{
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE CircleAvatar::GetAdvise(/* [annotation][unique][out] */ _Out_opt_ DWORD
        *pAspects, /* [annotation][unique][out] */ _Out_opt_ DWORD *pAdvf, /* [annotation][out] */ _Outptr_ IAdviseSink
        **ppAdvSink)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CircleAvatar::GetExtent(/* [in] */ DWORD dwDrawAspect, /* [in] */ LONG
        lindex, /* [unique][in] */ __RPC__in_opt DVTARGETDEVICE *ptd, /* [out] */ __RPC__out LPSIZEL lpsizel)
{
	return S_OK;
}

HRESULT CircleAvatar::ensureTypeInfo()
{
    ITypeLib* typeLib;
    auto hr = LoadRegTypeLib(LIBID_GraphicsLibrary, 1, 0, 0, &typeLib);
    if (hr != S_OK) {
        return hr;
    }
    hr = typeLib->GetTypeInfoOfGuid(IID_ICircleAvatar, &typeInfo_);
    if (hr != S_OK) {
        return hr;
    }
    ITypeInfo2* typeInfo2 = NULL;
    typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
    typeInfo_ = typeInfo2;
    typeLib->Release();
    return S_OK;
}

/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE CircleAvatar::get_ImageFilePath(/* [retval][out] */ BSTR *ReturnVal)
{
	*ReturnVal = SysAllocString(filePath_);
	return S_OK;
}

/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE CircleAvatar::put_ImageFilePath(/* [in] */ BSTR Value)
{
	SysFreeString(filePath_);
	filePath_ = SysAllocString(Value);
	return S_OK;
}
