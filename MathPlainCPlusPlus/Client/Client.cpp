// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Objbase.h>
#include <initguid.h>
#include <iostream>
#include "../MathPlainCPlusPlus/IMath.h"
#include "../AttributeVersion/_attributeversion.h"
#include "../AttributeVersion/_attributeversion_i.c"

void dispCallWithRet() {
	IDispatch* obj = NULL;
	auto hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&obj);
	DISPPARAMS disp = { 0 };

	VARIANT arg1;
	VariantInit(&arg1);
	arg1.vt = VT_INT;
	arg1.intVal = 3;

	VARIANT arg2;
	VariantInit(&arg2);
	arg2.vt = VT_INT;
	arg2.intVal = 4;

	VARIANTARG args[] = { arg1, arg2};
	disp.cArgs = 2;
	disp.rgvarg = args;
	disp.cNamedArgs = 0;
	disp.rgdispidNamedArgs = NULL;

	VARIANT ret;
	VariantInit(&ret);
	hr = obj->Invoke(1, IID_NULL, 0, DISPATCH_METHOD, &disp, &ret, NULL, NULL);
	obj->Release();
	printf("%d\n", ret.intVal);
}

//call haha
void dispCallWithoutArg() {
	IDispatch* obj = NULL;
	auto hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&obj);
	DISPPARAMS disp = { 0 };
	hr = obj->Invoke(5, IID_NULL, 0, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	obj->Release();
}

void dispCallWithPointArg() {
	IDispatch* obj = NULL;
	auto hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&obj);
	DISPPARAMS disp = { 0 };

	VARIANT arg1;
	VariantInit(&arg1);
	arg1.vt = VT_INT;
	arg1.intVal = 3;

	VARIANT arg2;
	VariantInit(&arg2);
	arg2.vt = VT_INT;
	arg2.intVal = 4;

	int a;
	VARIANT arg3;
	VariantInit(&arg3);
	arg3.vt = VT_I4 | VT_BYREF;
	arg3.pintVal = &a;


	VARIANTARG args[] = { arg3, arg2, arg1 };
	disp.cArgs = 3;
	disp.rgvarg = args;
	disp.cNamedArgs = 0;
	disp.rgdispidNamedArgs = NULL;

	hr = obj->Invoke(4, IID_NULL, 0, DISPATCH_METHOD, &disp, NULL, NULL, NULL);
	obj->Release();
}

void normalTest() {
	IMath* math = nullptr;
	auto hr = CoCreateInstance(CLSID_Math, NULL, CLSCTX_INPROC_SERVER, IID_IMath, (void**)&math);
	int result = 0;
	math->Add(1, 2, &result);
	std::cout << result;
	math->Release();
}

void attributeTest() {
	IMyMath* mm = nullptr;
	auto hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void**)&mm);
	int result = 0;
	mm->Add(1, 2, &result);
	std::cout << result;
	mm->Release();
}

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	normalTest();
	attributeTest();
	dispCallWithRet();
	dispCallWithoutArg();
	dispCallWithPointArg();
	CoUninitialize();
	return 0;
}
