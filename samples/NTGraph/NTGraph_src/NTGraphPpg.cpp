// NTGraphPpg.cpp : Implementation of the CNTGraphPropPage property page class.

#include "stdafx.h"
#include "NTGraph.h"
#include "NTGraphPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CNTGraphPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CNTGraphPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CNTGraphPropPage)
	ON_WM_HELPINFO()
	ON_MESSAGE(CPN_CLOSEUP , OnColorChange)
	ON_EN_CHANGE(IDC_CAPTION, OnChangeCaption)
	ON_BN_CLICKED(IDC_CHECK_SHOWGRID, OnCheckShowgrid)
	ON_BN_CLICKED(IDC_CHECK_XLOG, OnCheckXlog)
	ON_BN_CLICKED(IDC_CHECK_YLOG, OnCheckYlog)
	ON_CBN_CLOSEUP(IDC_COMBO_FRAME, OnCloseupComboFrame)
	ON_CBN_CLOSEUP(IDC_COMBO_MODE, OnCloseupComboMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CNTGraphPropPage, "NTGRAPH.NTGraphPropPage.1",
	0x2dd5d509, 0xe89e, 0x4825, 0x87, 0xd3, 0xa9, 0x39, 0xe6, 0x89, 0xbd, 0x25)


/////////////////////////////////////////////////////////////////////////////
// CNTGraphPropPage::CNTGraphPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CNTGraphPropPage

BOOL CNTGraphPropPage::CNTGraphPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_NTGRAPH_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CNTGraphPropPage::CNTGraphPropPage - Constructor

CNTGraphPropPage::CNTGraphPropPage() :
	COlePropertyPage(IDD, IDS_NTGRAPH_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CNTGraphPropPage)
	//}}AFX_DATA_INIT

	SetHelpInfo(_T("Names to appear in the control"), _T("NTGRAPH.HLP"), 0);
}


/////////////////////////////////////////////////////////////////////////////
// CNTGraphPropPage::DoDataExchange - Moves data between page and properties

void CNTGraphPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CNTGraphPropPage)
	DDX_Control(pDX, IDC_CHECK_YLOG, m_btnYLog);
	DDX_Control(pDX, IDC_CHECK_XLOG, m_btnXLog);
	DDX_Control(pDX, IDC_CHECK_SHOWGRID, m_btnGrid);
	DDX_Control(pDX, IDC_FRAME_COLOR, m_btnFrameColor);
	DDX_Control(pDX, IDC_PLOT_COLOR, m_btnPlotColor);
	DDX_Control(pDX, IDC_GRID_COLOR, m_btnGridColor);
	DDX_Control(pDX, IDC_AXIS_COLOR, m_btnAxisColor);
	DDX_Control(pDX, IDC_LABEL_COLOR, m_btnLabelColor);
	DDP_CBIndex(pDX, IDC_COMBO_FRAME, m_nFrame, _T("FrameStyle") );
	DDX_CBIndex(pDX, IDC_COMBO_FRAME, m_nFrame);
	DDX_Control(pDX, IDC_COMBO_FRAME, m_cbFrame);
	DDP_CBIndex(pDX, IDC_COMBO_FRAME, m_nMode, _T("TrackMode") );
	DDX_CBIndex(pDX, IDC_COMBO_FRAME, m_nMode);
	DDX_Control(pDX, IDC_COMBO_MODE, m_cbTrackMode);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);

}


/////////////////////////////////////////////////////////////////////////////
// CNTGraphPropPage message handlers
///////////////////////////////////////////////////////////////////////////


BOOL CNTGraphPropPage::OnHelpInfo(HELPINFO* pHelpInfo) 
{

	// OnHelp is called by IPropertyPage::Help.  When someone requests
	// it, we supply help by calling CWinApp::WinHelp
	 AfxGetApp()->WinHelp(0,HELP_CONTENTS);
	
	return COlePropertyPage::OnHelpInfo(pHelpInfo);
}

