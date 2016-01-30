#pragma once

class IMath : public IUnknown {
public:
	virtual HRESULT Add(int a, int b, int* reult) = 0;
	virtual HRESULT Sub(int a, int b, int* result) = 0;
	virtual HRESULT Mul(int a, int b, int* result) = 0;
	virtual HRESULT Div(int a, int b, int* result) = 0;
};

class IAdvanceMath : public IUnknown {
public:
	virtual HRESULT Factorial(int num, int *result) = 0;
	virtual HRESULT Fibonacci(int num, int *result) = 0;
};

// {F9AF2C22-3862-4332-B993-57919212F1F1}
DEFINE_GUID(IID_IMath,
	0xf9af2c22, 0x3862, 0x4332, 0xb9, 0x93, 0x57, 0x91, 0x92, 0x12, 0xf1, 0xf1);
// {F9AF2C22-3862-4332-B993-57919212F1F1}
DEFINE_GUID(IID_IAdvanceMath,
	0xf9af2c22, 0x3862, 0x4332, 0xb9, 0x93, 0x57, 0x91, 0x92, 0x12, 0xf1, 0xf1);
// {E8CD884E-6D12-4067-95DA-C475A671D00F}
DEFINE_GUID(CLSID_Math,
	0xe8cd884e, 0x6d12, 0x4067, 0x95, 0xda, 0xc4, 0x75, 0xa6, 0x71, 0xd0, 0xf);

