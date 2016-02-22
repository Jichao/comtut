#pragma once
#include "OCIdl.h"
#include <vector>
class IEnumConnectionPointsImpl :
	public IEnumConnectionPoints
{
public:
	IEnumConnectionPointsImpl(const std::vector<IConnectionPoint*>& connectionPoints);
	~IEnumConnectionPointsImpl();

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);

	ULONG STDMETHODCALLTYPE AddRef(void);

	ULONG STDMETHODCALLTYPE Release(void);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG cConnections,
		/* [length_is][size_is][out] */ LPCONNECTIONPOINT *ppCP,
		/* [out] */ ULONG *pcFetched);

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG cConnections);

	virtual HRESULT STDMETHODCALLTYPE Reset(void);

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ __RPC__deref_out_opt IEnumConnectionPoints **ppEnum);

private:
	std::vector<IConnectionPoint*> connectionPoints_;
	ULONG index_;
	volatile long count_;
};

