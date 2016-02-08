// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Objbase.h>
#include <initguid.h>
#include <iostream>
#include "../MathPlainCPlusPlus/IMath.h"
int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	IMath* math = nullptr;
	auto hr = CoCreateInstance(CLSID_Math, NULL, CLSCTX_INPROC_SERVER, IID_IMath, (void**)&math);
	int result = 0;
	math->Add(1, 2, &result);
	std::cout << result;
	CoUninitialize();
	return 0;
}

