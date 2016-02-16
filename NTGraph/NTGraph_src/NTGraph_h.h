

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Feb 15 16:09:35 2016
 */
/* Compiler settings for NTGraph.odl:
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


#ifndef __NTGraph_h_h__
#define __NTGraph_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DNTGraph_FWD_DEFINED__
#define ___DNTGraph_FWD_DEFINED__
typedef interface _DNTGraph _DNTGraph;

#endif 	/* ___DNTGraph_FWD_DEFINED__ */


#ifndef ___DNTGraphEvents_FWD_DEFINED__
#define ___DNTGraphEvents_FWD_DEFINED__
typedef interface _DNTGraphEvents _DNTGraphEvents;

#endif 	/* ___DNTGraphEvents_FWD_DEFINED__ */


#ifndef __NTGraph_FWD_DEFINED__
#define __NTGraph_FWD_DEFINED__

#ifdef __cplusplus
typedef class NTGraph NTGraph;
#else
typedef struct NTGraph NTGraph;
#endif /* __cplusplus */

#endif 	/* __NTGraph_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __NTGRAPHLib_LIBRARY_DEFINED__
#define __NTGRAPHLib_LIBRARY_DEFINED__

/* library NTGRAPHLib */
/* [control][helpstring][helpfile][version][uuid] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion
typedef /* [helpstring][uuid] */  DECLSPEC_UUID("865EDFD4-9E4D-4752-907A-033D45C1C7F5") 
enum __MIDL___MIDL_itf_NTGraph_0000_0000_0001
    {
        Solid	= 0,
        Dash	= 1,
        Dot	= 2,
        DashDot	= 3,
        DashDotDot	= 4,
        Null	= 5,
        XYStep	= 6,
        YXStep	= 7,
        Bars	= 8,
        Stick	= 9
    } 	LineType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("A096E330-15BA-42C1-BD53-2C7E0B96CF77") 
enum __MIDL___MIDL_itf_NTGraph_0000_0000_0002
    {
        Nosym	= 0,
        Dots	= 1,
        Rectangles	= 2,
        Diamonds	= 3,
        Asterisk	= 4,
        DownTriangles	= 5,
        UpTriangles	= 6,
        LeftTriangles	= 7,
        RightTriangles	= 8
    } 	SymbolType;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("77D6CAFB-62A7-4916-A188-9A76D6194870") 
enum __MIDL___MIDL_itf_NTGraph_0000_0000_0003
    {
        Flat	= 0,
        Scope	= 1,
        Bitmap	= 2
    } 	FrameStyle;

typedef /* [helpstring][uuid] */  DECLSPEC_UUID("7F2E3118-D790-42AE-81C9-FA14B54FC817") 
enum __MIDL___MIDL_itf_NTGraph_0000_0000_0004
    {
        None	= 0,
        Track	= 1,
        Zoom	= 2,
        PanXY	= 3,
        PanX	= 4,
        PanY	= 5
    } 	TrackModeState;


DEFINE_GUID(LIBID_NTGRAPHLib,0x49F811F7,0x6005,0x4AAF,0xAE,0x00,0x9D,0x98,0x76,0x6A,0x6E,0x26);

#ifndef ___DNTGraph_DISPINTERFACE_DEFINED__
#define ___DNTGraph_DISPINTERFACE_DEFINED__

/* dispinterface _DNTGraph */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DNTGraph,0xAC90A107,0x78E8,0x4ED8,0x99,0x5A,0x3A,0xE8,0xBB,0x30,0x44,0xA7);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AC90A107-78E8-4ED8-995A-3AE8BB3044A7")
    _DNTGraph : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DNTGraphVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DNTGraph * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DNTGraph * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DNTGraph * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DNTGraph * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DNTGraph * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DNTGraph * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DNTGraph * This,
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
    } _DNTGraphVtbl;

    interface _DNTGraph
    {
        CONST_VTBL struct _DNTGraphVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DNTGraph_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DNTGraph_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DNTGraph_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DNTGraph_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DNTGraph_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DNTGraph_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DNTGraph_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DNTGraph_DISPINTERFACE_DEFINED__ */


#ifndef ___DNTGraphEvents_DISPINTERFACE_DEFINED__
#define ___DNTGraphEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DNTGraphEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DNTGraphEvents,0xD59ADFE5,0x1B52,0x45D5,0xAE,0x1D,0x8F,0xA1,0x46,0x15,0x21,0x54);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D59ADFE5-1B52-45D5-AE1D-8FA146152154")
    _DNTGraphEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DNTGraphEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DNTGraphEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DNTGraphEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DNTGraphEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DNTGraphEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DNTGraphEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DNTGraphEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DNTGraphEvents * This,
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
    } _DNTGraphEventsVtbl;

    interface _DNTGraphEvents
    {
        CONST_VTBL struct _DNTGraphEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DNTGraphEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DNTGraphEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DNTGraphEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DNTGraphEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DNTGraphEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DNTGraphEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DNTGraphEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DNTGraphEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_NTGraph,0xC9FE01C2,0x2746,0x479B,0x96,0xAB,0xE0,0xBE,0x99,0x31,0xB0,0x18);

#ifdef __cplusplus

class DECLSPEC_UUID("C9FE01C2-2746-479B-96AB-E0BE9931B018")
NTGraph;
#endif
#endif /* __NTGRAPHLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


