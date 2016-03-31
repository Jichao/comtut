#pragma once
#include <OCIdl.h>
class ChapterFactory : public IClassFactory2 {
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstance(
		/* [annotation][unique][in] */
		_In_opt_  IUnknown *pUnkOuter,
		/* [annotation][in] */
		_In_  REFIID riid,
		/* [annotation][iid_is][out] */
		_COM_Outptr_  void **ppvObject);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE LockServer(
		/* [in] */ BOOL fLock);

	virtual HRESULT STDMETHODCALLTYPE GetLicInfo(
		/* [out][in] */ __RPC__inout LICINFO *pLicInfo);

	virtual HRESULT STDMETHODCALLTYPE RequestLicKey(
		/* [in] */ DWORD dwReserved,
		/* [out] */ __RPC__deref_out_opt BSTR *pBstrKey);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstanceLic(
		/* [in] */ IUnknown *pUnkOuter,
		/* [in] */ IUnknown *pUnkReserved,
		/* [in] */ REFIID riid,
		/* [in] */ BSTR bstrKey,
		/* [iid_is][out] */ PVOID *ppvObj);

private:
	volatile LONG count_;
};