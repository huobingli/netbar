#include "CRecviceOrder.h"
#include "resource.h"


CRecviceOrder::CRecviceOrder()
{
}


CRecviceOrder::~CRecviceOrder()
{
}


CRecvDlg::CRecvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RECV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CRecvDlg::~CRecvDlg()
{

}

void CRecvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRecvDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CNetbarDlg 消息处理程序

BOOL CRecvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_nHour = 59;
	m_nMinute = 59;
	m_nSecond = 59;


	SetTimer(TIMER_COUNTDOWN, 1000, NULL);
	//SetTimer(NULL, TIMER_COUNTDOWN)
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRecvDlg::OnPaint()
{
	if (IsIconic())
	{

	}
	else
	{
 		CPaintDC dc(this); // 用于绘制的设备上下文
 		CRect rcDlg;
 		GetClientRect(rcDlg);
		CDC* pDC = &dc;
// 
// 		rcDlg.bottom -= 40;
// 		CRect rcDraw(rcDlg);
// 
// 		// 第一行绘制 
// 		// 位置  台数  使用时间
// 		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
// 		DrawFirst(&dc, rcDraw);
// 
// 		// 第二行绘制
// 		// 用户要求
// 		rcDraw.top = rcDraw.bottom;
// 		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
// 		DrawSecond(&dc, rcDraw);
// 
// 		// 第三行绘制
// 		// 用户留言
// 		rcDraw.top = rcDraw.bottom;
// 		rcDraw.bottom = rcDlg.bottom;
// 		DrawMessage(&dc, rcDraw);

		CString str;
		str.Format(_T("%02d : %02d : %02d"), m_nHour, m_nMinute, m_nSecond);
		pDC->DrawText(str, rcDlg, DT_LEFT | DT_VCENTER);
		

		CDialog::OnPaint();
	}
}

void CRecvDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialog::OnClose();
}

BOOL CRecvDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
}

void CRecvDlg::SetParent(CNetbarDlg* pParent)
{
	m_pParent = pParent;
}

void CRecvDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (TIMER_COUNTDOWN == nIDEvent)
	{
		UpdateCountDown(nIDEvent);
	}

	CDialog::OnTimer(nIDEvent);
}

void CRecvDlg::UpdateCountDown(UINT_PTR nIDEvent)
{
	CString str(_T(""));
#define MAX_VALUE 59
	///*static*/ int nHour = MAX_VALUE;
	///*static*/ int nMinute = MAX_VALUE;
	///*static*/ int nSecond = MAX_VALUE;
	--m_nSecond;

	if (!m_nSecond)
	{
		--m_nMinute;
		if (!m_nMinute)
		{
			--m_nHour;
			if (!m_nHour)
			{
				//SetDlgItemText(IDC_EDIT1, _T("00 : 00 : 00"));
				//::SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_EDIT1, strTime);
				KillTimer(nIDEvent);
				AfxMessageBox(_T("Game Over!"));
				return;
			}
			m_nMinute = MAX_VALUE;
		}
		m_nSecond = MAX_VALUE;
	}

	Invalidate(TRUE);
	//str.Format(_T("%02d : %02d : %02d"), m_nHour, m_nMinute, m_nSecond);
	//SetDlgItemText(IDC_EDIT1, str);
}
