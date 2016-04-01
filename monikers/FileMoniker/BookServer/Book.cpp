#include "stdafx.h"
#include "base/trace.h"
#include "base/ConnectionPointImpl.h"
#include "base/IEnumConnectionPointsImpl.h"
#include "base/ComPtr.h"
#include "base/ComQIPtr.h"
#include "base/StringUtils.h"
#include "book_h.h"
#include "book.h"

static const WCHAR kStreamName[] = L"CONTENTS";

namespace {
	bool FileExists(LPCWSTR szPath)
	{
		DWORD dwAttrib = GetFileAttributes(szPath);

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
}


Book::Book()
{
	count_ = 0;
	typeInfo_ = nullptr;
}

Book::~Book()
{
	if (typeInfo_) {
		typeInfo_->Release();
	}

}

HRESULT STDMETHODCALLTYPE Book::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IDispatch) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IUnknown) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IBook) {
		*ppvObject = (IBook*)this;
	} else if (riid == IID_IPersistFile) {
		*ppvObject = (IPersistFile*)this;
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

ULONG STDMETHODCALLTYPE Book::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE Book::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

HRESULT STDMETHODCALLTYPE Book::GetTypeInfoCount(/* [out] */ __RPC__out UINT *pctinfo)
{
	*pctinfo = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Book::GetTypeInfo(/* [in] */ UINT iTInfo, /* [in] */ LCID lcid, /* [out] */
	__RPC__deref_out_opt ITypeInfo **ppTInfo)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	*ppTInfo = typeInfo_;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Book::GetIDsOfNames(/* [in] */ __RPC__in REFIID riid, /* [size_is][in] */
	__RPC__in_ecount_full(cNames) LPOLESTR *rgszNames, /* [range][in] */ __RPC__in_range(0,
	16384) UINT cNames, /* [in] */ LCID lcid, /* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId)
{
	if (FAILED(ensureTypeInfo())) {
		return E_FAIL;
	}
	return DispGetIDsOfNames(typeInfo_, rgszNames, cNames, rgDispId);
}

/* [local] */ HRESULT STDMETHODCALLTYPE Book::Invoke(/* [annotation][in] */ _In_ DISPID
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

HRESULT STDMETHODCALLTYPE Book::GetClassID(/* [out] */ __RPC__out CLSID *pClassID)
{
	*pClassID = CLSID_Book;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Book::IsDirty(void)
{
	return dirty_ ? S_OK : S_FALSE;
}

HRESULT STDMETHODCALLTYPE Book::Load(/* [in] */ __RPC__in LPCOLESTR pszFileName, /* [in] */ DWORD dwMode)
{
	if (SUCCEEDED(StgIsStorageFile(pszFileName))) {
		if (dwMode == 0) {
			dwMode = STGM_READ;
		}
		dwMode = dwMode | STGM_SHARE_DENY_NONE | STGM_DIRECT;
		ComPtr<IStorage> pStorage = nullptr;
		auto hr = StgOpenStorageEx(pszFileName, dwMode, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
		if (FAILED(hr))
			return hr;
		ComPtr<IStream> pStream = nullptr;
		hr = pStorage->OpenStream(kStreamName, NULL, dwMode, 0, &pStream);
		if (FAILED(hr))
			return hr;

		ULONG cb;
		bookName_.readFromStream(pStream);
		hr = pStream->Read(&pageCount_, sizeof(pageCount_), &cb);
		if (FAILED(hr) || cb != sizeof(pageCount_))
			return E_FAIL;
		int chapterCount;
		hr = pStream->Read(&chapterCount, sizeof(chapterCount), &cb);
		if (FAILED(hr) || cb != sizeof(chapterCount))
			return E_FAIL;
		for (int i = 0; i < chapterCount; ++i) {
			ComPtr<IChapter> chapterObj;
			ComBSTR chapterName;
			if (FAILED(chapterName.readFromStream(pStream))) {
				chapters_.push_back(chapterObj);
				continue;
			}
			ComPtr<IStorage> chapterStg;
			auto hr = pStorage->OpenStorage(chapterName, NULL, dwMode, 0, NULL, &chapterStg);
			if (FAILED(hr)) {
				chapters_.push_back(chapterObj);
				continue;
			}
			ComPtr<IPersistStorage> chapterPersistStroage;
			hr = CoCreateInstance(CLSID_Chapter, NULL, CLSCTX_INPROC_SERVER, IID_IPersistStorage, (void**)&chapterPersistStroage);
			if (FAILED(hr)) {
				chapters_.push_back(chapterObj);
				continue;
			}
			hr = chapterPersistStroage->Load(chapterStg);
			if (FAILED(hr)) {
				chapters_.push_back(chapterObj);
				continue;
			}
			ComQIPtr<IChapter> ptr = chapterPersistStroage;
			chapterObj = ptr;
			chapters_.push_back(chapterObj);
		}

		pStorage_ = pStorage;
		pStream_ = pStream;
		filePath_ = pszFileName;
		return S_OK;
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Book::Save(/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName, /* [in] */ BOOL fRemember)
{
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
		hr = pStorage->OpenStream(kStreamName, NULL, STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, &pStream);
		if (FAILED(hr)) {
			hr = pStorage->CreateStream(kStreamName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE, 0, 0, &pStream);
		}
		if (FAILED(hr))
			return hr;
	}

	ULONG cb;
	hr = bookName_.writeToStream(pStream);
	if (FAILED(hr))
		return hr;
	hr = pStream->Write(&pageCount_, 4, &cb);
	if (FAILED(hr) || cb != 4)
		return hr;
	int count = chapters_.size();
	hr = pStream->Write(&count, 4, &cb);
	if (FAILED(hr) || cb != 4)
		return hr;

	for (int i = 0; i < count; ++i) {
		ComBSTR chapterName = getChapterName(i);
		hr = chapterName.writeToStream(pStream);
		if (FAILED(hr))
			continue;
		ComPtr<IStorage> chapterStg;
		auto hr = pStorage->OpenStorage(chapterName, NULL, STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &chapterStg);
		if (FAILED(hr)) {
			hr = pStorage->CreateStorage(chapterName, STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &chapterStg);
			if (FAILED(hr))
				continue;
		}
		ComQIPtr<IPersistStorage> obj = chapters_[i];
		obj->Save(chapterStg, TRUE);
		WriteClassStg(chapterStg, CLSID_Chapter);
	}

	if (!pszFileName || fRemember) {
		dirty_ = false;
	}
	if (pszFileName && fRemember) {
		filePath_ = pszFileName;
	}
	pStorage->SetClass(CLSID_Book);
	pStorage->Commit(STGC_OVERWRITE);
	pStream_ = NULL;
	pStorage_ = NULL;
	return hr;
}

HRESULT STDMETHODCALLTYPE Book::SaveCompleted(/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName)
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

HRESULT STDMETHODCALLTYPE Book::GetCurFile(/* [out] */ __RPC__deref_out_opt LPOLESTR *ppszFileName)
{
	LPWSTR path = (LPWSTR)CoTaskMemAlloc((filePath_.size() + 1) * sizeof(WCHAR));
	StringCchCopy(path, filePath_.size() + 1, filePath_.c_str());
	*ppszFileName = path;
	return S_OK;
}

HRESULT Book::ensureTypeInfo()
{
	ITypeLib* typeLib;
	auto hr = LoadRegTypeLib(LIBID_BookLibrary, 1, 0, 0, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = typeLib->GetTypeInfoOfGuid(IID_IBook, &typeInfo_);
	if (hr != S_OK) {
		return hr;
	}
	ITypeInfo2* typeInfo2 = NULL;
	typeInfo_->QueryInterface(IID_ITypeInfo2, (void**)&typeInfo2);
	typeInfo_ = typeInfo2;
	typeLib->Release();
	return S_OK;
}

HRESULT Book::get_pageCount(UINT32* retValue)
{
	*retValue = pageCount_;
	return S_OK;
}

HRESULT Book::get_name(BSTR* value)
{
	*value = bookName_.Clone();
	return S_OK;
}

HRESULT Book::put_name(BSTR value)
{
	bookName_ = value;
	return S_OK;

}

HRESULT Book::put_pageCount(UINT32 value)
{
	pageCount_ = value;
	return S_OK;
}

HRESULT Book::CreateChapter(IChapter** chapter)
{
	if (!chapter)
		return E_POINTER;
	ensureFirstStorage();
	ComBSTR name = getChapterName(chapters_.size());
	ComPtr<IStorage> chapterStg;
	pStorage_->CreateStorage(name, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, 0, 0, &chapterStg);
	ComPtr<IPersistStorage>chapterPstg;
	auto hr = CoCreateInstance(CLSID_Chapter, NULL, CLSCTX_INPROC_SERVER, IID_IPersistStorage, (void**)&chapterPstg);
	if (FAILED(hr))
		return hr;
	hr = WriteClassStg(chapterStg, CLSID_Chapter);
	if (FAILED(hr))
		return hr;
	hr = chapterPstg->InitNew(chapterStg);
	if (FAILED(hr))
		return hr;
	ComQIPtr<IChapter> obj = chapterPstg;
	*chapter = obj;
	if (*chapter) {
		(*chapter)->AddRef();
		chapters_.push_back(*chapter);
	}
	return hr;
}

HRESULT Book::GetChapter(UINT index, IChapter** chapter)
{ 
	if (index > chapters_.size())
		return E_INVALIDARG;
	if (!chapter)
		return E_POINTER;
	chapters_[index].CopyTo(chapter);
	return S_OK;
}

HRESULT Book::ParseDisplayName(IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut)
{
	if (!pchEaten || !ppmkOut)
		return E_POINTER;

	for (int i = 0; i < chapters_.size(); ++i){
		std::wstring needle = getChapterName(i);
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

HRESULT STDMETHODCALLTYPE Book::EnumObjects(DWORD grfFlags, IEnumUnknown **ppenum)
{
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Book::LockContainer(BOOL fLock)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Book::GetObject(/* [in] */ __RPC__in LPOLESTR pszItem, /* [in] */ DWORD dwSpeedNeeded,
	/* [unique][in] */ __RPC__in_opt IBindCtx *pbc, /* [in] */ __RPC__in REFIID riid,
	/* [iid_is][out] */ __RPC__deref_out_opt void **ppvObject)
{
	for (int i = 0; i < chapters_.size(); ++i){
		std::wstring needle = getChapterName(i);
		std::wstring target = pszItem;
		if (needle == target) {
			auto hr = chapters_[i]->QueryInterface(riid, ppvObject);
			//todo bindctx
			return hr;
		}
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Book::GetObjectStorage(/* [in] */ __RPC__in LPOLESTR pszItem, /* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
	/* [in] */ __RPC__in REFIID riid, /* [iid_is][out] */ __RPC__deref_out_opt void **ppvStorage)
{
	for (int i = 0; i < chapters_.size(); ++i){
		std::wstring needle = getChapterName(i);
		std::wstring target = pszItem;
		if (needle == target) {
			auto hr = chapters_[i]->QueryInterface(riid, ppvStorage);
			//todo bindctx
			return hr;
		}
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE Book::IsRunning(/* [in] */ __RPC__in LPOLESTR pszItem)
{
	auto index = nameToChapterIndex(pszItem);
	if (index == -1 || index >= chapters_.size())
		return MK_E_NOOBJECT;
	if (chapters_[index])
		return S_OK;
	return S_FALSE;
}


std::wstring Book::getChapterName(int index)
{
	WCHAR name[20];
	StringCchPrintf(name, 20, L"chapter%d", index);
	return name;
}

int Book::nameToChapterIndex(const std::wstring& name)
{
	auto pos = name.find(L"chapter");
	if (pos == -1)
		return -1;
	try {
		return std::stoi(name.substr(7));
	} catch (...) {
		return -1;
	}
}

void Book::ensureFirstStorage()
{
	if (pStorage_)
		return;
	auto hr = StgCreateStorageEx(NULL, STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE, STGFMT_STORAGE, 0, NULL, NULL, IID_IStorage, (void**)&pStorage_);
}
