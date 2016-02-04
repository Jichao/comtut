// NativeClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../DispTest/String_h.h"
#include "../DispTest/string_i.c"

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	IString* obj = nullptr;
	auto hr = CoCreateInstance(CLSID_StringObj, NULL, CLSCTX_INPROC_SERVER, IID_IString, (void**)&obj);
	BSTR result = 0;
	obj->Concat(SysAllocString(L"keke"), SysAllocString(L"haha"), &result);
	obj->Release();
	CoUninitialize();
	return 0;
}

