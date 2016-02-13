#pragma once
#include "OCIdl.h"
#include <vector>

template <typename IT>
class ConnectionPointImpl :
	public IConnectionPoint
{
public:
	ConnectionPointImpl(IID interfaceIId, IConnectionPointContainer* cpc) {
		cpc_ = cpc;
		if (cpc_)
			cpc_->AddRef();
		count_ = 0;
		interfaceIID_ = interfaceIId;
	}
	~ConnectionPointImpl() {
		if (cpc_) {
			cpc_->Release();
		}
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
		*ppCPC = cpc_;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Advise(
		/* [in] */ __RPC__in_opt IUnknown *pUnkSink,
		/* [out] */ __RPC__out DWORD *pdwCookie) {
		pUnkSink->AddRef();
		*pdwCookie = clients_.size();
		IT* eventPtr = nullptr;
		pUnkSink->QueryInterface(interfaceIID_, (void**)&eventPtr);
		clients_.push_back(eventPtr);
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Unadvise(
		/* [in] */ DWORD dwCookie) {
		clients_[dwCookie]->Release();
		clients_[dwCookie] = nullptr;
		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumConnections(
		/* [out] */ __RPC__deref_out_opt IEnumConnections **ppEnum) {
		return E_NOTIMPL;
	}

	std::vector<IT*> clients_;
private:
	volatile long count_;
	IConnectionPointContainer* cpc_;
	IID interfaceIID_;
};

