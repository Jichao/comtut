#include "stdafx.h"
#include "IEnumConnectionPointsImpl.h"

IEnumConnectionPointsImpl::IEnumConnectionPointsImpl(const std::vector<IConnectionPoint*>& connectionPoints)
{
	index_ = 0;
	connectionPoints_ = connectionPoints;
}

IEnumConnectionPointsImpl::~IEnumConnectionPointsImpl()
{
}

HRESULT STDMETHODCALLTYPE IEnumConnectionPointsImpl::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IUnknown || riid == IID_IEnumConnectionPoints) {
		*ppvObject = (IEnumConnectionPoints*)this;
	}
	if (*ppvObject) {
		AddRef();
		return S_OK;
	}
	else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE IEnumConnectionPointsImpl::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE IEnumConnectionPointsImpl::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumConnectionPointsImpl::Next(/* [in] */ ULONG cConnections,
	/* [length_is][size_is][out] */ LPCONNECTIONPOINT *ppCP,
	/* [out] */ ULONG *pcFetched)
{
	ULONG len = std::max<ULONG>(cConnections, connectionPoints_.size() - index_); // [index_, connectionPoints_.size())
	*pcFetched = len;
	size_t j = 0;
	for (size_t i = index_; i < index_ + len; i++, j++) {
		ppCP[j] = connectionPoints_[i];
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE IEnumConnectionPointsImpl::Skip(/* [in] */ ULONG cConnections)
{
	index_ = std::max<ULONG>(index_ + cConnections, connectionPoints_.size() - 1);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE IEnumConnectionPointsImpl::Reset(void)
{
	index_ = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE IEnumConnectionPointsImpl::Clone(/* [out] */ __RPC__deref_out_opt IEnumConnectionPoints **ppEnum)
{
	*ppEnum = new IEnumConnectionPointsImpl(connectionPoints_);
	return S_OK;
}
