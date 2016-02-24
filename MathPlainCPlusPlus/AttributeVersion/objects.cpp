#include "stdafx.h"
#include "base/trace.h"
#include "objects.h"

HRESULT MyMath::Div(int a, int b, int* result)
{
	*result = a / b;
	return S_OK;
}

HRESULT MyMath::Mul(int a, int b, int* result)
{
	*result = a * b;
	return S_OK;
}

HRESULT MyMath::Sub(int a, int b, int* result)
{
	*result = a - b;
	return S_OK;
}

HRESULT MyMath::Add(int a, int b, int* result)
{
	*result = a + b;
	return S_OK;
}

HRESULT MyMath::TripleAdd(int a, int b, int* c)
{
	TRACE("result = %d\n", a + b + *c);
	return S_OK;
}

HRESULT MyMath::Haha()
{
	MessageBox(NULL, L"hahahaha", 0, 0);
	return S_OK;
}
