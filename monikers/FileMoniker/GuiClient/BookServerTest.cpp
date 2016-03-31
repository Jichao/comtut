#include "stdafx.h"
#include "base/trace.h"
#include "base/ComPtr.h"
#include "base/ComQIPtr.h"
#include "base/ComBSTR.h"
#include "../BookServer/book_h.h"
#include "../BookServer/book_i.c"
#include "BookServerTest.h"

static const WCHAR kFileName[] = L"e:\\keke.bin";
static const WCHAR kMonikerFileName[] = L"e:\\moniker.bin";
static const WCHAR kStreamName[] = L"cc";
static const WCHAR kBookName[] = L"21天COM从入门到精通";
static const int kData[] = { 1, 2, 3, 4, 5, 6 };

BookServerTest::BookServerTest()
{
	CoInitialize(NULL);
}


BookServerTest::~BookServerTest()
{
}

int BookServerTest::createBook()
{
	ComPtr<IBook> bk;
	auto hr = CoCreateInstance(CLSID_Book, NULL, CLSCTX_INPROC_SERVER, IID_IBook, (void**)&bk);
	if (FAILED(hr)) {
		return -1;
	}
	bk->put_name(ComBSTR(kBookName));
	bk->put_pageCount(10);
	ComPtr<IChapter> ch0;
	bk->CreateChapter(&ch0);
	ch0->put_name(L"概述");

	ComPtr<ISection> sec0;
	ch0->CreateSection(&sec0);
	sec0->put_name(L"how to read this book");
	sec0->put_content(L"you could skip the lvoe section, if you're single");

	ComQIPtr<IPersistFile> pf = bk;
	pf->Save(kFileName, TRUE);
	pf->SaveCompleted(kFileName);
	return 0;
}

int BookServerTest::readBook()
{
	ComPtr<IBook> book;
	auto hr = CoCreateInstance(CLSID_Book, NULL, CLSCTX_INPROC_SERVER,
		IID_IBook, (void**)&book);
	if (FAILED(hr)) {
		return -1;
	}
	ComQIPtr<IPersistFile> pf = book;
	hr = pf->Load(kFileName, STGM_READ | STGM_SHARE_EXCLUSIVE);
	if (FAILED(hr)) {
		TRACE("load persist file failed\n");
		return -1;
	}

	ComBSTR name;
	book->get_name(&name);
	UINT32 pageCount;
	book->get_pageCount(&pageCount);
	TRACE(L"book name = %s,page count = %u\n", name, pageCount);

	ComPtr<IChapter> ch0;
	book->GetChapter(0, &ch0);
	ch0->get_name(&name);
	TRACE(L"ch0 name = %s\n", name);

	ComPtr<ISection> sec;
	ch0->GetSection(0, &sec);
	sec->get_name(&name);
	ComBSTR content;
	sec->get_content(&content);
	TRACE(L"sec name = %s, content = %s\n", name, content);
	return 0;
}

int BookServerTest::createFileMoniker()
{
	ComPtr<IMoniker> moniker;
	auto hr = CreateFileMoniker(kFileName, &moniker);
	if (FAILED(hr)) {
		return -1;
	}
	IBindCtx* pbc;
	CreateBindCtx(0, &pbc);
	ComPtr<IBook> book;
	hr = moniker->BindToObject(pbc, NULL, IID_IBook, (void**)&book);
	if (FAILED(hr)) {
		return -1;
	}
	ComPtr<IStorage> pStorage;
	ComPtr<IStream> pStream;
	hr = StgCreateStorageEx(kMonikerFileName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
	if (FAILED(hr))
		return hr;
	hr = pStorage->CreateStream(kStreamName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		0, 0, &pStream);
	if (FAILED(hr))
		return hr;
	OleSaveToStream(moniker, pStream);
	return 0;
}

int BookServerTest::readFileMoniker()
{
	ComPtr<IStorage> pStorage;
	ComPtr<IStream> pStream;
	auto hr = StgOpenStorageEx(kMonikerFileName,
		STGM_READ | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
	if (FAILED(hr))
		return hr;
	hr = pStorage->OpenStream(kStreamName, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream);
	if (FAILED(hr))
		return hr;
	ComPtr<IMoniker> moniker;
	OleLoadFromStream(pStream, IID_IMoniker, (void**)&moniker);
	IBindCtx* pbc;
	CreateBindCtx(0, &pbc);
	ComPtr<IBook> book;
	hr = moniker->BindToObject(pbc, NULL, IID_IBook, (void**)&book);
	if (FAILED(hr)) {
		return -1;
	}
	ComBSTR name;
	book->get_name(&name);
	assert(name == kBookName);
	return 0;
}

int BookServerTest::readItemMoniker()
{
	ComPtr<IStorage> pStorage;
	ComPtr<IStream> pStream;
	auto hr = StgOpenStorageEx(kMonikerFileName,
		STGM_READ | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
	if (FAILED(hr))
		return hr;
	hr = pStorage->OpenStream(kStreamName, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream);
	if (FAILED(hr))
		return hr;
	IBindCtx* pbc;
	CreateBindCtx(0, &pbc);
	ComPtr<IMoniker> bkMoniker;
	OleLoadFromStream(pStream, IID_IMoniker, (void**)&bkMoniker);

	{
		ComPtr<IMoniker> chMoniker;
		CreateItemMoniker(L"!", L"chapter0", &chMoniker);
		ComPtr<IChapter> chObj;
		hr = chMoniker->BindToObject(pbc, bkMoniker, IID_IChapter, (void**)&chObj);
		if (FAILED(hr))
			return hr;
		ComBSTR chName;
		chObj->get_name(&chName);
		assert(chName == L"概述");
	}

	{
		ComPtr<ISection> secObj;
		ComPtr<IMoniker> chMoniker;
		ComPtr<IMoniker> secMoniker;
		CreateItemMoniker(L"!", L"chapter0", &chMoniker);
		CreateItemMoniker(L"!", L"section0", &secMoniker);
		ComPtr<IMoniker> composeMoniker;
		chMoniker->ComposeWith(secMoniker, FALSE, &composeMoniker);
		hr = composeMoniker->BindToObject(pbc, bkMoniker, IID_ISection, (void**)&secObj);
		if (FAILED(hr))
			return hr;
		ComBSTR name;
		secObj->get_name(&name);
	}

	//ComPtr<IMoniker> secMoniker;
	//CreateItemMoniker(L"!", L"section0", &secMoniker);
	//ComPtr<ISection> secObj;
	//hr = secMoniker->BindToObject(pbc, bkMoniker, IID_ISection, (void**)&secObj);
	//if (FAILED(hr))
	//	return hr;
	//ComBSTR secName;
	//secObj->get_name(&secName);
	//assert(secName == L"how to read this book");

	//chObj = NULL;
	//ComPtr<IMoniker> composeMoniker;
	//hr = bkMoniker->ComposeWith(chMoniker, FALSE, &composeMoniker);
	//if (FAILED(hr))
	//	return hr;
	//composeMoniker->BindToObject(pbc, NULL, IID_IChapter, (void**)&chObj);
	//chObj->get_name(&chName);
	//assert(chName == L"概述");
	//CreateGenericComposite(bkMoniker, chMoniker, &composeMoniker);
	return 0;
}
