#include "stdafx.h"
#include "COrderDlg.h"
#include "netbarDlg.h"
#include "resource.h"
#include "CHttpClient.h"


COrderDlg::COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ORDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pOrderInfo = new OrderInfo(pOrderInfo);
	//m_pParent = pParent;
}

void COrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COrderDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_CANCEL_ORDER, &COrderDlg::OnBnClickedCancelOrder)
	ON_BN_CLICKED(ID_CONFIRM_ORDER, &COrderDlg::OnBnClickedConfirmOrder)
	ON_WM_CLOSE()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CNetbarDlg 消息处理程序

BOOL COrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COrderDlg::OnPaint()
{
	if (IsIconic())
	{
		
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		CRect rcDlg;
		GetClientRect(rcDlg);

		rcDlg.bottom -= 40;
		CRect rcDraw(rcDlg);
		
		// 第一行绘制 
		// 位置  台数  使用时间
		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
		DrawFirst(&dc, rcDraw);

		// 第二行绘制
		// 用户要求
		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
		DrawSecond(&dc, rcDraw);

		// 第三行绘制
		// 用户留言
		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDlg.bottom;
		DrawMessage(&dc, rcDraw);
		
		CDialog::OnPaint();
	}
}

void COrderDlg::DrawFirst(CDC* pDC, CRect rcDraw)
{
	pDC->DrawText(m_pOrderInfo->m_strLocate, rcDraw, DT_LEFT);
	pDC->DrawText(m_pOrderInfo->m_strMachineNum + _T("台"), rcDraw, DT_CENTER);
	pDC->DrawText(m_pOrderInfo->m_strUseTimer + _T("小时"), rcDraw, DT_RIGHT);
}

void COrderDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{
	pDC->DrawText(m_pOrderInfo->m_strMessage, rcDraw, DT_LEFT);
}

void COrderDlg::DrawMessage(CDC* pDC, CRect rcDraw)
{
	pDC->DrawText(m_pOrderInfo->m_strAdditional, rcDraw, DT_LEFT);
}

// 取消订单
void COrderDlg::OnBnClickedCancelOrder()
{
	CString strURL;
	strURL.LoadString(IDS_STRING_ORDEROP);
	strURL = strURL +  _T("cancel/") + m_pOrderInfo->m_strOrderNum + _T("?u=") + _T("eXdtZGRqZysyMTIxOGNjYTc3ODA0ZDJiYTE5MjJjMzNlMDE1MTEwNQ==");

	CHttpClient* pHttpClient = new CHttpClient;
	LPCTSTR pJsonPostData = _T("");
	CString strResponse;
	if (pHttpClient)
	{
		pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
	}
}	

// 确认接单
void COrderDlg::OnBnClickedConfirmOrder()
{
 	CString strURL;
 	strURL.LoadString(IDS_STRING_ORDEROP);
 	strURL = strURL + m_pOrderInfo->m_strOrderNum + _T("receive/");
// 
// 	CHttpClient* pHttpClient = new CHttpClient;
// 	LPCTSTR pJsonPostData = _T("");
// 	CString strResponse;
// 	if (pHttpClient)
// 	{
// 		pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
// 	}

	// 写入到
	m_pParent->InsertVcRecv();
}

void COrderDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialog::OnClose();
}


BOOL COrderDlg::PreTranslateMessage(MSG* pMsg)
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

void COrderDlg::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
}

void COrderDlg::SetParent(CNetbarDlg* pParent)
{
	m_pParent = pParent;
}

// CString CRecvDlg::GetOrderNum()
// {
// 	if (m_pOrderInfo)
// 	{
// 		m_pOrderInfo->m_strOrderNum;
// 	}
// }


//////////////////////////////////////////////////////////////////////////
/// COrderManager 
COrderManager::COrderManager(CNetbarDlg* pParent)
{
	m_pNetBarDlg = pParent;
	//m_vcOrderInfo.clear();
}


COrderManager::~COrderManager()
{

}


void COrderManager::InsertOrder(OrderInfo pOrderInfo)
{
	m_vcOrderInfo.push_back(pOrderInfo);
}

void COrderManager::DeleteOrder(const CString& strOrderNum)
{
	itOrderInfo it = m_vcOrderInfo.begin();
	for (; it != m_vcOrderInfo.end(); it++)
	{
		if (it->m_strOrderNum.CompareNoCase(strOrderNum) == 0)
		{
			m_vcOrderInfo.erase(it);
		}
	}
}

void COrderManager::CreateOrderInfo()
{
	itOrderInfo it = m_vcOrderInfo.begin();
	for (; it != m_vcOrderInfo.end(); it++)
	{
		COrderDlg* pOrderDlg = new COrderDlg(&(*it));
	}
}

void COrderManager::ShowOrderInfo()
{
	itOrderInfo it = m_vcOrderInfo.begin();
	CRect rc;
	GetClientRect(AfxGetMainWnd()->GetSafeHwnd(), rc);
	CPoint pt(rc.TopLeft());
	int nCount = m_vcOrderInfo.size();

	for (; it != m_vcOrderInfo.end(); it++)
	{
		COrderDlg* pOrderDlg = new COrderDlg(&(*it));
		pOrderDlg->SetParent(m_pNetBarDlg);
		
		pOrderDlg->Create(IDD_ORDER_DIALOG, NULL);
		pOrderDlg->ShowWindow(SW_SHOW);

		nCount--;

		m_vcOrderDlg.push_back(pOrderDlg);
	}
}

void COrderManager::ShowRecvOrderInfo()
{

	CRecvDlg* pRecvDlg = new CRecvDlg();
	pRecvDlg->SetParent(m_pNetBarDlg);

	pRecvDlg->Create(IDD_RECV_DIALOG, NULL);
	pRecvDlg->ShowWindow(SW_SHOW);

	//nCount--;

	m_vcRecvDlg.push_back(pRecvDlg);
	return ;

	vector<CRecvDlg*>::iterator it = m_vcRecvDlg.begin();
	CRect rc;
	GetClientRect(AfxGetMainWnd()->GetSafeHwnd(), rc);
	CPoint pt(rc.TopLeft());
	int nCount = m_vcRecvDlg.size();

	for (; it != m_vcRecvDlg.end(); it++)
	{
		CRecvDlg* pRecvDlg = new CRecvDlg();
		pRecvDlg->SetParent(m_pNetBarDlg);

		pRecvDlg->Create(IDD_RECV_DIALOG, NULL);
		pRecvDlg->ShowWindow(SW_SHOW);

		nCount--;

		m_vcRecvDlg.push_back(pRecvDlg);
	}
}

void COrderManager::MoveWindow(CRect rcClient)
{
	vector<COrderDlg*>::iterator itOrder = m_vcOrderDlg.begin();
	COrderDlg* ptemp = nullptr;

	CPoint pt(rcClient.TopLeft());
	for (; itOrder != m_vcOrderDlg.end(); itOrder++)
	{
		ptemp = *itOrder;
		ptemp->SetWindowPos(NULL, pt.x + 200, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
	}

	vector<CRecvDlg*>::iterator itRecv = m_vcRecvDlg.begin();
	CRecvDlg* pTempRecv = nullptr;
	for (; itRecv != m_vcRecvDlg.end(); itRecv++)
	{
		pTempRecv = *itRecv;
		pTempRecv->SetWindowPos(NULL, pt.x + 552, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
	}
}