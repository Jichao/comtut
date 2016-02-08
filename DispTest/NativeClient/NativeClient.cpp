// NativeClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../DispTest/String_h.h"
#include "../DispTest/string_i.c"
void normalCall()
{
	CoInitialize(NULL);
	IString* obj = nullptr;
	auto hr = CoCreateInstance(CLSID_StringObj, NULL, CLSCTX_INPROC_SERVER, IID_IString, (void**)&obj);
	BSTR result = 0;
	obj->Concat(SysAllocString(L"keke"), SysAllocString(L"haha"), &result);
	obj->Release();
	CoUninitialize();
}

void dispCall() {
	CoInitialize(NULL);
	IDispatch* obj = NULL;
	auto hr = CoCreateInstance(CLSID_StringObj, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&obj);
	BSTR result = 0;
	DISPPARAMS disp = { 0 };
	VARIANT arg1;
	VariantInit(&arg1);
	arg1.vt = VT_BSTR;
	arg1.bstrVal = SysAllocString(L"hello");
	VARIANT arg2;
	VariantInit(&arg2);
	arg2.vt = VT_BSTR;
	arg2.bstrVal = SysAllocString(L"world");

	VARIANTARG args[] = { arg1, arg2 };
	DISPID dispIds[] = { 0, 1 };
	disp.cArgs = 2;
	disp.cNamedArgs = 2;
	disp.rgdispidNamedArgs = dispIds;
	disp.rgvarg = args;
	VARIANT ret;
	VariantInit(&ret);
	obj->Invoke(1, IID_NULL, 0, INVOKE_FUNC, &disp, &ret, NULL, NULL);
	obj->Release();
	printf("%S\n", ret.bstrVal);
	CoUninitialize();
}
int _tmain(int argc, _TCHAR* argv[])
{
	dispCall();
	return 0;
}

