#include "stdafx.h"
#include "base/trace.h"
#include "base/ComPtr.h"
#include "base/ComQIPtr.h"
#include "base/ComBSTR.h"
#include "WordTest.h"

void WordTest::testWord()
{
	//static const WCHAR kFilePath[] = LR"(F:\bk\physics\quantum mechanics\exam\2009\09北京大学量子力学（记忆版）.doc)";
	DWORD rtfFormat = RegisterClipboardFormat(L"Rich Text Format");
	static const WCHAR kFilePath[] = LR"(e:\test.docx)";
	ComPtr<IMoniker> fileMoniker;
	auto hr = CreateFileMoniker(kFilePath, &fileMoniker);
	if (FAILED(hr))
		return;
	ComPtr<IBindCtx> pbc;
	CreateBindCtx(0, &pbc);
	ComPtr<IDataObject> dataObject;
	hr = fileMoniker->BindToObject(pbc, NULL, IID_IDataObject, (void**)&dataObject);
	if (FAILED(hr))
		return;

	ComPtr<IDataObject> dataObject2;
	hr = fileMoniker->BindToObject(pbc, NULL, IID_IDataObject, (void**)&dataObject2);
	if (FAILED(hr))
		return;

	{
		ComPtr<IEnumFORMATETC> enumFormat;
		auto hr = dataObject->EnumFormatEtc(DATADIR_GET, &enumFormat);
		if (FAILED(hr))
			return;
		FORMATETC format;
		std::vector<FORMATETC> getFormats;
		while ((hr = enumFormat->Next(1, &format, NULL)) == S_OK) {
			getFormats.push_back(format);
		}
		assert(getFormats.size() > 1);
	}

	{
		ComPtr<IEnumFORMATETC> enumFormat;
		auto hr = dataObject->EnumFormatEtc(DATADIR_SET, &enumFormat);
		if (FAILED(hr))
			return;
		FORMATETC format;
		std::vector<FORMATETC> setFormats;
		while ((hr = enumFormat->Next(1, &format, NULL)) == S_OK) {
			setFormats.push_back(format);
		}
		assert(setFormats.size() > 1);
	}

	{
		FORMATETC etc = { 0 };
		etc.cfFormat = CF_UNICODETEXT;
		etc.dwAspect = DVASPECT_CONTENT;
		etc.lindex = -1;
		etc.tymed = TYMED_HGLOBAL;
		STGMEDIUM stg = { 0 };
		hr = dataObject->GetData(&etc, &stg);
		if (FAILED(hr))
			return;
		auto ptr = GlobalLock(stg.hGlobal);
		assert(ptr);
	}


	{
		FORMATETC etc = { 0 };
		etc.cfFormat = CF_TEXT;
		etc.dwAspect = DVASPECT_CONTENT;
		etc.lindex = -1;
		etc.tymed = TYMED_HGLOBAL;
		STGMEDIUM stg = { 0 };
		hr = dataObject->GetData(&etc, &stg);
		if (FAILED(hr))
			return;
		//return gbk encoding.
		auto ptr = GlobalLock(stg.hGlobal);
		assert(ptr);
	}

	{
		FORMATETC format = { 0 };
		format.cfFormat = CF_TEXT;
		format.dwAspect = DVASPECT_CONTENT;
		format.lindex = -1;
		format.tymed = TYMED_HGLOBAL;
		DWORD dwConn;
		dataObject->DAdvise(&format, ADVF_NODATA, this, &dwConn);
		STGMEDIUM stg = { 0 };
		const static CHAR kContent[] = "how to zhangbi\r\n";
		auto hg = GlobalAlloc(GPTR, sizeof(kContent) + 1);
		auto ptr = (CHAR*)GlobalLock(hg);
		StringCchCopyA(ptr, sizeof(kContent), kContent);
		stg.tymed = TYMED_HGLOBAL;
		stg.hGlobal = hg;
		hr = dataObject->SetData(&format, &stg, FALSE);
		if (FAILED(hr))
			return;
		assert(stg.lpszFileName);
		ReleaseStgMedium(&stg);
		ComQIPtr<IPersistFile> file = dataObject;
		hr = file->Save(NULL, TRUE);
		if (FAILED(hr))
			return;
	}
}

WordTest::WordTest()
{ 
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
}

WordTest::~WordTest()
{
	CoUninitialize();
}

HRESULT STDMETHODCALLTYPE WordTest::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IUnknown) {
		*ppvObject = (IDispatch*)this;
	} else if (riid == IID_IAdviseSink) {
		*ppvObject = (IAdviseSink*)this;
	} 	if (*ppvObject) {
		AddRef();
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE WordTest::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE WordTest::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

/* [local] */ void STDMETHODCALLTYPE WordTest::OnDataChange(/* [annotation][unique][in] */ _In_ FORMATETC *pFormatetc, /* [annotation][unique][in] */ _In_ STGMEDIUM *pStgmed)
{
	printf("ondatachagned\n");
	return;
}

/* [local] */ void STDMETHODCALLTYPE WordTest::OnViewChange(/* [in] */ DWORD dwAspect, /* [in] */ LONG lindex)
{

}

/* [local] */ void STDMETHODCALLTYPE WordTest::OnRename(/* [annotation][in] */ _In_ IMoniker *pmk)
{

}

/* [local] */ void STDMETHODCALLTYPE WordTest::OnSave(void)
{

}

/* [local] */ void STDMETHODCALLTYPE WordTest::OnClose(void)
{

}
