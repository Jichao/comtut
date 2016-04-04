#include "stdafx.h"
#include "base/trace.h"
#include "base/ConnectionPointImpl.h"
#include "base/IEnumConnectionPointsImpl.h"
#include "base/ComPtr.h"
#include "base/StringUtils.h"
#include "base/OleUtils.h"
#include "base/ComQIPtr.h"
#include "book_h.h"
#include "chapter.h"

static const WCHAR kStreamName[] = L"CONTENTS";

Chapter::Chapter()
{
	count_ = 0;
	typeInfo_ = nullptr;
	inited_ = false;
}

Chapter::~Chapter()
{
	if (typeInfo_) {
		typeInfo_->Release();
	}
}

HRESULT STDMETHODCALLTYPE Chapter::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IDispatch) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IUnknown) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IChapter) {
		*ppvObject = (IChapter*)this;
	} else if (riid == IID_IPersistStorage) {
		*ppvObject = (IPersistStorage*)this;
	} else if (riid == IID_IOleItemContainer) {
		*ppvObject = (IOleItemContainer*)this;
	}
	if (*ppvObject) {
		AddRef();
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE Chapter::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE Chapter::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

HRESULT STDMETHODCALLTYPE Chapter::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Chapter::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
	__RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	*ppTInfo = typeInfo_;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Chapter::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
	__RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
	16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE Chapter::Invoke(/* [annotation][in] */ _In_ DISPID
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

HRESULT STDMETHODCALLTYPE Chapter::GetClassID(/* [out] */ __RPC__out CLSID *pClassID)
{
	*pClassID = CLSID_Chapter;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Chapter::IsDirty(void)
{
	return dirty_ ? S_OK : S_FALSE;
}

HRESULT STDMETHODCALLTYPE Chapter::Load(/* [unique][in] */ __RPC__in_opt IStorage *pStg)
{
	if (!pStg)
		return E_POINTER;

	ComPtr<IStream> pStream = nullptr;
	auto dwMode = STGM_READ | STGM_SHARE_EXCLUSIVE | STGM_DIRECT;
	auto hr = pStg->OpenStream(kStreamName, NULL, dwMode, 0, &pStream);
	if (FAILED(hr))
		return hr;

	ULONG cb;
	hr = chapterName_.readFromStream(pStream);
	if (FAILED(hr))
		return hr;

	int sectionCount;
	hr = pStream->Read(&sectionCount, sizeof(sectionCount), &cb);
	if (FAILED(hr) || cb != sizeof(sectionCount))
		return E_FAIL;

	for (int i = 0; i < sectionCount; ++i) {
		ComPtr<ISection> sectionObj;
		ComBSTR sectionName;
		if (FAILED(sectionName.readFromStream(pStream))) {
			sections_.push_back(sectionObj);
			continue;
		}
		ComPtr<IStream> sectionStream;
		auto hr = pStg->OpenStream(sectionName, NULL, dwMode, 0, &sectionStream);
		if (FAILED(hr)) {
			sections_.push_back(sectionObj);
			continue;
		}
		hr = OleLoadFromStream(sectionStream, IID_ISection, (void**)&sectionObj);
		if (FAILED(hr)) {
			sections_.push_back(sectionObj);
			continue;
		}
		sections_.push_back(sectionObj);
	}
	pStg_ = pStg;
	pStream_ = pStream;
	inited_ = true;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Chapter::Save(/* [unique][in] */ __RPC__in_opt IStorage *pStgSave, /* [in] */ BOOL fSameAsLoad)
{
	ComPtr<IStorage> pStg;
	ComPtr<IStream> pStream;
	HRESULT hr;
	if (!pStgSave) {
		pStg = pStg;
		pStream = pStream_;
	} else {
		pStg = pStgSave;
		hr = pStg->OpenStream(kStreamName, NULL, STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, &pStream);
		if (FAILED(hr)) {
			hr = pStg->CreateStream(kStreamName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, 0, &pStream);
		}
		if (FAILED(hr))
			return hr;
	}

	ULONG cb;
	hr = chapterName_.writeToStream(pStream);
	if (FAILED(hr))
		return hr;

	int count = sections_.size();
	hr = pStream->Write(&count, 4, &cb);
	if (FAILED(hr) || cb != 4)
		return hr;
	for (int i = 0; i < sections_.size(); ++i) {
		ComBSTR sectionName = getSectionName(i);
		hr = sectionName.writeToStream(pStream);
		if (FAILED(hr))
			continue;
		ComPtr<IStream> sectionStream;
		hr = pStg->OpenStream(sectionName, NULL, STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, &sectionStream);
		if (FAILED(hr)) {
			hr = pStg->CreateStream(sectionName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, 0, &sectionStream);
		}
		if (FAILED(hr))
			continue;
		ComQIPtr<IPersistStreamInit> init = sections_[i];
		OleUtils::SaveToStream(init, sectionStream);
		sectionStream->Commit(STGC_OVERWRITE);
	}
	if (!pStgSave || fSameAsLoad) {
		dirty_ = false;
	}
	if (pStgSave && fSameAsLoad) {
		pStg_ = pStg;
	}
	pStream_ = NULL;
	pStg = NULL;
	return hr;
}

HRESULT STDMETHODCALLTYPE Chapter::SaveCompleted(/* [unique][in] */ __RPC__in_opt IStorage *pStgNew)
{
	pStg_ = pStgNew;
	return S_OK;
}

HRESULT Chapter::ensureTypeInfo()
{
	ITypeLib* typeLib;
	auto hr = LoadRegTypeLib(LIBID_BookLibrary, 1, 0, 0, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = typeLib->GetTypeInfoOfGuid(IID_IChapter, &typeInfo_);
	if (hr != S_OK) {
		return hr;
	}
	ITypeInfo2* typeInfo2 = NULL;
	typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
	typeInfo_ = typeInfo2;
	typeLib->Release();
	return S_OK;
}

HRESULT Chapter::get_name(BSTR* value)
{
	*value = chapterName_.Clone();
	return S_OK;
}

HRESULT Chapter::put_name(BSTR value)
{
	chapterName_ = value;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE Chapter::CreateSection(/* [in] */ ISection **section)
{
	if (!pStg_)
		return E_FAIL;
	if (!section)
		return E_POINTER;
	ComBSTR name = getSectionName(sections_.size());
	ComPtr<IPersistStreamInit> sectionStream;
	auto hr = CoCreateInstance(CLSID_Section, NULL, CLSCTX_INPROC_SERVER, IID_IPersistStreamInit, (void**)&sectionStream);
	if (FAILED(hr))
		return hr;
	sectionStream->InitNew();
	ComQIPtr<ISection> obj = sectionStream;
	*section = obj;
	if (*section) {
		(*section)->AddRef();
		sections_.push_back(*section);
	}
	return hr;
}

HRESULT STDMETHODCALLTYPE Chapter::GetSection(/* [in] */ UINT index, /* [out] */ ISection **section)
{
	if (!section)
		return E_POINTER;
	if (index >= sections_.size())
		return E_INVALIDARG;
	*section = sections_[index];
	if (*section) {
		(*section)->AddRef();
	}
	return S_OK;
}


HRESULT Chapter::ParseDisplayName(IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut)
{
	if (!pchEaten || !ppmkOut)
		return E_POINTER;

	for (int i = 0; i < sections_.size(); ++i){
		std::wstring needle = getSectionName(i);
		std::wstring stack = pszDisplayName;
		if (su::startsWith(stack, needle)) {
			bool match = false;
			int matchLen = 0;
			if (stack.size() > needle.size() && stack[needle.size()] == L'!') {
				match = true;
				matchLen = needle.size() + 1;
			} else {
				match = true;
				matchLen = needle.size();
			}
			if (match) {
				auto hr = CreateItemMoniker(L"!", needle.c_str(), ppmkOut);
				if (SUCCEEDED(hr)) {
					*pchEaten = matchLen;
				}
				if (pbc && SUCCEEDED(hr)) {
					pbc->RegisterObjectBound(*ppmkOut);
				}
			}
		}
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Chapter::EnumObjects(DWORD grfFlags, IEnumUnknown **ppenum)
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Chapter::LockContainer(BOOL fLock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Chapter::GetObject(/* [in] */ __RPC__in LPOLESTR pszItem, /* [in] */ DWORD dwSpeedNeeded,
	/* [unique][in] */ __RPC__in_opt IBindCtx *pbc, /* [in] */ __RPC__in REFIID riid,
	/* [iid_is][out] */ __RPC__deref_out_opt void **ppvObject)
{
	for (int i = 0; i < sections_.size(); ++i){
		std::wstring needle = getSectionName(i);
		std::wstring target = pszItem;
		if (needle == target) {
			auto hr = sections_[i]->QueryInterface(riid, ppvObject);
			//todo bindctx
			return hr;
		}
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Chapter::GetObjectStorage(/* [in] */ __RPC__in LPOLESTR pszItem, /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
	/* [in] */ __RPC__in REFIID riid, /* [iid_is][out] */ __RPC__deref_out_opt void **ppvStorage)
{
	for (int i = 0; i < sections_.size(); ++i){
		std::wstring needle = getSectionName(i);
		std::wstring target = pszItem;
		if (needle == target) {
			auto hr = sections_[i]->QueryInterface(riid, ppvStorage);
			//todo bindctx
			return hr;
		}
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Chapter::IsRunning(/* [in] */ __RPC__in LPOLESTR pszItem)
{
	auto index = nameToSectionIndex(pszItem);
	if (index == -1 || index >= sections_.size())
		return MK_E_NOOBJECT;
	if (sections_[index])
		return S_OK;
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE Chapter::InitNew(/* [unique][in] */ __RPC__in_opt IStorage *pStg)
{
	if (inited_)
		return CO_E_ALREADYINITIALIZED;
	if (!pStg)
		return E_POINTER;
	pStg_ = pStg;
	auto hr = pStg->CreateStream(kStreamName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, 0, &pStream_);
	return hr;
}

HRESULT STDMETHODCALLTYPE Chapter::HandsOffStorage(void)
{
	pStream_ = NULL;
	for (auto& item : sections_) {
		item = nullptr;
	}
	return S_OK;
}

std::wstring Chapter::getSectionName(int index)
{
	WCHAR name[20];
	StringCchPrintf(name, 20, L"section%d", index);
	return name;
}

int Chapter::nameToSectionIndex(const std::wstring& name)
{
	auto pos = name.find(L"section");
	if (pos == -1)
		return -1;
	try {
		return std::stoi(name.substr(7));
	} catch (...) {
		return -1;
	}
}
