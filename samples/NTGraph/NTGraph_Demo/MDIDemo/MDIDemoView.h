// MDIDemoView.h : interface of the CMDIDemoView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "ntgraph.h"
//}}AFX_INCLUDES

#if !defined(AFX_MDIDEMOVIEW_H__95375B63_80BA_44C9_961A_B79316136555__INCLUDED_)
#define AFX_MDIDEMOVIEW_H__95375B63_80BA_44C9_961A_B79316136555__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMDIDemoView : public CFormView
{
protected: // create from serialization only
	CMDIDemoView();
	DECLARE_DYNCREATE(CMDIDemoView)

public:
	//{{AFX_DATA(CMDIDemoView)
	enum { IDD = IDD_MDIDEMO_FORM };
	CNTGraph	m_Graph;
	//}}AFX_DATA

// Attributes
public:
	CMDIDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMDIDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void OnPrintControl();
	//{{AFX_MSG(CMDIDemoView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnControlCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MDIDemoView.cpp
inline CMDIDemoDoc* CMDIDemoView::GetDocument()
   { return (CMDIDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIDEMOVIEW_H__95375B63_80BA_44C9_961A_B79316136555__INCLUDED_)
