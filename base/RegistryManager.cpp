#include "stdafx.h"
#include "RegistryManager.h"

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

	HRESULT RegisterServer(HMODULE hMod, const CLSID& clsid, const std::wstring& progId, int version) {
		WCHAR path[MAX_PATH];
		GetModuleFileName(hMod, path, MAX_PATH);
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

RegistryManager::RegistryManager()
{
}

RegistryManager::~RegistryManager()
{
}

void RegistryManager::registry(HINSTANCE hInst, UINT resId)
{
		
}

void RegistryManager::unregistry(HINSTANCE hInst, UINT resId)
{

}
