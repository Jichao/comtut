#pragma once

#include "IMath.h"

class Math : public IMath, public IAdvanceMath 
{
public:
	virtual HRESULT Add(int a, int b, int* reult) override;
	virtual HRESULT Sub(int a, int b, int* result) override;
	virtual HRESULT Mul(int a, int b, int* result) override;
	virtual HRESULT Div(int a, int b, int* result) override;
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);
	virtual HRESULT Factorial(int num, int *result) override;
	virtual HRESULT Fibonacci(int num, int *result) override;

private:
	volatile LONG count_;
};