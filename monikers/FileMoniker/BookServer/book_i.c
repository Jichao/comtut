

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sun Mar 27 00:40:00 2016
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

MIDL_DEFINE_GUID(IID, IID_ISection,0x57F0CC0A,0x8A4F,0x413E,0xAE,0xEC,0xDA,0x9E,0x11,0x5B,0xDA,0x77);


MIDL_DEFINE_GUID(IID, IID_IChapter,0xA6829C1B,0xB73A,0x4400,0x90,0x48,0x16,0xD3,0x29,0x91,0x29,0xB4);


MIDL_DEFINE_GUID(IID, IID_IBook,0xA1B6605F,0xFD40,0x4B6C,0x86,0x25,0x9E,0x86,0xEE,0x22,0x7C,0x8D);


MIDL_DEFINE_GUID(IID, LIBID_BookLibrary,0xA09F7882,0xD0A5,0x4A33,0x94,0x33,0xC0,0x56,0x3E,0x8B,0x5C,0x36);


MIDL_DEFINE_GUID(CLSID, CLSID_Book,0xd03979bc,0x59fa,0x48dc,0xb5,0x15,0xac,0x25,0x65,0xda,0xbc,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_Chapter,0xc03979bc,0x59fa,0x48dc,0xb5,0x15,0xac,0x25,0x65,0xda,0xbc,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_Section,0x05765590,0xf55e,0x4aa5,0xb0,0xf3,0x3c,0xc8,0x22,0x75,0xf8,0x40);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



