

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_NTGRAPHLib,0x49F811F7,0x6005,0x4AAF,0xAE,0x00,0x9D,0x98,0x76,0x6A,0x6E,0x26);


MIDL_DEFINE_GUID(IID, DIID__DNTGraph,0xAC90A107,0x78E8,0x4ED8,0x99,0x5A,0x3A,0xE8,0xBB,0x30,0x44,0xA7);


MIDL_DEFINE_GUID(IID, DIID__DNTGraphEvents,0xD59ADFE5,0x1B52,0x45D5,0xAE,0x1D,0x8F,0xA1,0x46,0x15,0x21,0x54);


MIDL_DEFINE_GUID(CLSID, CLSID_NTGraph,0xC9FE01C2,0x2746,0x479B,0x96,0xAB,0xE0,0xBE,0x99,0x31,0xB0,0x18);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



