#include "CMachineOrder.h"
#include "resource.h"
#include "CHttpClient.h"

CMachineOrderDlg::CMachineOrderDlg(CWnd* pParent /* = NULL */)
	: CDialog(IDD_MACHINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_vcEdit.clear();
}


CMachineOrderDlg::~CMachineOrderDlg()
{
	m_vcEdit.clear();
}


void CMachineOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMachineOrderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMachineOrderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMachineOrderDlg::OnBnClickedCancel)
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

		DWORD dwStyle = ::GetWindowLong(pEdit->GetSafeHwnd(), GWL_STYLE);
		dwStyle |= ES_NUMBER;
		::SetWindowLong(pEdit->GetSafeHwnd(), GWL_STYLE, dwStyle);
		pEdit->ShowWindow(SW_SHOW); 
		rc.OffsetRect(nSpace, 0);

		m_vcEdit.push_back(pEdit);
	}
}

void CMachineOrderDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strMachineList;
	CString strText;
	for (int i = 0; i < m_nCount; ++i)
	{
		GetDlgItem(ID_EDIT_BEGIN + i)->GetWindowText(strText);
		strMachineList = strMachineList + strText + _T("+");
	}
	
	strMachineList.TrimRight(_T("+"));

	CString strURL;
	strURL.LoadString(IDS_STRING_ORDERRECV);
	strURL = strURL +  + _T("receive/");

	CHttpClient* pHttpClient = new CHttpClient;
	LPCTSTR pJsonPostData = _T("");
	CString strResponse;
	if (pHttpClient)
	{
		//pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
	}


	m_pParent->SetMachineList(strMachineList);

	if (pHttpClient)
	{
		delete pHttpClient;
		pHttpClient = NULL;
	}

	CDialog::OnOK();
}


void CMachineOrderDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
