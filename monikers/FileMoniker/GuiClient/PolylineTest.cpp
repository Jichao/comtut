#include "stdafx.h"
#include "base/trace.h"
#include "../Polyline/Polyline_i.c"
#include "PolylineTest.h"

static const WCHAR kFileName[] = L"e:\\keke.bin";
static const WCHAR kMonikerFileName[] = L"e:\\moniker.bin";
static const WCHAR kStreamName[] = L"cc";
static const int kData[] = { 1, 2, 3, 4, 5, 6 };

PolylineTest::PolylineTest()
{
	CoInitialize(NULL);
}


PolylineTest::~PolylineTest()
{
}

int PolylineTest::writePersistFile()
{
	ComPtr<IPolyline> pl;
	auto hr = CoCreateInstance(CLSID_PolylineObj, NULL, CLSCTX_INPROC_SERVER, IID_IPolyline, (void**)&pl);
	if (FAILED(hr)) {
		return -1;
	}
	LPTYPEINFO pTypeInfo = NULL;
	LPTYPELIB pTypelib = NULL;
	IRecordInfo* pRecInfo = NULL;
	hr = LoadRegTypeLib(LIBID_GraphicsLibrary, 1, 0, GetUserDefaultLCID(), &pTypelib);
	_ASSERT(SUCCEEDED(hr) && pTypelib);
	hr = pTypelib->GetTypeInfoOfGuid(__uuidof(PolyPoint), &pTypeInfo);
	_ASSERT(SUCCEEDED(hr) && pTypeInfo);
	hr = GetRecordInfoFromTypeInfo(pTypeInfo, &pRecInfo);
	_ASSERT(SUCCEEDED(hr) && pRecInfo);
	pTypeInfo->Release();
	pTypelib->Release();

	std::vector<POINT> points = { { 1, 2 }, { 100, 200 }, { 300, 400 } };
	auto psa = SafeArrayCreateVectorEx(VT_RECORD, 0, points.size(), pRecInfo);
	PolyPoint* pps;
	SafeArrayAccessData(psa, (void**)&pps);
	_ASSERT(psa);
	for (size_t i = 0; i < points.size(); ++i) {
		pps[i].x = points[i].x;
		pps[i].y = points[i].y;
	}
	pl->put_Points(psa);
	outputPoints(pl);

	ComPtr<IPersistFile> pf;
	pl->QueryInterface(IID_IPersistFile, (void**)&pf);
	pf->Save(kFileName, TRUE);
	pf->SaveCompleted(kFileName);
	return 0;
}

int PolylineTest::readPersistFile()
{
	ComPtr<IPolyline> pl;
	ComPtr<IPersistFile> pf;
	auto hr = CoCreateInstance(CLSID_PolylineObj, NULL, CLSCTX_INPROC_SERVER,
		IID_IPolyline, (void**)&pl);
	if (FAILED(hr)) {
		return -1;
	}
	pl->QueryInterface(IID_IPersistFile, (void**)&pf);
	hr = pf->Load(kFileName, STGM_READ | STGM_SHARE_EXCLUSIVE);
	if (FAILED(hr)) {
		TRACE("load persist file failed\n");
		return -1;
	}
	outputPoints(pl);
	return 0;
}

int PolylineTest::writeFileMoniker()
{
	ComPtr<IMoniker> moniker;
	auto hr = CreateFileMoniker(kFileName, &moniker);
	if (FAILED(hr)) {
		return -1;
	}
	IBindCtx* pbc;
	CreateBindCtx(0, &pbc);
	ComPtr<IPolyline> polyline;
	hr = moniker->BindToObject(pbc, NULL, IID_IPolyline, (void**)&polyline);
	if (FAILED(hr)) {
		return -1;
	}
	polyline->put_Color(RGB(0xff, 0x00, 0x00));
	COLORREF value;
	polyline->get_Color(&value);
	assert(value == RGB(0xff, 0x00, 0x00));

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

int PolylineTest::readFileMoniker()
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
	ComPtr<IPolyline> polyline;
	hr = moniker->BindToObject(pbc, NULL, IID_IPolyline, (void**)&polyline);
	if (FAILED(hr)) {
		return -1;
	}
	ComPtr<IPolyline> polyline2;
	hr = moniker->BindToObject(pbc, NULL, IID_IPolyline, (void**)&polyline2);
	if (FAILED(hr)) {
		return -1;
	}
	outputPoints(polyline);
	outputPoints(polyline2);
	polyline->put_Color(RGB(0xff, 0x00, 0x00));
	COLORREF value;
	polyline->get_Color(&value);
	assert(value == RGB(0xff, 0x00, 0x00));
	return 0;
}

void PolylineTest::outputPoints(ComPtr<IPolyline>& pl)
{
	PolyPoint* pps;
	SAFEARRAY* ppo;
	pl->get_Points(&ppo);
	SafeArrayAccessData(ppo, (void**)&pps);
	for (size_t i = 0; i < ppo->rgsabound[0].cElements; ++i) {
		TRACE("point[%d] (%d, %d)\n", i, pps[i].x, pps[i].y);
	}
}

int PolylineTest::testCompoundFile() {
	if (FAILED(writeCompoundFile())) {
		return -1;
	}
	if (FAILED(readCompundFile())) {
		return -1;
	}
	return 0;
}

int PolylineTest::writeCompoundFile()
{
	ComPtr<IStorage> pStorage;
	ComPtr<IStream> pStream;
	auto hr = StgCreateStorageEx(kFileName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
	if (FAILED(hr))
		return hr;
	hr = pStorage->CreateStream(kStreamName, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		0, 0, &pStream);
	if (FAILED(hr))
		return hr;

	ULARGE_INTEGER ui;
	ui.QuadPart = 10;
	pStream->SetSize(ui);
	ULONG cb;
	hr = pStream->Write(kData, sizeof(int) * _countof(kData), &cb);
	if (FAILED(hr))
		return hr;
	pStorage->Commit(STGC_OVERWRITE);
	return 0;
}

int PolylineTest::readCompundFile()
{
	assert(StgIsStorageFile(kFileName) == S_OK);
	ComPtr<IStorage> pStorage;
	ComPtr<IStream> pStream;
	auto hr = StgOpenStorageEx(kFileName,
		STGM_READ | STGM_SHARE_EXCLUSIVE | STGM_DIRECT, STGFMT_STORAGE, 0, NULL, 0, IID_IStorage, (void**)&pStorage);
	if (FAILED(hr))
		return hr;
	hr = pStorage->OpenStream(kStreamName, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pStream);
	if (FAILED(hr))
		return hr;

	ULARGE_INTEGER ui;
	ui.QuadPart = 10;
	pStream->SetSize(ui);
	int keke[6];
	ULONG cb;
	hr = pStream->Read(keke, sizeof(int) * _countof(keke), &cb);
	if (FAILED(hr))
		return hr;
	for (int i = 0; i < _countof(kData); i++) {
		assert(keke[i] == kData[i]);
	}
	return 0;
}

