#pragma once
#include "OCIdl.h"
#include <vector>
#include "IEnumConnectionsImpl.h"

template <typename IT>
class ConnectionPointImpl : public IConnectionPoint
{
public:
	ConnectionPointImpl(IID interfaceIId, IConnectionPointContainer* cpc) {
		cpc_ = cpc;
		count_ = 0;
		cookie_ = 0;
		interfaceIID_ = interfaceIId;
	}
	~ConnectionPointImpl() {
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) {
		*ppvObject = NULL;
		if (riid == IID_IUnknown) {
			*ppvObject = (IUnknown*)this;
		}
		else if (riid == IID_IConnectionPoint) {
			*ppvObject = (IConnectionPoint*)this;
		}
		if (*ppvObject) {
			AddRef();
			return S_OK;
		}
		else {
			return E_NOINTERFACE;
		}
	}

	virtual ULONG STDMETHODCALLTYPE AddRef(void) {
		return InterlockedIncrement(&count_);
	}
	virtual ULONG STDMETHODCALLTYPE Release(void) {
		LONG count = InterlockedDecrement(&count_);
		if (count == 0) {
			delete this;
		}
		return count;
	}

	virtual HRESULT STDMETHODCALLTYPE GetConnectionInterface(
		/* [out] */ __RPC__out IID *pIID) {
		*pIID = interfaceIID_;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetConnectionPointContainer(
		/* [out] */ __RPC__deref_out_opt IConnectionPointContainer **ppCPC) {
		cpc_->AddRef();
		*ppCPC = cpc_;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Advise(
		/* [in] */ __RPC__in_opt IUnknown *pUnkSink,
		/* [out] */ __RPC__out DWORD *pdwCookie) {
		if (!pUnkSink || !pdwCookie) {
			return E_INVALIDARG;
		}
		pUnkSink->AddRef();
		*pdwCookie = cookie_;
		cookie_++;
		CONNECTDATA cd = { pUnkSink, *pdwCookie };
		connectData_.push_back(cd);
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Unadvise(
		/* [in] */ DWORD dwCookie) {
		auto iter = std::find_if(connectData_.begin(), connectData_.end(), [dwCookie](const CONNECTDATA& cd) {
			return (dwCookie == cd.dwCookie);
		});
		if (iter != connectData_.end()) {
			connectData_.erase(iter);
			return S_OK;
		}
		return E_INVALIDARG;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumConnections(
		/* [out] */ __RPC__deref_out_opt IEnumConnections **ppEnum) {
		*ppEnum = new IEnumConnectionsImpl(connectData_);
		return S_OK;
	}

private:
	DWORD cookie_;
	std::vector<CONNECTDATA> connectData_;
	volatile long count_;
	IConnectionPointContainer* cpc_;
	IID interfaceIID_;
};

