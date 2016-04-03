// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "viewserver_h.h"
#include "ViewServerFactory.h"

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

	HRESULT RegisterServer(const CLSID& clsid, const std::wstring& progId, int version) {
		WCHAR path[MAX_PATH];
		GetModuleFileName(g_hMod, path, MAX_PATH);
		WCHAR clsidStr[200];
		StringFromGUID2(clsid, clsidStr, 200);
		WCHAR keyName[200];
		StringCchPrintf(keyName, 200, L"CLSID\\%s\\InprocServer32", clsidStr);
		std::wstring progIdVer = progId + L"." + std::to_wstring(version);
		auto ret = RegSetString(HKEY_CLASSES_ROOT, keyName, NULL, path);
		if (!ret)
			return E_FAIL;

		ret = RegSetString(HKEY_CLASSES_ROOT, keyName, L"ThreadingModel", L"Apartment");
		if (!ret)
			return E_FAIL;

		StringCchPrintf(keyName, 200, L"CLSID\\%s\\ProgID", clsidStr);
		ret = RegSetString(HKEY_CLASSES_ROOT, keyName, NULL, progIdVer.c_str());
		if (!ret)
			return E_FAIL;

		StringCchPrintf(keyName, 200, L"CLSID\\%s\\VersionIndependentProgID", clsidStr);
		ret = RegSetString(HKEY_CLASSES_ROOT, keyName, NULL, progId.c_str());
		if (!ret)
			return E_FAIL;

		StringCchPrintf(keyName, 200, L"%s\\CLSID", progIdVer.c_str());
		ret = RegSetString(HKEY_CLASSES_ROOT, keyName, NULL, clsidStr);
		if (!ret)
			return E_FAIL;

		StringCchPrintf(keyName, 200, L"%s\\CLSID", progId.c_str());
		ret = RegSetString(HKEY_CLASSES_ROOT, keyName, NULL, clsidStr);
		if (!ret)
			return E_FAIL;

		StringCchPrintf(keyName, 200, L"%s\\CurVer", progId.c_str());
		ret = RegSetString(HKEY_CLASSES_ROOT, keyName, NULL, progIdVer.c_str());
		if (!ret)
			return E_FAIL;
		return S_OK;
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
	if (rclsid != CLSID_ViewServer) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	if (rclsid == CLSID_ViewServer) {
		ViewServerFactory* factory = new ViewServerFactory();
		auto hr = factory->QueryInterface(riid, ppv);
		if (S_OK != hr) {
			delete factory;
			*ppv = NULL;
			return hr;
		}
		factory->AddRef();
		return hr;
	} 
	return E_FAIL;
}

STDAPI  DllCanUnloadNow(void) {
	return S_OK;
}
STDAPI DllRegisterServer(void) {
	WCHAR path[MAX_PATH];
	GetModuleFileName(g_hMod, path, MAX_PATH);
	RegisterServer(CLSID_ViewServer, L"ViewServerLib.ViewServer", 1);
	ITypeLib* typeLib = nullptr;
	auto hr = LoadTypeLib(path, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = RegisterTypeLib(typeLib, path, NULL);
	return hr;
}

STDAPI DllUnregisterServer(void) {
	WCHAR clsidStr[200];
	StringFromGUID2(CLSID_ViewServer, clsidStr, 200);
	WCHAR keyname[200];
	StringCchPrintf(keyname, 200, L"CLSID\\%s", clsidStr);
	SHDeleteKey(HKEY_CLASSES_ROOT, keyname);
	UnRegisterTypeLib(LIBID_ViewServerLibrary, 1, 0, GetSystemDefaultLCID(), SYS_WIN32);
	return S_OK;
}
