#pragma once

#include <OAIdl.h>
[
	object,
	uuid("f9071835-aee8-493e-a2e0-45ad2848354e"),
	dual,
	helpstring("math interface"),
	pointer_default(unique)
]
__interface IMyMath : IDispatch
{
	[id(0)]HRESULT Add(int a, int b, [out,retval]int* reult);
	[id(1)]HRESULT Sub(int a, int b, [out,retval]int* result);
	[id(2)]HRESULT Mul(int a, int b, [out,retval]int* result);
	[id(3)]HRESULT Div(int a, int b, [out,retval]int* result);
	[id(4)]HRESULT TripleAdd(int a, int b, int* c);
	[id(5)]HRESULT Haha();
};

[
	coclass,
	threading(apartment),
	uuid("58c861b7-760a-4c1e-b7b6-8e56d1fbc9e3"),
	progid("Math.Object.1"),
	vi_progid("Math.Object.1"),
	version("1.0"),
	aggregatable(never),
	helpstring("MyMath object")
]
class MyMath : public IMyMath
{
public:
	HRESULT Add(int a, int b, int* result);
	HRESULT Sub(int a, int b, int* result);
	HRESULT Mul(int a, int b, int* result);
	HRESULT Div(int a, int b, int* result);
	HRESULT TripleAdd(int a, int b, int* c);
	HRESULT Haha();
};