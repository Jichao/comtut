#include "stdafx.h"
#include "base/trace.h"
#include "base/ConnectionPointImpl.h"
#include "base/IEnumConnectionPointsImpl.h"
#include "base/ComPtr.h"
#include "Polyline_h.h"
#include "Polyline_i.c"
#include "PolyObj.h"
#include <initguid.h>
// {53386330-1406-425F-8264-062B13FA2D16}
DEFINE_GUID(UUID_PolyPoint,
	0x53386330, 0x1406, 0x425f, 0x82, 0x64, 0x6, 0x2b, 0x13, 0xfa, 0x2d, 0x16);


static const WCHAR kStreamName[] = L"CONTENTS";
namespace {
	bool FileExists(LPCWSTR szPath)
	{
		DWORD dwAttrib = GetFileAttributes(szPath);

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
}



PolylineObj::PolylineObj()
{
	count_ = 0;
	typeInfo_ = nullptr;
	initConnectionMap();
}

PolylineObj::~PolylineObj()
{
	if (typeInfo_) {
		typeInfo_->Release();
	}
	if (classInfo_) {
		classInfo_->Release();
	}

}

HRESULT STDMETHODCALLTYPE PolylineObj::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IDispatch) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IUnknown) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IPolyline) {
		*ppvObject = (IPolyline*)this;
	} else if (riid == IID_IConnectionPointContainer) {
		*ppvObject = (IConnectionPointContainer*)this;
	} else if (riid == IID_IPersistFile) {
		*ppvObject = (IPersistFile*)this;
	} else if (riid == IID_IProvideClassInfo) {
		*ppvObject = (IProvideClassInfo*)this;
	} else if (riid == IID_IProvideClassInfo2) {
		*ppvObject = (IProvideClassInfo2*)this;
	}
	if (*ppvObject) {
		AddRef();
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE PolylineObj::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE PolylineObj::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

HRESULT STDMETHODCALLTYPE PolylineObj::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObj::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
	__RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	*ppTInfo = typeInfo_;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObj::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
	__RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
	16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE PolylineObj::Invoke(/* [annotation][in] */ _In_ DISPID
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

HRESULT STDMETHODCALLTYPE PolylineObj::EnumConnectionPoints(/* [out] */ __RPC__deref_out_opt IEnumConnectionPoints **ppEnum)
{
	*ppEnum = new IEnumConnectionPointsImpl(connectionPoints_);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObj::FindConnectionPoint(/* [in] */ __RPC__in REFIID riid,
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

/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE PolylineObj::put_Color(/* [in] */ COLORREF value)
{
	lineInfo_.color = value;
	return S_OK;
}

/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE PolylineObj::get_Color(/* [retval][out] */ COLORREF *retValue)
{
	*retValue = lineInfo_.color;
	return S_OK;
}

/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE PolylineObj::put_Points(/* [in] */ SAFEARRAY * values)
{
	POINT* points;
	auto hr = SafeArrayAccessData(values, (void**)&points);
	if (FAILED(hr))
		return hr;
	points_.assign(points, points + values->rgsabound->cElements);
	return S_OK;
}

/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE PolylineObj::get_Points(/* [retval][out] */ SAFEARRAY * *retValues)
{
	LPTYPEINFO pTypeInfo = NULL;
	LPTYPELIB pTypelib = NULL;
	IRecordInfo* pRecInfo = NULL;
	auto hr = LoadRegTypeLib(LIBID_GraphicsLibrary, 1, 0, GetUserDefaultLCID(), &pTypelib);
	_ASSERT(SUCCEEDED(hr) && pTypelib);
	hr = pTypelib->GetTypeInfoOfGuid(UUID_PolyPoint, &pTypeInfo);
	_ASSERT(SUCCEEDED(hr) && pTypeInfo);
	hr = GetRecordInfoFromTypeInfo(pTypeInfo, &pRecInfo);
	_ASSERT(SUCCEEDED(hr) && pRecInfo);
	pTypeInfo->Release();
	pTypelib->Release();

	auto psa = SafeArrayCreateVectorEx(VT_RECORD, 0, points_.size(), pRecInfo);
	PolyPoint* points;
	SafeArrayAccessData(psa, (void**)&points);
	_ASSERT(psa);
	for (size_t i = 0; i < points_.size(); ++i) {
		points[i].x = points_[i].x;
		points[i].y = points_[i].y;
	}
	*retValues = psa;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObj::GetClassID(/* [out] */ __RPC__out CLSID *pClassID)
{
	*pClassID = CLSID_PolylineObj;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObj::IsDirty(void)
{
	return dirty_ ? S_OK : S_FALSE;
}

HRESULT STDMETHODCALLTYPE PolylineObj::Load(/* [in] */ __RPC__in LPCOLESTR pszFileName, /* [in] */ DWORD dwMode)
{
	if (SUCCEEDED(StgIsStorageFile(pszFileName))) {
		if (dwMode == 0) {
			dwMode = STGM_READ ;
		}
		dwMode = dwMode | STGM_SHARE_EXCLUSIVE | STGM_DIRECT;
		ComPtr<IStorage> pStorage = nullptr;
		auto hr = StgOpenStorageEx(pszFileName, dwMode, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
		if (FAILED(hr))
			return hr;
		ComPtr<IStream> pStream = nullptr;
		hr = pStorage->OpenStream(kStreamName, NULL, dwMode, 0, &pStream);
		if (FAILED(hr))
			return hr;
		ULONG cb;
		hr = pStream->Read(&lineInfo_, sizeof(PolylineInfo), &cb);
		if (FAILED(hr) || cb != sizeof(PolylineInfo))
			return E_FAIL;
		points_.resize(lineInfo_.pointCount);
		hr = pStream->Read(points_.data(), sizeof(POINT) * lineInfo_.pointCount, &cb);
		if (FAILED(hr) || cb != sizeof(POINT) * lineInfo_.pointCount)
			return E_FAIL;
		pStorage_ = pStorage;
		pStream_ = pStream;
		filePath_ = pszFileName;
		return S_OK;
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE PolylineObj::Save(/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName, /* [in] */ BOOL fRemember)
{
	lineInfo_.pointCount = points_.size();
	ComPtr<IStorage> pStorage;
	ComPtr<IStream> pStream;
	HRESULT hr;
	if (!pszFileName) {
		pStorage = pStorage_;
		pStream = pStream_;
	} else {
		if (SUCCEEDED(StgIsStorageFile(pszFileName))) {
			hr = StgOpenStorageEx(pszFileName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
		} else {
			hr = StgCreateStorageEx(pszFileName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
		}
		if (FAILED(hr))
			return hr;
		hr = pStorage->OpenStream(kStreamName, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream);
		if (FAILED(hr)) {
			hr = pStorage->CreateStream(kStreamName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, 0, &pStream);
		}
		if (FAILED(hr))
			return hr;
	}
	ULARGE_INTEGER ui;
	ui.QuadPart = (int64_t)(sizeof(PolylineInfo) + sizeof(POINT) * lineInfo_.pointCount);
	pStream->SetSize(ui);
	ULONG cb;
	hr = pStream->Write(&lineInfo_, sizeof(PolylineInfo), &cb);
	if (FAILED(hr))
		return hr;
	hr = pStream->Write(points_.data(), sizeof(POINT) * lineInfo_.pointCount, &cb);
	if (FAILED(hr))
		return hr;
	if (!pszFileName || fRemember) {
		dirty_ = false;
	}
	if (pszFileName && fRemember) {
		filePath_ = pszFileName;
	}
	pStorage->SetClass(CLSID_PolylineObj);
	pStorage->Commit(STGC_OVERWRITE);
	pStream_ = NULL;
	pStorage_ = NULL;
	return hr;
}

HRESULT STDMETHODCALLTYPE PolylineObj::SaveCompleted(/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName)
{
	auto hr = StgOpenStorageEx(pszFileName, STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage_);
	if (FAILED(hr))
		return hr;
	hr = pStorage_->OpenStream(kStreamName, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream_);
	if (FAILED(hr))
		return hr;
	filePath_ = pszFileName;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObj::GetCurFile(/* [out] */ __RPC__deref_out_opt LPOLESTR *ppszFileName)
{
	LPWSTR path = (LPWSTR)CoTaskMemAlloc((filePath_.size() + 1) * sizeof(WCHAR));
	StringCchCopy(path, filePath_.size() + 1, filePath_.c_str());
	*ppszFileName = path;
	return S_OK;
}

HRESULT PolylineObj::ensureTypeInfo()
{
	ITypeLib* typeLib;
	auto hr = LoadRegTypeLib(LIBID_GraphicsLibrary, 1, 0, 0, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = typeLib->GetTypeInfoOfGuid(IID_IPolyline, &typeInfo_);
	if (hr != S_OK) {
		return hr;
	}
	ITypeInfo2* typeInfo2 = NULL;
	typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
	typeInfo_ = typeInfo2;
	typeLib->Release();
	return S_OK;
}

void PolylineObj::initConnectionMap()
{
	connectionPoints_.push_back(new ConnectionPointImpl<_IPolylineEvent>(DIID__IPolylineEvent, this));
}

void PolylineObj::fireOnResult(BSTR result)
{
	IConnectionPoint* cp = nullptr;
	auto hr = FindConnectionPoint(DIID__IPolylineEvent, &cp);
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

HRESULT STDMETHODCALLTYPE PolylineObj::GetClassInfo(/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTI)
{
	ensureClassInfo();
	classInfo_->AddRef();
	*ppTI = classInfo_;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PolylineObj::GetGUID(/* [in] */ DWORD dwGuidKind, /* [out] */ __RPC__out GUID *pGUID)
{
	*pGUID = DIID__IPolylineEvent;
	return S_OK;
}

HRESULT PolylineObj::ensureClassInfo()
{
	ITypeLib* typeLib;
	auto hr = LoadRegTypeLib(LIBID_GraphicsLibrary, 1, 0, 0, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = typeLib->GetTypeInfoOfGuid(__uuidof(PolylineObj), &classInfo_);
	if (hr != S_OK) {
		return hr;
	}
	ITypeInfo2* typeInfo2 = NULL;
	classInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
	classInfo_ = typeInfo2;
	typeLib->Release();
	return S_OK;

}
