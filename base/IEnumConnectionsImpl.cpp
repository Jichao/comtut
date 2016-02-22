#include "stdafx.h"
#include "IEnumConnectionsImpl.h"

IEnumConnectionsImpl::IEnumConnectionsImpl(const std::vector<CONNECTDATA>& connectData)
{
	index_ = 0;
	connectData_ = connectData;
}

IEnumConnectionsImpl::~IEnumConnectionsImpl()
{
}

HRESULT STDMETHODCALLTYPE IEnumConnectionsImpl::QueryInterface(REFIID riid, void **ppvObject)
{
	*ppvObject = NULL;
	if (riid == IID_IUnknown || riid == IID_IEnumConnections) {
		*ppvObject = (IEnumConnections*)this;
	}
	if (*ppvObject) {
		AddRef();
		return S_OK;
	} else {
		return E_NOINTERFACE;
	}
}

ULONG STDMETHODCALLTYPE IEnumConnectionsImpl::AddRef(void)
{
	return InterlockedIncrement(&count_);
}

ULONG STDMETHODCALLTYPE IEnumConnectionsImpl::Release(void)
{
	LONG count = InterlockedDecrement(&count_);
	if (count == 0) {
		delete this;
	}
	return count;
}

/* [local] */ HRESULT STDMETHODCALLTYPE IEnumConnectionsImpl::Next(/* [in] */ ULONG cConnections,
	/* [length_is][size_is][out] */ CONNECTDATA *cd,
	/* [out] */ ULONG *pcFetched)
{
	ULONG len = std::min<ULONG>(cConnections, connectData_.size() - index_); // [index_, connectionPoints_.size())
	*pcFetched = len;
	if (*pcFetched) {
		size_t j = 0;
		for (size_t i = index_; i < index_ + len; i++, j++) {
			cd[j] = connectData_[i];
			cd[j].pUnk->AddRef();
		}
		index_ += *pcFetched;
		return S_OK;
	}
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE IEnumConnectionsImpl::Skip(/* [in] */ ULONG cConnections)
{
	index_ = std::max<ULONG>(index_ + cConnections, connectData_.size() - 1);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE IEnumConnectionsImpl::Reset(void)
{
	index_ = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE IEnumConnectionsImpl::Clone(/* [out] */ __RPC__deref_out_opt IEnumConnections **ppEnum)
{
	*ppEnum = new IEnumConnectionsImpl(connectData_);
	return S_OK;
}
