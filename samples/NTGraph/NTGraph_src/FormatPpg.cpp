// FormatPpg.cpp : implementation file
//

#include "stdafx.h"
#include "NTGraph.h"
#include "FormatPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormatPropPage dialog

IMPLEMENT_DYNCREATE(CFormatPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CFormatPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CFormatPropPage)
	ON_EN_CHANGE(IDC_EDIT_FORMAT, OnChangeEditFormat)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT, OnButtonDefault)
	ON_LBN_SELCHANGE(IDC_FORMAT_LIST, OnSelchangeFormatList)
	ON_CBN_CLOSEUP(IDC_COMBO_TYPE, OnCloseupComboType)
	ON_CBN_CLOSEUP(IDC_COMBO_AXIS, OnCloseupComboAxis)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

// {743A8F83-8596-4E55-92AF-CC48DA8BAA5E}
IMPLEMENT_OLECREATE_EX(CFormatPropPage, "NTGraph.CFormatPropPage",
	0x743a8f83, 0x8596, 0x4e55, 0x92, 0xaf, 0xcc, 0x48, 0xda, 0x8b, 0xaa, 0x5e)


/////////////////////////////////////////////////////////////////////////////
// CFormatPropPage::CFormatPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CFormatPropPage

BOOL CFormatPropPage::CFormatPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Define string resource for page type; replace '0' below with ID.

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_FORMAT_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CFormatPropPage::CFormatPropPage - Constructor

// TODO: Define string resource for page caption; replace '0' below with ID.

CFormatPropPage::CFormatPropPage() :
// ****** Add your code below this line ********** //
     COlePropertyPage(IDD,  IDS_FORMAT_PPG_CAPTION)
