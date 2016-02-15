

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Feb 14 16:51:08 2016
 */
/* Compiler settings for CircleControl.idl:
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

#ifndef __CircleControl_h_h__
#define __CircleControl_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICircleControl_FWD_DEFINED__
#define __ICircleControl_FWD_DEFINED__
typedef interface ICircleControl ICircleControl;

#endif 	/* __ICircleControl_FWD_DEFINED__ */


#ifndef __CircleControl_FWD_DEFINED__
#define __CircleControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class CircleControl CircleControl;
#else
typedef struct CircleControl CircleControl;
#endif /* __cplusplus */

#endif 	/* __CircleControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICircleControl_INTERFACE_DEFINED__
#define __ICircleControl_INTERFACE_DEFINED__

/* interface ICircleControl */
/* [unique][nonextensible][object][dual][uuid] */ 


EXTERN_C const IID IID_ICircleControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5DD61CD-2165-4B3D-BCC0-594C36F9EE06")
    ICircleControl : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Radius( 
            /* [retval][out] */ float *ReturnVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Radius( 
            /* [in] */ float Value) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICircleControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICircleControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICircleControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICircleControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICircleControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICircleControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICircleControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICircleControl * This,
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
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Radius )( 
            ICircleControl * This,
            /* [retval][out] */ float *ReturnVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Radius )( 
            ICircleControl * This,
            /* [in] */ float Value);
        
        END_INTERFACE
    } ICircleControlVtbl;

    interface ICircleControl
    {
        CONST_VTBL struct ICircleControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICircleControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICircleControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICircleControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICircleControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICircleControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICircleControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICircleControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICircleControl_get_Radius(This,ReturnVal)	\
    ( (This)->lpVtbl -> get_Radius(This,ReturnVal) ) 

#define ICircleControl_put_Radius(This,Value)	\
    ( (This)->lpVtbl -> put_Radius(This,Value) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICircleControl_INTERFACE_DEFINED__ */



#ifndef __CircleControlLib_LIBRARY_DEFINED__
#define __CircleControlLib_LIBRARY_DEFINED__

/* library CircleControlLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CircleControlLib;

EXTERN_C const CLSID CLSID_CircleControl;

#ifdef __cplusplus

class DECLSPEC_UUID("1C797BFB-3F97-4CF8-B857-45C90028759B")
CircleControl;
#endif
#endif /* __CircleControlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


