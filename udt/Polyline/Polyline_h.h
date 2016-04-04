

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Apr 03 22:10:35 2016
 */
/* Compiler settings for Polyline.idl:
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

#ifndef __Polyline_h_h__
#define __Polyline_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPolyline_FWD_DEFINED__
#define __IPolyline_FWD_DEFINED__
typedef interface IPolyline IPolyline;

#endif 	/* __IPolyline_FWD_DEFINED__ */


#ifndef ___IPolylineEvent_FWD_DEFINED__
#define ___IPolylineEvent_FWD_DEFINED__
typedef interface _IPolylineEvent _IPolylineEvent;

#endif 	/* ___IPolylineEvent_FWD_DEFINED__ */


#ifndef __PolylineObj_FWD_DEFINED__
#define __PolylineObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class PolylineObj PolylineObj;
#else
typedef struct PolylineObj PolylineObj;
#endif /* __cplusplus */

#endif 	/* __PolylineObj_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_Polyline_0000_0000 */
/* [local] */ 

/* [uuid] */ struct  DECLSPEC_UUID("53386330-1406-425F-8264-062B13FA2D16") PolyPoint
    {
    long x;
    long y;
    } ;


extern RPC_IF_HANDLE __MIDL_itf_Polyline_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Polyline_0000_0000_v0_0_s_ifspec;

#ifndef __IPolyline_INTERFACE_DEFINED__
#define __IPolyline_INTERFACE_DEFINED__

/* interface IPolyline */
/* [unique][nonextensible][object][dual][uuid] */ 


EXTERN_C const IID IID_IPolyline;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5A09E545-E4C3-4EFA-9F42-C321441BF611")
    IPolyline : public IDispatch
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ COLORREF value) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ COLORREF *retValue) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Points( 
            /* [in] */ SAFEARRAY * values) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Points( 
            /* [retval][out] */ SAFEARRAY * *retValues) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPolylineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPolyline * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPolyline * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPolyline * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPolyline * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPolyline * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPolyline * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPolyline * This,
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
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Color )( 
            IPolyline * This,
            /* [in] */ COLORREF value);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Color )( 
            IPolyline * This,
            /* [retval][out] */ COLORREF *retValue);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Points )( 
            IPolyline * This,
            /* [in] */ SAFEARRAY * values);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Points )( 
            IPolyline * This,
            /* [retval][out] */ SAFEARRAY * *retValues);
        
        END_INTERFACE
    } IPolylineVtbl;

    interface IPolyline
    {
        CONST_VTBL struct IPolylineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPolyline_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPolyline_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPolyline_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPolyline_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPolyline_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPolyline_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPolyline_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPolyline_put_Color(This,value)	\
    ( (This)->lpVtbl -> put_Color(This,value) ) 

#define IPolyline_get_Color(This,retValue)	\
    ( (This)->lpVtbl -> get_Color(This,retValue) ) 

#define IPolyline_put_Points(This,values)	\
    ( (This)->lpVtbl -> put_Points(This,values) ) 

#define IPolyline_get_Points(This,retValues)	\
    ( (This)->lpVtbl -> get_Points(This,retValues) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPolyline_INTERFACE_DEFINED__ */



#ifndef __GraphicsLibrary_LIBRARY_DEFINED__
#define __GraphicsLibrary_LIBRARY_DEFINED__

/* library GraphicsLibrary */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_GraphicsLibrary;

#ifndef ___IPolylineEvent_DISPINTERFACE_DEFINED__
#define ___IPolylineEvent_DISPINTERFACE_DEFINED__

/* dispinterface _IPolylineEvent */
/* [uuid] */ 


EXTERN_C const IID DIID__IPolylineEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C196D98F-9E3C-4537-ABE7-522394BEDDFC")
    _IPolylineEvent : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPolylineEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IPolylineEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IPolylineEvent * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IPolylineEvent * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IPolylineEvent * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IPolylineEvent * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IPolylineEvent * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IPolylineEvent * This,
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
        
        END_INTERFACE
    } _IPolylineEventVtbl;

    interface _IPolylineEvent
    {
        CONST_VTBL struct _IPolylineEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPolylineEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IPolylineEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IPolylineEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IPolylineEvent_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IPolylineEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IPolylineEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IPolylineEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPolylineEvent_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PolylineObj;

#ifdef __cplusplus

class DECLSPEC_UUID("FB59B0D8-BA04-441D-8928-95BE137A0D87")
PolylineObj;
#endif
#endif /* __GraphicsLibrary_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


