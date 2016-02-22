#pragma once
#include "OCIdl.h"
#include <vector>
class IEnumConnectionsImpl :
	public IEnumConnections
{
public:
	IEnumConnectionsImpl(const std::vector<CONNECTDATA>& connectionPoints);
	~IEnumConnectionsImpl();

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);

	ULONG STDMETHODCALLTYPE AddRef(void);

	ULONG STDMETHODCALLTYPE Release(void);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG cConnections,
		/* [length_is][size_is][out] */ CONNECTDATA *ppCP,
		/* [out] */ ULONG *pcFetched);

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG cConnections);

	virtual HRESULT STDMETHODCALLTYPE Reset(void);

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ __RPC__deref_out_opt IEnumConnections **ppEnum);

private:
	std::vector<CONNECTDATA> connectData_;
	ULONG index_;
	volatile long count_;
};

