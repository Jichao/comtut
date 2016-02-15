#pragma once

#include <OCIdl.h>

template <typename T, typename Base>
class EnumerationImpl : public Base {
public:
	
	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ ULONG cConnections,
		/* [length_is][size_is][out] */ T* rgcd,
		/* [out] */ ULONG *pcFetched) {

	}

	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ ULONG cConnections) {

	}

	virtual HRESULT STDMETHODCALLTYPE Reset(void) {

	}

	virtual HRESULT STDMETHODCALLTYPE Clone(
		/* [out] */ __RPC__deref_out_opt IEnumConnections **ppEnum) {

	}
private:
};
