#include "CMachineOrder.h"
#include "resource.h"


CMachineOrderDlg::CMachineOrderDlg(CWnd* pParent /* = NULL */)
	: CDialog(IDD_MACHINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_vcEdit.clear();
}


CMachineOrderDlg::~CMachineOrderDlg()
{


}


void CMachineOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMachineOrderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CMachineOrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//SetTimer(NULL, TIMER_COUNTDOWN)

	ShowMachineEdit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMachineOrderDlg::SetMachineCount(int nCount)
{
	m_nCount = nCount;
}

void CMachineOrderDlg::ShowMachineEdit()
{
	CRect rcDlg;
	GetClientRect(rcDlg);
	//CRect rc(0, 0, 25, 25);
	CRect rc(rcDlg.left + 20, rcDlg.top + 20, rcDlg.left + 60, rcDlg.top + 40);
	int nSpace = 50;

	for (int i = 0; i < m_nCount; ++i)
	{
		CEdit* pEdit = new CEdit;

		pEdit->Create(WS_VISIBLE | WS_CHILD | WS_BORDER | WS_EX_STATICEDGE, rc ,this,ID_EDIT_BEGIN + i);
		pEdit->ShowWindow(SW_SHOW); 
		rc.OffsetRect(nSpace, 0);

		m_vcEdit.push_back(pEdit);
	}
}