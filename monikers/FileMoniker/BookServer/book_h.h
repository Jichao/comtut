

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Fri Mar 04 23:27:57 2016
 */
/* Compiler settings for book.idl:
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

#ifndef __book_h_h__
#define __book_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISection_FWD_DEFINED__
#define __ISection_FWD_DEFINED__
typedef interface ISection ISection;

#endif 	/* __ISection_FWD_DEFINED__ */


#ifndef __IChapter_FWD_DEFINED__
#define __IChapter_FWD_DEFINED__
typedef interface IChapter IChapter;

#endif 	/* __IChapter_FWD_DEFINED__ */


#ifndef __IBook_FWD_DEFINED__
#define __IBook_FWD_DEFINED__
typedef interface IBook IBook;

#endif 	/* __IBook_FWD_DEFINED__ */


#ifndef __Book_FWD_DEFINED__
#define __Book_FWD_DEFINED__

#ifdef __cplusplus
typedef class Book Book;
#else
typedef struct Book Book;
#endif /* __cplusplus */

#endif 	/* __Book_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISection_INTERFACE_DEFINED__
#define __ISection_INTERFACE_DEFINED__

/* interface ISection */
/* [unique][nonextensible][object][dual][uuid] */ 


EXTERN_C const IID IID_ISection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("57F0CC0A-8A4F-413E-AEEC-DA9E115BDA77")
    ISection : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ISectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISection * This,
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
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            ISection * This,
            /* [retval][out] */ BSTR *val);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_name )( 
            ISection * This,
            /* [in] */ BSTR val);
        
        END_INTERFACE
    } ISectionVtbl;

    interface ISection
    {
        CONST_VTBL struct ISectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ISection_get_name(This,val)	\
    ( (This)->lpVtbl -> get_name(This,val) ) 

#define ISection_put_name(This,val)	\
    ( (This)->lpVtbl -> put_name(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISection_INTERFACE_DEFINED__ */


#ifndef __IChapter_INTERFACE_DEFINED__
#define __IChapter_INTERFACE_DEFINED__

/* interface IChapter */
/* [unique][nonextensible][object][dual][uuid] */ 


EXTERN_C const IID IID_IChapter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6829C1B-B73A-4400-9048-16D3299129B4")
    IChapter : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR val) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddSection( 
            /* [in] */ ISection *chapter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSection( 
            /* [in] */ UINT index,
            /* [out] */ ISection **chapter) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IChapterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChapter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChapter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChapter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IChapter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IChapter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IChapter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IChapter * This,
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
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            IChapter * This,
            /* [retval][out] */ BSTR *val);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_name )( 
            IChapter * This,
            /* [in] */ BSTR val);
        
        HRESULT ( STDMETHODCALLTYPE *AddSection )( 
            IChapter * This,
            /* [in] */ ISection *chapter);
        
        HRESULT ( STDMETHODCALLTYPE *GetSection )( 
            IChapter * This,
            /* [in] */ UINT index,
            /* [out] */ ISection **chapter);
        
        END_INTERFACE
    } IChapterVtbl;

    interface IChapter
    {
        CONST_VTBL struct IChapterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChapter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IChapter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IChapter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IChapter_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IChapter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IChapter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IChapter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IChapter_get_name(This,val)	\
    ( (This)->lpVtbl -> get_name(This,val) ) 

#define IChapter_put_name(This,val)	\
    ( (This)->lpVtbl -> put_name(This,val) ) 

#define IChapter_AddSection(This,chapter)	\
    ( (This)->lpVtbl -> AddSection(This,chapter) ) 

#define IChapter_GetSection(This,index,chapter)	\
    ( (This)->lpVtbl -> GetSection(This,index,chapter) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IChapter_INTERFACE_DEFINED__ */


#ifndef __IBook_INTERFACE_DEFINED__
#define __IBook_INTERFACE_DEFINED__

/* interface IBook */
/* [unique][nonextensible][object][dual][uuid] */ 


EXTERN_C const IID IID_IBook;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1B6605F-FD40-4B6C-8625-9E86EE227C8D")
    IBook : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_pageCount( 
            /* [retval][out] */ UINT32 *retValue) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_name( 
            /* [in] */ BSTR val) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddChapter( 
            /* [in] */ IChapter *chapter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetChapter( 
            /* [in] */ UINT index,
            /* [out] */ IChapter **chapter) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IBookVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBook * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBook * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBook * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBook * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBook * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBook * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBook * This,
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
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pageCount )( 
            IBook * This,
            /* [retval][out] */ UINT32 *retValue);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            IBook * This,
            /* [retval][out] */ BSTR *val);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_name )( 
            IBook * This,
            /* [in] */ BSTR val);
        
        HRESULT ( STDMETHODCALLTYPE *AddChapter )( 
            IBook * This,
            /* [in] */ IChapter *chapter);
        
        HRESULT ( STDMETHODCALLTYPE *GetChapter )( 
            IBook * This,
            /* [in] */ UINT index,
            /* [out] */ IChapter **chapter);
        
        END_INTERFACE
    } IBookVtbl;

    interface IBook
    {
        CONST_VTBL struct IBookVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBook_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBook_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBook_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBook_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBook_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBook_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBook_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBook_get_pageCount(This,retValue)	\
    ( (This)->lpVtbl -> get_pageCount(This,retValue) ) 

#define IBook_get_name(This,val)	\
    ( (This)->lpVtbl -> get_name(This,val) ) 

#define IBook_put_name(This,val)	\
    ( (This)->lpVtbl -> put_name(This,val) ) 

#define IBook_AddChapter(This,chapter)	\
    ( (This)->lpVtbl -> AddChapter(This,chapter) ) 

#define IBook_GetChapter(This,index,chapter)	\
    ( (This)->lpVtbl -> GetChapter(This,index,chapter) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBook_INTERFACE_DEFINED__ */



#ifndef __BookLibrary_LIBRARY_DEFINED__
#define __BookLibrary_LIBRARY_DEFINED__

/* library BookLibrary */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_BookLibrary;

EXTERN_C const CLSID CLSID_Book;

#ifdef __cplusplus

class DECLSPEC_UUID("F837DC51-3E9F-4DC2-B342-647E70C07F33")
Book;
#endif
#endif /* __BookLibrary_LIBRARY_DEFINED__ */

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


