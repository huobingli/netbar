#include "CRecviceOrder.h"
#include "resource.h"
#include "netbarDlg.h"
#include "CHttpClient.h"
#include "CUserInfo.h"


// CRecviceOrder::CRecviceOrder()
// {
// }
// 
// 
// CRecviceOrder::~CRecviceOrder()
// {
// }


CRecvDlg::CRecvDlg(RecvInfo* pInfo, CWnd* pParent /* =NULL */)
	: CDialog(IDD_RECV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pRecvInfo = new RecvInfo(pInfo);

	m_font.CreateFont(14, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("宋体"));

	m_fontMessage.CreateFont(12, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("宋体"));
}

CRecvDlg::~CRecvDlg()
{
	if (m_pRecvInfo)
	{
		delete m_pRecvInfo;
		m_pRecvInfo = NULL;
	}
}

void CRecvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRecvDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_CANCEL_DAODIAN, &CRecvDlg::OnBnClickedCancelDaodian)
	ON_BN_CLICKED(ID_CONFIM_RECVLAST, &CRecvDlg::OnBnClickedCancelDaodian)
	ON_BN_CLICKED(ID_CONFIM_RECVFULL, &CRecvDlg::OnBnClickedCancelDaodian)
END_MESSAGE_MAP()


// CNetbarDlg 消息处理程序

BOOL CRecvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_nHour = atoi(m_pRecvInfo->m_strArriveTimer) - 1;
	m_nMinute = 59;
	m_nSecond = 59;

// 	m_nHour = 0;// atoi(m_pRecvInfo->m_strArriveTimer) - 1;
// 	m_nMinute = 0;
// 	m_nSecond = 10;

	SetTimer(TIMER_COUNTDOWN, 1000, NULL);
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
 
 		rcDlg.bottom -= 20;
		rcDlg.top += 4;
 		CRect rcDraw(rcDlg);
 
 		// 第一行绘制 
		// 绘制信息表头
 		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 2;
 		DrawFirst(&dc, rcDraw);
 
 		// 第二行绘制
		// 绘制显示信息
 		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDlg.bottom;
 		DrawSecond(&dc, rcDraw);
			

		CDialog::OnPaint();
	}
}

