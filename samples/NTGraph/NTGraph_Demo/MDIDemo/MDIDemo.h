// MDIDemo.h : main header file for the MDIDEMO application
//

#if !defined(AFX_MDIDEMO_H__426936B6_02CE_4C04_B4C3_FE938DFC7E72__INCLUDED_)
#define AFX_MDIDEMO_H__426936B6_02CE_4C04_B4C3_FE938DFC7E72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMDIDemoApp:
// See MDIDemo.cpp for the implementation of this class
//

class CMDIDemoApp : public CWinApp
{
public:
	CMDIDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMDIDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIDEMO_H__426936B6_02CE_4C04_B4C3_FE938DFC7E72__INCLUDED_)
