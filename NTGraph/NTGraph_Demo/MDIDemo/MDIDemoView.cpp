// MDIDemoView.cpp : implementation of the CMDIDemoView class
//

#include "stdafx.h"
#include "MDIDemo.h"

#include "MDIDemoDoc.h"
#include "MDIDemoView.h"


#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIDemoView

IMPLEMENT_DYNCREATE(CMDIDemoView, CFormView)

BEGIN_MESSAGE_MAP(CMDIDemoView, CFormView)
	//{{AFX_MSG_MAP(CMDIDemoView)
	ON_WM_TIMER()
	ON_COMMAND(ID_EDIT_COPY, OnControlCopy)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, OnPrintControl)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIDemoView construction/destruction

CMDIDemoView::CMDIDemoView()
	: CFormView(CMDIDemoView::IDD)
{
	//{{AFX_DATA_INIT(CMDIDemoView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMDIDemoView::~CMDIDemoView()
{
}

void CMDIDemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMDIDemoView)
	DDX_Control(pDX, IDC_NTGRAPHCTRL1, m_Graph);
	//}}AFX_DATA_MAP
}

BOOL CMDIDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CFormView::PreCreateWindow(cs);
}

void CMDIDemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
    
	m_Graph.SetPlotAreaColor(RGB(0,0,0));
    m_Graph.SetGridColor(RGB(120,225,0));
	m_Graph.SetShowGrid(TRUE);
	m_Graph.SetFrameStyle(2);

	// setup the timer id=1, 50 ms
	SetTimer(1, 50, NULL);
	

}

/////////////////////////////////////////////////////////////////////////////
// CMDIDemoView diagnostics

#ifdef _DEBUG
void CMDIDemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMDIDemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMDIDemoDoc* CMDIDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDIDemoDoc)));
	return (CMDIDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIDemoView message handlers

void CMDIDemoView::OnDraw(CDC* pDC) 
{
	CRect Rect ;
	GetClientRect(&Rect) ;
	m_Graph.MoveWindow(Rect,TRUE);
}

void CMDIDemoView::OnTimer(UINT nIDEvent) 
{
  
  UpdateData(TRUE);

  m_Graph.ClearGraph();

  // The Element [0] is allocated by default
  m_Graph.SetElementLineColor(RGB(225,255,0));
 	   
  double data;
  for (int i=0;i<100;i++)
  {
		data=(rand()*sin(i/3.15))/10000;
        m_Graph.PlotY(data,0);
  }
  
  m_Graph.SetRange(0,100,-3,3);
  

  UpdateData(FALSE);	

  CFormView::OnTimer(nIDEvent);
}

void CMDIDemoView::OnPrintControl()
{
	KillTimer(1);
	m_Graph.PrintGraph();
	Sleep(100);
	SetTimer(1,50,NULL);
}

void CMDIDemoView::OnControlCopy() 
{
	KillTimer(1);
	m_Graph.CopyToClipboard();
	Sleep(100);
    SetTimer(1,50,NULL);
}
