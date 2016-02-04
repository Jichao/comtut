// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "String_h.h"
#include "StringObjFactory.h"
#pragma comment(lib, "Shlwapi.lib")

HMODULE g_hMod = NULL;

namespace {
	bool RegSetString(HKEY key, LPCTSTR subkey, LPCTSTR name, LPCTSTR value) {
		HKEY hKey = NULL;
		auto hr = RegCreateKeyEx(key, subkey, NULL, NULL, NULL, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		if (hr != ERROR_SUCCESS)
			return false;
		hr = RegSetValueEx(hKey, name, NULL, REG_SZ, (const BYTE*)value, (wcslen(value) + 1) * sizeof(WCHAR));
		if (hr != ERROR_SUCCESS)
			return false;
		return true;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hMod = hModule;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

STDAPI  DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID FAR* ppv) {
	MessageBox(NULL, NULL, NULL, NULL);
	if (rclsid != CLSID_StringObj) {
		return E_NOINTERFACE;
	}
	StringObjFactory* factory = new StringObjFactory();
	auto hr = factory->QueryInterface(riid, ppv);
	if (S_OK != hr) {
		delete factory;
		*ppv = NULL;
		return hr;
	}
	factory->AddRef();
	return hr;
}

STDAPI  DllCanUnloadNow(void) {
	return S_OK;
}
STDAPI DllRegisterServer(void) {
	//register server
	WCHAR path[MAX_PATH];
	GetModuleFileName(g_hMod, path, MAX_PATH);
	auto ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{B1D59117-CC63-483B-9A19-240A5A19ED67}\\InprocServer32",
		NULL, path);
	if (!ret)
		return E_FAIL;
	ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{B1D59117-CC63-483B-9A19-240A5A19ED67}\\InprocServer32",
		L"ThreadingModel", L"Apartment");
	if (!ret)
		return E_FAIL;
	//register typelib
	auto hr = RegisterTypeLib(NULL, path, NULL);
	return S_OK;
}

STDAPI DllUnregisterServer(void) {
	return SHDeleteKey(HKEY_CLASSES_ROOT, L"CLSID\\{B1D59117-CC63-483B-9A19-240A5A19ED67}");
}