BOOL CNTGraphPropPage::OnHelp(LPCTSTR)
{

	// OnHelp is called by IPropertyPage::Help.  When someone requests
	// it, we supply help by calling CWinApp::WinHelp
	 AfxGetApp()->WinHelp(0,HELP_CONTENTS);


return TRUE;
}
LONG CNTGraphPropPage::OnColorChange(UINT /*lParam*/, LONG /*wParam*/)
{

	CString str;
	
	str.Format(L"%d",m_btnFrameColor.GetColour());
	SetPropText(L"ControlFrameColor", str);

	str.Format(L"%d",m_btnPlotColor.GetColour());
	SetPropText(L"PlotAreaColor", str);
	
	str.Format(L"%d",m_btnGridColor.GetColour());
	SetPropText(L"GridColor", str);
	
	str.Format(L"%d",m_btnAxisColor.GetColour());
	SetPropText(L"AxisColor", str);
	
	str.Format(L"%d",m_btnLabelColor.GetColour());
	SetPropText(L"LabelColor", str);


    TRACE0("Selection changed= %d\n");
    return TRUE;
}

void CNTGraphPropPage::OnChangeCaption() 
{
	CString str;
	GetDlgItemText(IDC_CAPTION, str);
	SetPropText(L"Caption", str);		
}


void CNTGraphPropPage::OnCheckShowgrid() 
{
	CString str(L"TRUE");		

	if(m_btnGrid.GetCheck())
		SetPropText(L"ShowGrid", str);
	else
	{   
		str = L"FALSE";
        SetPropText(L"ShowGrid", str);
	}

}

void CNTGraphPropPage::OnCheckXlog() 
{
	CString str(L"TRUE");		

	if(m_btnXLog.GetCheck())
		SetPropText(L"XLog", str);
	else
	{   
		str = L"FALSE";
        SetPropText(L"XLog", str);
	}
}

void CNTGraphPropPage::OnCheckYlog() 
{
	CString str(L"TRUE");		

	if(m_btnYLog.GetCheck())
		SetPropText(L"YLog", str);
	else
	{   
		str = L"FALSE";
        SetPropText(L"YLog", str);
	}	
}

void CNTGraphPropPage::OnCloseupComboFrame() 
{
	CString str;
	str.Format(L"%d",m_cbFrame.GetCurSel());
   	SetPropText(L"FrameStyle", str);		
}

void CNTGraphPropPage::OnCloseupComboMode() 
{
	CString str;
	str.Format(L"%d",m_cbTrackMode.GetCurSel());
   	SetPropText(L"TrackMode", str);			
}

void CNTGraphPropPage::UpdateControls() 
{
	CString caption;
	GetPropText(L"Caption", &caption);

	SetDlgItemText (IDC_CAPTION, caption);

	COLORREF color;

	GetPropText(L"AxisColor", &color);
    m_btnAxisColor.SetColour(color);

	GetPropText(L"ControlFrameColor", &color);
    m_btnFrameColor.SetColour(color);

	GetPropText(L"GridColor", &color);
    m_btnGridColor.SetColour(color);

	GetPropText(L"PlotAreaColor", &color);
    m_btnPlotColor.SetColour(color);

	GetPropText(L"LabelColor", &color);
    m_btnLabelColor.SetColour(color);

	int frame;
	GetPropText(L"FrameStyle", &frame);
	m_cbFrame.SetCurSel(frame);

	int mode;
	GetPropText(L"TrackMode", &mode);
	m_cbTrackMode.SetCurSel(mode);

	BOOL grid;
	GetPropText(L"ShowGrid", &grid);

	if(grid)
		CheckDlgButton(IDC_CHECK_SHOWGRID,BST_CHECKED);
	else
		CheckDlgButton(IDC_CHECK_SHOWGRID,BST_UNCHECKED);	

	BOOL xlog;
	GetPropText(L"XLog", &xlog);

	if(xlog)
		CheckDlgButton(IDC_CHECK_XLOG,BST_CHECKED);
	else
		CheckDlgButton(IDC_CHECK_XLOG,BST_UNCHECKED);	

	BOOL ylog;
	GetPropText(L"YLog", &ylog);

	if(ylog)
		CheckDlgButton(IDC_CHECK_YLOG,BST_CHECKED);
	else
		CheckDlgButton(IDC_CHECK_YLOG,BST_UNCHECKED);	


}

BOOL CNTGraphPropPage::OnInitDialog() 
{
	COlePropertyPage::OnInitDialog();
	


	UpdateControls();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
