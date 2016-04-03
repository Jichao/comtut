#include "stdafx.h"
#include "base/trace.h"
#include "base/ConnectionPointImpl.h"
#include "base/IEnumConnectionPointsImpl.h"
#include "base/ComPtr.h"
#include "base/ComQIPtr.h"
#include "base/StringUtils.h"
#include "base/GdiplusStarter.h"
#include "viewserver_h.h"
#include "viewserver.h"
#include <initguid.h>
#include "viewserver_i.c"
#pragma comment(lib, "gdiplus.lib")

ViewServer::ViewServer()
{
    count_ = 0;
    typeInfo_ = nullptr;
    color_ = RGB(0xff, 0x00, 0x00);
}

ViewServer::~ViewServer()
{
    if (typeInfo_) {
        typeInfo_->Release();
    }

}

HRESULT STDMETHODCALLTYPE ViewServer::QueryInterface(REFIID riid, void **ppvObject)
{
    *ppvObject = NULL;
    if (riid == IID_IDispatch) {
        *ppvObject = (IDispatch*)this;
    } else if (riid == IID_IUnknown) {
        *ppvObject = (IDispatch*)this;
    } else if (riid == IID_IViewServer) {
        *ppvObject = (IViewServer*)this;
    } else if (riid == IID_IViewObject || riid == IID_IViewObject2) {
        *ppvObject = (IViewObject2*)this;
    }     
	if (*ppvObject) {
        AddRef();
        return S_OK;
    } else {
        return E_NOINTERFACE;
    }
}

ULONG STDMETHODCALLTYPE ViewServer::AddRef(void)
{
    return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE ViewServer::Release(void)
{
    LONG count = InterlockedDecrement(&count_);
    if (count == 0) {
        delete this;
    }
    return count;
}

HRESULT STDMETHODCALLTYPE ViewServer::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
    *pctinfo = 1;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ViewServer::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
        __RPC__deref_out_opt ITypeInfo **ppTInfo)
{
    if (FAILED(ensureTypeInfo())) {
        return E_FAIL;
    }
    *ppTInfo = typeInfo_;
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ViewServer::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
        __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
                16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
    if (FAILED(ensureTypeInfo())) {
        return E_FAIL;
    }
    return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE ViewServer::Invoke(/* [annotation][in] */ _In_ DISPID
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
HRESULT ViewServer::ensureTypeInfo()
{
    ITypeLib* typeLib;
    auto hr = LoadRegTypeLib(LIBID_ViewServerLibrary, 1, 0, 0, &typeLib);
    if (hr != S_OK) {
        return hr;
    }
    hr = typeLib->GetTypeInfoOfGuid(IID_IViewServer, &typeInfo_);
    if (hr != S_OK) {
        return hr;
    }
    ITypeInfo2* typeInfo2 = NULL;
    typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
    typeInfo_ = typeInfo2;
    typeLib->Release();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE ViewServer::get_color(COLORREF* retValue)
{
    *retValue = color_;
    return S_OK;
}

HRESULT	STDMETHODCALLTYPE ViewServer::put_color(COLORREF value)
{
    color_ = value;
    return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE ViewServer::Draw(/* [annotation][in] */ _In_ DWORD
        dwDrawAspect, /* [annotation][in] */ _In_ LONG lindex, /* [annotation][unique][in] */ _Null_ void
        *pvAspect, /* [annotation][unique][in] */ _In_opt_ DVTARGETDEVICE *ptd, /* [annotation][in] */ _In_opt_ HDC
        hdcTargetDev, /* [annotation][in] */ _In_ HDC hdcDraw, /* [annotation][in] */ _In_opt_ LPCRECTL
        lprcBounds, /* [annotation][unique][in] */ _In_opt_ LPCRECTL lprcWBounds, /* [annotation][in] */ _In_opt_ BOOL(
            STDMETHODCALLTYPE *pfnContinue)(ULONG_PTR dwContinue), /* [annotation][in] */ _In_ ULONG_PTR dwContinue)
{
	using namespace Gdiplus;
	GdiplusStarter starter;
	Graphics g(hdcDraw);
	Color color;
	color.SetFromCOLORREF(color_);
	SolidBrush brush(color);
	Pen pen(&brush, 3);
	Rect rc;
	if (lprcBounds) {
		rc.X = lprcBounds->left;
		rc.Y = lprcBounds->top;
		rc.Width = lprcBounds->right - lprcBounds->left;
		rc.Height = lprcBounds->bottom - lprcBounds->top;
	} else {
		rc.X = 0;
		rc.Y = 0;
		rc.Width = 100;
		rc.Height = 100;
	}
	g.DrawArc(&pen, rc, 0.f, 360.f);
	return S_OK;
}

/* [local] */ HRESULT STDMETHODCALLTYPE ViewServer::GetColorSet(/* [annotation][in] */ _In_ DWORD
        dwDrawAspect, /* [annotation][in] */ _In_ LONG lindex, /* [annotation][unique][in] */ _Null_ void
        *pvAspect, /* [annotation][unique][in] */ _In_opt_ DVTARGETDEVICE *ptd, /* [annotation][in] */ _In_opt_ HDC
        hicTargetDev, /* [annotation][out] */ _Outptr_ LOGPALETTE **ppColorSet)
{
	return S_FALSE;
}

/* [local] */ HRESULT STDMETHODCALLTYPE ViewServer::Freeze(/* [annotation][in] */ _In_ DWORD
        dwDrawAspect, /* [annotation][in] */ _In_ LONG lindex, /* [annotation][unique][in] */ _Null_ void
        *pvAspect, /* [annotation][out] */ _Out_ DWORD *pdwFreeze)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE ViewServer::Unfreeze(/* [in] */ DWORD dwFreeze)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE ViewServer::SetAdvise(/* [in] */ DWORD aspects, /* [in] */ DWORD advf, /* [unique][in] */
        __RPC__in_opt IAdviseSink *pAdvSink)
{
	return E_FAIL;
}

/* [local] */ HRESULT STDMETHODCALLTYPE ViewServer::GetAdvise(/* [annotation][unique][out] */ _Out_opt_ DWORD
        *pAspects, /* [annotation][unique][out] */ _Out_opt_ DWORD *pAdvf, /* [annotation][out] */ _Outptr_ IAdviseSink
        **ppAdvSink)
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE ViewServer::GetExtent(/* [in] */ DWORD dwDrawAspect, /* [in] */ LONG
        lindex, /* [unique][in] */ __RPC__in_opt DVTARGETDEVICE *ptd, /* [out] */ __RPC__out LPSIZEL lpsizel)
{
	lpsizel->cx = 100;
	lpsizel->cy = 100;
	return S_OK;
}
