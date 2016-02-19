// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "CircleAvatar_h.h"
#include "CircleControlFactory.h"

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
	if (rclsid != CLSID_CircleAvatar) {
		return E_NOINTERFACE;
	}
	CircleAvatarFactory* factory = new CircleAvatarFactory();
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
	auto ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\InprocServer32",
		NULL, path);
	if (!ret)
		return E_FAIL;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\InprocServer32",
		L"ThreadingModel", L"Apartment");
	if (!ret)
		return E_FAIL;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\ProgID",
		NULL, L"CircleControl.CircleControl.1");
	if (!ret)
		return E_FAIL;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\VersionIndependentProgID",
		NULL, L"CircleControl.CircleControl");
	if (!ret)
		return E_FAIL;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\TypeLib",
		NULL, L"{E9D304EC-552C-4D89-9804-7AB9E45FEF32}");
	if (!ret)
		return E_FAIL;

	HKEY hKey = NULL;
	auto hr = RegCreateKeyEx(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\Programmable",
		NULL, NULL, NULL, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (hr != ERROR_SUCCESS)
		return hr;

	hr = RegCreateKeyEx(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\Control",
		NULL, NULL, NULL, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (hr != ERROR_SUCCESS)
		return hr;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\Version",
		NULL, L"1.0");
	if (!ret)
		return E_FAIL;

	WCHAR pathRsrc[MAX_PATH + 100];
	StringCchPrintf(pathRsrc, MAX_PATH + 100, L"%s, 101", path);
	hr = RegSetString(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}\\ToolboxBitmap32",
		NULL, pathRsrc);
	if (hr != ERROR_SUCCESS)
		return hr;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CircleControl.CircleControl.1\\CLSID",
		NULL, L"{1C797BFB-3F97-4CF8-B857-45C90028759B}");
	if (!ret)
		return E_FAIL;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CircleControl.CircleControl\\CLSID",
		NULL, L"{1C797BFB-3F97-4CF8-B857-45C90028759B}");
	if (!ret)
		return E_FAIL;

	ret = RegSetString(HKEY_CLASSES_ROOT, L"CircleControl.CircleControl\\CurVer",
		NULL, L"CircleControl.CircleControl.1");
	if (!ret)
		return E_FAIL;

	//register the typelib
	HRSRC hrsrc = FindResource(g_hMod, MAKEINTRESOURCE(1), L"TYPELIB");
	if (!hrsrc)
		return E_FAIL;
	HGLOBAL hGlobal = LoadResource(g_hMod, hrsrc);
	if (!hGlobal)
		return E_FAIL;
	auto size = SizeofResource(g_hMod, hrsrc);
	WCHAR tempDir[MAX_PATH];
	GetTempPath(MAX_PATH, tempDir);
	WCHAR tempFile[MAX_PATH];
	GetTempFileName(tempDir, L"keke", 0, tempFile);
	HANDLE hFile = CreateFile(tempFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;
	DWORD byteCount;
	if (!WriteFile(hFile, hGlobal, size, &byteCount, NULL) || byteCount != size)
		return E_FAIL;
	if (!CloseHandle(hFile))
		return E_FAIL;
	ITypeLib* typeLib = nullptr;
	hr = LoadTypeLib(tempFile, &typeLib);
	if (hr != S_OK) {
		return hr;
	}
	hr = RegisterTypeLib(typeLib, path, NULL);
	return hr;
}

STDAPI DllUnregisterServer(void) {
	return SHDeleteKey(HKEY_CLASSES_ROOT, L"CLSID\\{1C797BFB-3F97-4CF8-B857-45C90028759B}");
}
