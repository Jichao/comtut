#pragma once

#include "FxClassFactoryImpl.h"

class DllModule
{
public:
	DllModule();
	~DllModule();

	BOOL APIENTRY DllMain(HMODULE hModule,
		DWORD  ul_reason_for_call,
		LPVOID lpReserved
		);
	HRESULT DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID FAR* ppv);
	HRESULT DllCanUnloadNow(void);
	HRESULT DllRegisterServer(void);
	HRESULT DllUnregisterServer(void);

private:
	HMODULE hMod_;
};