// ****** Add your code above this line ********** //
{
	//{{AFX_DATA_INIT(CFormatPropPage)
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CFormatPropPage::DoDataExchange - Moves data between page and properties

void CFormatPropPage::DoDataExchange(CDataExchange* pDX)
{
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_DATA_MAP(CFormatPropPage)
	DDX_Control(pDX, IDC_FORMAT_LIST, m_lbFormats);
	DDX_Control(pDX, IDC_COMBO_TYPE, m_cbType);
	DDX_Control(pDX, IDC_COMBO_AXIS, m_cbAxis);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CFormatPropPage message handlers

void CFormatPropPage::OnChangeEditFormat() 
{
	CString str ;
	GetDlgItemText(IDC_EDIT_FORMAT, str);
	
	if(m_cbAxis.GetCurSel())
		SetPropText(L"FormatAxisLeft", str);
	else
		SetPropText(L"FormatAxisBottom", str);
}

void CFormatPropPage::UpdateControls()
{
	CString str;
	BOOL time;

	if(m_cbAxis.GetCurSel())
	{
		GetPropText(L"YTime",&time);
		GetPropText(L"FormatAxisLeft", &str);
	}
    else
	{
		GetPropText(L"XTime",&time);
		GetPropText(L"FormatAxisBottom", &str);
	}

	SetDlgItemText(IDC_EDIT_FORMAT, str);

	if(time)
		m_cbType.SetCurSel(3);
	else
		m_cbType.SetCurSel(0);

	OnCloseupComboType() ;
}


BOOL CFormatPropPage::OnInitDialog() 
{
	COlePropertyPage::OnInitDialog();
	
	m_cbAxis.SetCurSel(0);
	m_cbType.SetCurSel(0);
	UpdateControls();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFormatPropPage::OnButtonDefault() 
{
	SetDlgItemText(IDC_EDIT_FORMAT, L"%g");
	m_cbType.SetCurSel(0);
	UpdateControls();

}

void CFormatPropPage::OnSelchangeFormatList() 
{
	CString str;
	switch(m_cbType.GetCurSel())
	{
		case 0:
			if(m_lbFormats.GetCaretIndex()==0)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%g");
			else if(m_lbFormats.GetCaretIndex()==1)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.1f");
			else if(m_lbFormats.GetCaretIndex()==2)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.2f");
			else if(m_lbFormats.GetCaretIndex()==3)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.3f");
			else if(m_lbFormats.GetCaretIndex()==4)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.4f");
			break;
		case 1:
			if(m_lbFormats.GetCaretIndex()==0)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.e");
			else if(m_lbFormats.GetCaretIndex()==1)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.1e");
			else if(m_lbFormats.GetCaretIndex()==2)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.2e");
			else if(m_lbFormats.GetCaretIndex()==3)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.3e");
			else if(m_lbFormats.GetCaretIndex()==4)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.4e");
			else if(m_lbFormats.GetCaretIndex()==5)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.E");
			else if(m_lbFormats.GetCaretIndex()==6)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.1E");
			else if(m_lbFormats.GetCaretIndex()==7)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.2E");
			else if(m_lbFormats.GetCaretIndex()==8)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.3E");
			else if(m_lbFormats.GetCaretIndex()==9)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.4E");
			break;
		case 2:
			if(m_lbFormats.GetCaretIndex()==0)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%g V");
			else if(m_lbFormats.GetCaretIndex()==1)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%g A");
			else if(m_lbFormats.GetCaretIndex()==2)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%g Hz");
			else if(m_lbFormats.GetCaretIndex()==3)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%g g");
			else if(m_lbFormats.GetCaretIndex()==4)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%g Deg");
			else if(m_lbFormats.GetCaretIndex()==5)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%g %%");
			else if(m_lbFormats.GetCaretIndex()==6)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.1f %%");
			else if(m_lbFormats.GetCaretIndex()==7)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%.2f %%");
			else if(m_lbFormats.GetCaretIndex()==8)
				SetDlgItemText(IDC_EDIT_FORMAT, L"$ %g");
			else if(m_lbFormats.GetCaretIndex()==9)
				SetDlgItemText(IDC_EDIT_FORMAT, L"$ %.1f");
			else if(m_lbFormats.GetCaretIndex()==10)
				SetDlgItemText(IDC_EDIT_FORMAT, L"$ %.2f");
			break;
		case 3:
			if(m_lbFormats.GetCaretIndex()==0)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%d %a/%B/%Y");
			else if(m_lbFormats.GetCaretIndex()==1)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%d/%b/%Y");
            else if(m_lbFormats.GetCaretIndex()==2)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%d/%m/%Y");
            else if(m_lbFormats.GetCaretIndex()==3)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%b/%Y");
            else if(m_lbFormats.GetCaretIndex()==4)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%d/%B");
			break;
		case 4:
			if(m_lbFormats.GetCaretIndex()==0)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%H:%M:%S");
			else if(m_lbFormats.GetCaretIndex()==1)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%H %p/%M");
			else if(m_lbFormats.GetCaretIndex()==2)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%H:%M");
            else if(m_lbFormats.GetCaretIndex()==3)
				SetDlgItemText(IDC_EDIT_FORMAT, L"%M:%S");
			break;
	}

}


void CFormatPropPage::OnCloseupComboType() 
{

	switch(m_cbType.GetCurSel())
	{
		case 0:
			SetAxisTimeFormat("FALSE");
			m_lbFormats.ResetContent();
			m_lbFormats.AddString(L".");
            m_lbFormats.AddString(L".#");
			m_lbFormats.AddString(L".##");
			m_lbFormats.AddString(L".###");
			m_lbFormats.AddString(L".####");
			break;
		case 1:
			SetAxisTimeFormat("FALSE");
			m_lbFormats.ResetContent();
			m_lbFormats.AddString(L"e");
            m_lbFormats.AddString(L".#e");
			m_lbFormats.AddString(L".##e");
			m_lbFormats.AddString(L".###e");
			m_lbFormats.AddString(L".####e");
			m_lbFormats.AddString(L"E");
            m_lbFormats.AddString(L".#E");
			m_lbFormats.AddString(L".##E");
			m_lbFormats.AddString(L".###E");
			m_lbFormats.AddString(L".####E");
			break;
		case 2:
			SetAxisTimeFormat("FALSE");
			m_lbFormats.ResetContent();
			m_lbFormats.AddString(L"V");
            m_lbFormats.AddString(L"A");
			m_lbFormats.AddString(L"Hz");
			m_lbFormats.AddString(L"g");
			m_lbFormats.AddString(L"Deg");
			m_lbFormats.AddString(L". %");
			m_lbFormats.AddString(L".# %");
            m_lbFormats.AddString(L".## %");
			m_lbFormats.AddString(L"$ .");
			m_lbFormats.AddString(L"$ .#");
			m_lbFormats.AddString(L"$ .##");
			break;
		case 3:
			SetAxisTimeFormat("TRUE");
			m_lbFormats.ResetContent();
			m_lbFormats.AddString(L"ddd/mmm/yyy");
			m_lbFormats.AddString(L"dd/mm/yy");
			m_lbFormats.AddString(L"d/m/y");
			m_lbFormats.AddString(L"m/y");
			m_lbFormats.AddString(L"d/m");
			break;
		case 4:
			SetAxisTimeFormat("TRUE");
			m_lbFormats.ResetContent();
			m_lbFormats.AddString(L"h:m:s");
			m_lbFormats.AddString(L"hh:m");
			m_lbFormats.AddString(L"h:m");
			m_lbFormats.AddString(L"m:s");
			break;
	}	
}

void CFormatPropPage::OnCloseupComboAxis() 
{
	UpdateControls();	
}

void CFormatPropPage::SetAxisTimeFormat(CString str)
{

	if(m_cbAxis.GetCurSel())
	{
		if(m_cbAxis.GetCurSel())
			SetPropText(L"YTime", str);
		else
			SetPropText(L"YTime", str);
	}
	else
	{
		if(m_cbAxis.GetCurSel())
			SetPropText(L"XTime", str);
		else
			SetPropText(L"XTime", str);
	}


}