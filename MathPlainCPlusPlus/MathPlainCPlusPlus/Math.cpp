#include "stdafx.h"
#include "Math.h"
#include <initguid.h>

// {F9AF2C22-3862-4332-B993-57919212F1F1}
DEFINE_GUID(IID_IMath,
	0xf9af2c22, 0x3862, 0x4332, 0xb9, 0x93, 0x57, 0x91, 0x92, 0x12, 0xf1, 0xf1);
// {F9AF2C22-3862-4332-B993-57919212F1F1}
DEFINE_GUID(IID_IAdvanceMath,
	0xf9af2c22, 0x3862, 0x4332, 0xb9, 0x93, 0x57, 0x91, 0x92, 0x12, 0xf1, 0xf1);
// {E8CD884E-6D12-4067-95DA-C475A671D00F}
DEFINE_GUID(CLSID_Math,
	0xe8cd884e, 0x6d12, 0x4067, 0x95, 0xda, 0xc4, 0x75, 0xa6, 0x71, 0xd0, 0xf);

namespace {
	int fib(int n) {
		if (n == 1 || n == 2)
			return 1;
		else
			return fib(n - 1) + fib(n - 2);
	}
	int fac(int n) {
		if (n == 1)
			return 1;
		else
			return n * fac(n - 1);
	}
}

HRESULT Math::Add(int a, int b, int* result)
{
	*result = a + b;
	return S_OK;
}

HRESULT Math::Sub(int a, int b, int* result)
{
	*result = a - b;
	return S_OK;
}

HRESULT Math::Mul(int a, int b, int* result)
{
	*result = a * b;
	return S_OK;
}

HRESULT Math::Div(int a, int b, int* result)
{
	if (b == 0) {
		return E_INVALIDARG;
	}
	*result = a / b;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE Math::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IMath) {
		*ppvObject = (IMath*)this;
	} else if (riid == IID_IAdvanceMath) {
		*ppvObject = (IAdvanceMath*)this;
	} else if (riid == IID_IUnknown) {
		*ppvObject = (IMath*)this;
	}
	if (*ppvObject) {
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE Math::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE Math::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

HRESULT Math::Factorial(int num, int *result)
{
	*result = fac(num);
	return S_OK;
}

HRESULT Math::Fibonacci(int num, int *result)
{
	*result = fib(num);
	return S_OK;
}
