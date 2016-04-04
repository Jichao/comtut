#include "stdafx.h"
#include "DllModule.h"



//DllModule::DllModule()
//{
//}
//
//DllModule::~DllModule()
//{
//}
//
//BOOL APIENTRY DllModule::DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
//{
//	switch (ul_reason_for_call)
//	{
//	case DLL_PROCESS_ATTACH:
//		hMod_ = hModule;
//	case DLL_THREAD_ATTACH:
//	case DLL_THREAD_DETACH:
//	case DLL_PROCESS_DETACH:
//		break;
//	}
//	return TRUE;
//}
//
//HRESULT DllModule::DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID FAR* ppv)
//{
//	auto factory = FxClassFactoryMap::CreateFactory(rclsid);
//	if (!factory) {
//		return E_FAIL;
//	}
//	auto hr = factory->QueryInterface(riid, ppv);
//	if (S_OK != hr) {
//		delete factory;
//		*ppv = NULL;
//		return hr;
//	}
//	factory->AddRef();
//	return hr;
//}
//
//HRESULT DllModule::DllCanUnloadNow(void)
//{
//	return S_OK;
//}
//
//HRESULT DllModule::DllRegisterServer(void)
//{
//	WCHAR path[MAX_PATH];
//	GetModuleFileName(hMod_, path, MAX_PATH);
//	RegisterServer(CLSID_PolylineObj, L"Graphics.Polyline", 1);
//	ITypeLib* typeLib = nullptr;
//	auto hr = LoadTypeLib(path, &typeLib);
//	if (hr != S_OK) {
//		return hr;
//	}
//	hr = RegisterTypeLib(typeLib, path, NULL);
//	return hr;
//}
//
//HRESULT DllModule::DllUnregisterServer(void)
//{
//	WCHAR clsidStr[200];
//	StringFromGUID2(CLSID_PolylineObj, clsidStr, 200);
//	WCHAR keyname[200];
//	StringCchPrintf(keyname, 200, L"CLSID\\%s", clsidStr);
//	SHDeleteKey(HKEY_CLASSES_ROOT, keyname);
//	UnRegisterTypeLib(LIBID_GraphicsLibrary, 1, 0, GetSystemDefaultLCID(), SYS_WIN32);
//	return S_OK;
//}
