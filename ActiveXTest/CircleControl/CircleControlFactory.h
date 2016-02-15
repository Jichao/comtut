#pragma once

class CircleControlFactory : public IClassFactory {
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
private:
	volatile LONG count_;
};