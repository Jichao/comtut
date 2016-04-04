#pragma once

#include <map>

//template <typename T>
//class FxClassFactoryImpl : public IClassFactory {
//public:
//	static FxClassFactoryImpl<T>* Create() {
//		return new FxClassFactoryImpl<T>();
//	}
//
//	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) {
//		*ppvObject = NULL;
//		if (riid == IID_IClassFactory || riid == IID_IUnknown) {
//			*ppvObject = (IClassFactory*)this;
//			return S_OK;
//		} else {
//			return E_NOINTERFACE;
//		}
//	}
//
//	virtual ULONG STDMETHODCALLTYPE AddRef(void) {
//		return InterlockedIncrement(&count_);
//	}
//
//	virtual ULONG STDMETHODCALLTYPE Release(void) {
//		LONG count = InterlockedDecrement(&count_);
//		if (count == 0) {
//			delete this;
//		}
//		return count
//	}
//
//	virtual /* [local] */ HRESULT STDMETHODCALLTYPE CreateInstance(
//		/* [annotation][unique][in] */
//		_In_opt_  IUnknown *pUnkOuter,
//		/* [annotation][in] */
//		_In_  REFIID riid,
//		/* [annotation][iid_is][out] */
//		_COM_Outptr_  void **ppvObject) {
//		T* obj = new T();
//		auto hr = obj->QueryInterface(riid, ppvObject);
//		if (S_OK != hr) {
//			delete obj;
//			*ppvObject = NULL;
//			return hr;
//		}
//		return S_OK;
//	}
//
//	virtual /* [local] */ HRESULT STDMETHODCALLTYPE LockServer(
//		/* [in] */ BOOL fLock) {
//		return S_OK;
//	}
//
//private:
//	volatile LONG count_;
//};
//
//class FxClassFactoryMap
//{
//	typedef void(*CreatorFuncPtr)();
//
//public:
//	static void RegistryFactory(const CLSID& clsid, CreatorFuncPtr func) {
//		s_factoryMap[clsid] = func;
//	}
//	static IClassFactory* CreateFactory(const CLSID& clsid) {
//		if (s_factoryMap.count(clsid)) {
//			return (IClassFactory*)(s_factoryMap[clsid]());
//		}
//		return nullptr;
//	}
//private:
//	static std::map<CLSID, CreatorFuncPtr> s_factoryMap;
//};
//
//template <CLSID* clsid, typename T>
//class FxClassFactoryRegistar
//{
//public:
//	FxClassFactoryRegistar() {
//		FxClassFactoryMap::RegistryFactory(&clsid, FxClassFactoryImpl<T>::Create);
//	}
//};
//
