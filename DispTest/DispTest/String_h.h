

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Feb 07 20:43:04 2016
 */
/* Compiler settings for String.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __String_h_h__
#define __String_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IString_FWD_DEFINED__
#define __IString_FWD_DEFINED__
typedef interface IString IString;

#endif 	/* __IString_FWD_DEFINED__ */


#ifndef __StringObj_FWD_DEFINED__
#define __StringObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class StringObj StringObj;
#else
typedef struct StringObj StringObj;
#endif /* __cplusplus */

#endif 	/* __StringObj_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IString_INTERFACE_DEFINED__
#define __IString_INTERFACE_DEFINED__

/* interface IString */
/* [unique][nonextensible][object][dual][uuid] */ 


EXTERN_C const IID IID_IString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A3A558F8-EDAA-487A-8E83-CDBFC4069165")
    IString : public IDispatch
    {
    public:
        virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE Concat( 
            /* [in] */ BSTR str1,
            /* [in] */ BSTR str2,
            /* [retval][out] */ BSTR *result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IString * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IString * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IString * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IString * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IString * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IString * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IString * This,
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
        
        /* [id][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Concat )( 
            IString * This,
            /* [in] */ BSTR str1,
            /* [in] */ BSTR str2,
            /* [retval][out] */ BSTR *result);
        
        END_INTERFACE
    } IStringVtbl;

    interface IString
    {
        CONST_VTBL struct IStringVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IString_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IString_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IString_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IString_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IString_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IString_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IString_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IString_Concat(This,str1,str2,result)	\
    ( (This)->lpVtbl -> Concat(This,str1,str2,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IString_INTERFACE_DEFINED__ */



#ifndef __StringLib_LIBRARY_DEFINED__
#define __StringLib_LIBRARY_DEFINED__

/* library StringLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_StringLib;

EXTERN_C const CLSID CLSID_StringObj;

#ifdef __cplusplus

class DECLSPEC_UUID("B1D59117-CC63-483B-9A19-240A5A19ED67")
StringObj;
#endif
#endif /* __StringLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