void CRecvDlg::DrawFirst(CDC* pDC, CRect rcDraw)
{
	CRect rcText(rcDraw);
	
	CFont* pFont = pDC->SelectObject(&m_font);

	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(_T("订单号"), rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(_T("安排机器"), rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcDraw.right;
	pDC->DrawText(_T("倒计时"), rcText, DT_CENTER | DT_VCENTER);
	pDC->SelectObject(pFont);
}

void CRecvDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{
	CRect rcText(rcDraw);

	CFont* pFont = pDC->SelectObject(&m_font);

	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(m_pRecvInfo->m_strOrderNum, rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(m_pRecvInfo->m_strMachineList, rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcDraw.right;
	CString str;
	if ((m_nHour == 0 && m_nMinute == 0 && m_nSecond == 0 ) || (m_pRecvInfo->m_dwShowOrder == RECVINFO_OVERTIME))
	{
		str = _T("已经超时");
	}
	else
	{
		str.Format(_T("%02d : %02d : %02d"), m_nHour, m_nMinute, m_nSecond);
	}	
	pDC->DrawText(str, rcText, DT_CENTER | DT_VCENTER);
	pDC->SelectObject(pFont);
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

// 	if (!m_nSecond)
// 	{
// 		--m_nMinute;
// 		if (!m_nMinute)
// 		{
// 			--m_nHour;
// 			if (!m_nHour)
// 			{
// 				//SetDlgItemText(IDC_EDIT1, _T("00 : 00 : 00"));
// 				//::SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_EDIT1, strTime);
// 				KillTimer(nIDEvent);
// 				//AfxMessageBox(_T("Game Over!"));
// 				return;
// 			}
// 			m_nMinute = MAX_VALUE;
// 		}		
// 		m_nSecond = MAX_VALUE;
// 	}

	if (!m_nSecond)
	{
		if (!m_nMinute)
		{	
			if (!m_nHour)
			{
				
				//SetDlgItemText(IDC_EDIT1, _T("00 : 00 : 00"));
				//::SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_EDIT1, strTime);
				KillTimer(nIDEvent);
				m_nSecond = 0;
				m_pRecvInfo->m_dwShowOrder = RECVINFO_OVERTIME;
				GetDlgItem(ID_CANCEL_DAODIAN)->ShowWindow(TRUE);
				GetDlgItem(ID_CONFIM_RECVFULL)->ShowWindow(FALSE);
				GetDlgItem(ID_CONFIM_RECVLAST)->ShowWindow(FALSE);
				Invalidate(TRUE);
				//AfxMessageBox(_T("Game Over!"));
				return;
			}
			else
			{
				--m_nHour;
			}
			m_nMinute = MAX_VALUE;
		}
		else
		{
			--m_nMinute;
		}
		m_nSecond = MAX_VALUE;
	}

	Invalidate(TRUE);
}


void CRecvDlg::OnBnClickedCancelDaodian()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_nSecond != 0 || m_nMinute != 0 || m_nHour != 0)
	{
		AfxMessageBox(_T("此订单还未超时"));
		return;
	}

	m_pParent->DeleteRecvInfo(m_pRecvInfo->m_strOrderNum);
	m_pParent->SetRecvStatus(m_pRecvInfo->m_strOrderNum, RECVINFO_OVERTIME);
	m_pRecvInfo->m_dwShowOrder = RECVINFO_OVERTIME;

	m_pParent->UpdateRecvInfo();
	CDialog::OnOK();
}

// 退全款按钮
void CRecvDlg::OnBnClickedConfirmFull()
{
	CString strOrderUrl;
	strOrderUrl.LoadString(IDS_STRING_RECVFULL);

	strOrderUrl.Format(strOrderUrl, m_pRecvInfo->m_strOrderNum ,CUserInfoHolder::Instance()->GetUrlParam());
	CHttpClient* pHttpClient = new CHttpClient;
	LPCTSTR pJsonPostData = _T("");
	CString strResponse;

	if (pHttpClient)
	{
		pHttpClient->HttpPost(strOrderUrl, pJsonPostData, strResponse);
	}

	if (pHttpClient)
	{
		delete pHttpClient;
		pHttpClient = NULL;
	}

	// 删除了
	m_pParent->DeleteRecvInfo(m_pRecvInfo->m_strOrderNum);
	m_pParent->SetRecvStatus(m_pRecvInfo->m_strOrderNum, RECVINFO_OVERTIME);
	m_pRecvInfo->m_dwShowOrder = RECVINFO_OVERTIME;

	m_pParent->UpdateRecvInfo();
	AfxMessageBox(_T("退款成功"));
	CDialog::OnOK();
}

// 退余款按钮
void CRecvDlg::OnBnClickedConfirmLast()
{
	CString strOrderUrl;
	strOrderUrl.LoadString(IDS_STRING_RECVLAST);

	strOrderUrl.Format(strOrderUrl, m_pRecvInfo->m_strOrderNum, CUserInfoHolder::Instance()->GetUrlParam());
	CHttpClient* pHttpClient = new CHttpClient;
	LPCTSTR pJsonPostData = _T("");
	CString strResponse;

	if (pHttpClient)
	{
		pHttpClient->HttpPost(strOrderUrl, pJsonPostData, strResponse);
	}

	if (pHttpClient)
	{
		delete pHttpClient;
		pHttpClient = NULL;
	}

	m_pParent->DeleteRecvInfo(m_pRecvInfo->m_strOrderNum);
	m_pParent->SetRecvStatus(m_pRecvInfo->m_strOrderNum, RECVINFO_OVERTIME);
	m_pRecvInfo->m_dwShowOrder = RECVINFO_OVERTIME;

	m_pParent->UpdateRecvInfo();
	AfxMessageBox(_T("退款成功"));
	CDialog::OnOK();
}