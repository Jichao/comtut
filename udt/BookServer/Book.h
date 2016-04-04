#pragma once

#include "book_h.h"
#include "base/ComPtr.h"
#include "base/ComBSTR.h"
#include <map>

class Book : public IBook, public IPersistFile, public IOleItemContainer
{
public:
	Book();
	~Book();

	//IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	//IDispatch
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(
		/* [out] */ __RPC__out UINT *pctinfo);

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(
		/* [in] */ UINT iTInfo,
		/* [in] */ LCID lcid,
		/* [out] */ __RPC__deref_out_opt ITypeInfo **ppTInfo);

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(
		/* [in] */ __RPC__in REFIID riid,
		/* [size_is][in] */ __RPC__in_ecount_full(cNames) LPOLESTR *rgszNames,
		/* [range][in] */ __RPC__in_range(0, 16384) UINT cNames,
		/* [in] */ LCID lcid,
		/* [size_is][out] */ __RPC__out_ecount_full(cNames) DISPID *rgDispId);

	virtual /* [local] */ HRESULT STDMETHODCALLTYPE Invoke(
		/* [annotation][in] */
		_In_  DISPID dispIdMember,
		/* [annotation][in] */
		_In_  REFIID riid,
		/* [annotation][in] */
		_In_  LCID lcid,
		/* [annotation][in] */
		_In_  WORD wFlags,
		/* [annotation][out][in] */
		_In_  DISPPARAMS *pDispParams,
		/* [annotation][out] */
		_Out_opt_  VARIANT *pVarResult,
		/* [annotation][out] */
		_Out_opt_  EXCEPINFO *pExcepInfo,
		/* [annotation][out] */
		_Out_opt_  UINT *puArgErr);

	//IPersistFile
	virtual HRESULT STDMETHODCALLTYPE GetClassID(
		/* [out] */ __RPC__out CLSID *pClassID);

	virtual HRESULT STDMETHODCALLTYPE IsDirty(void);

	virtual HRESULT STDMETHODCALLTYPE Load(
		/* [in] */ __RPC__in LPCOLESTR pszFileName,
		/* [in] */ DWORD dwMode);

	virtual HRESULT STDMETHODCALLTYPE Save(
		/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName,
		/* [in] */ BOOL fRemember);

	virtual HRESULT STDMETHODCALLTYPE SaveCompleted(
		/* [unique][in] */ __RPC__in_opt LPCOLESTR pszFileName);

	virtual HRESULT STDMETHODCALLTYPE GetCurFile(
		/* [out] */ __RPC__deref_out_opt LPOLESTR *ppszFileName);

	//IBook
	HRESULT STDMETHODCALLTYPE get_pageCount(UINT32* retValue) override;
	HRESULT	STDMETHODCALLTYPE put_pageCount(UINT32 value) override;
	HRESULT STDMETHODCALLTYPE get_name(BSTR* value) override;
	HRESULT STDMETHODCALLTYPE put_name(BSTR value) override;
	HRESULT STDMETHODCALLTYPE CreateChapter(IChapter** chapter) override;
	HRESULT STDMETHODCALLTYPE GetChapter(UINT index, IChapter** chapter) override;

	//IOleContainer
	HRESULT STDMETHODCALLTYPE ParseDisplayName(IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut) override;
	HRESULT STDMETHODCALLTYPE EnumObjects(DWORD grfFlags, IEnumUnknown **ppenum);
	HRESULT STDMETHODCALLTYPE LockContainer(BOOL fLock);
	virtual HRESULT STDMETHODCALLTYPE GetObject(
		/* [in] */ __RPC__in LPOLESTR pszItem,
		/* [in] */ DWORD dwSpeedNeeded,
		/* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
		/* [in] */ __RPC__in REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out_opt void **ppvObject);

	virtual HRESULT STDMETHODCALLTYPE GetObjectStorage(
		/* [in] */ __RPC__in LPOLESTR pszItem,
		/* [unique][in] */ __RPC__in_opt IBindCtx *pbc,
		/* [in] */ __RPC__in REFIID riid,
		/* [iid_is][out] */ __RPC__deref_out_opt void **ppvStorage);

	virtual HRESULT STDMETHODCALLTYPE IsRunning(
		/* [in] */ __RPC__in LPOLESTR pszItem);

private:
	HRESULT ensureTypeInfo();
	std::wstring getChapterName(int index);
	int nameToChapterIndex(const std::wstring& name);
	void ensureFirstStorage();

private:
	std::vector<ComPtr<IChapter>> chapters_;
	ITypeInfo* typeInfo_;
	bool dirty_;
	volatile long count_;
	int pageCount_;
	std::wstring filePath_;
	ComPtr<IStorage> pStorage_;
	ComPtr<IStream> pStream_;
	ComBSTR bookName_;
};
