#pragma once
#include "base/ComPtr.h"

class WordTest : public IAdviseSink
{
public:
	WordTest();
	~WordTest();
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual /* [local] */ void STDMETHODCALLTYPE OnDataChange(
		/* [annotation][unique][in] */
		_In_  FORMATETC *pFormatetc,
		/* [annotation][unique][in] */
		_In_  STGMEDIUM *pStgmed) override;

	virtual /* [local] */ void STDMETHODCALLTYPE OnViewChange(
		/* [in] */ DWORD dwAspect,
		/* [in] */ LONG lindex) override;

	virtual /* [local] */ void STDMETHODCALLTYPE OnRename(
		/* [annotation][in] */
		_In_  IMoniker *pmk) override;

	virtual /* [local] */ void STDMETHODCALLTYPE OnSave(void) override;

	virtual /* [local] */ void STDMETHODCALLTYPE OnClose(void) override;

	void testWord();
private:
	volatile long count_;
};
