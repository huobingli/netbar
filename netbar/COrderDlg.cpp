#include "stdafx.h"
#include "COrderDlg.h"
#include "netbarDlg.h"
#include "resource.h"
#include "CHttpClient.h"
#include "CMachineOrder.h"


COrderDlg::COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ORDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pOrderInfo = new OrderInfo(pOrderInfo);
	//m_pParent = pParent;

	m_font.CreateFont(15, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
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
		rcDraw.bottom = rcDraw.top + rcDlg.Height() / 3;
		DrawFirst(&dc, rcDraw);

		// 第二行绘制
		// 用户要求
		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDraw.top + rcDlg.Height() / 3;
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
	CFont* pFont = pDC->SelectObject(&m_font);
	pDC->DrawText(m_pOrderInfo->m_strLocate, rcDraw, DT_LEFT);
	pDC->DrawText(m_pOrderInfo->m_strMachineNum + _T("台"), rcDraw, DT_CENTER);
	pDC->DrawText(m_pOrderInfo->m_strUseTimer + _T("小时"), rcDraw, DT_RIGHT);
	pDC->SelectObject(pFont);
}

void COrderDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{
	CFont* pFont = pDC->SelectObject(&m_font);
	pDC->DrawText(m_pOrderInfo->m_strMessage, rcDraw, DT_LEFT);
	pDC->SelectObject(pFont);
}

void COrderDlg::DrawMessage(CDC* pDC, CRect rcDraw)
{
	CFont* pFont = pDC->SelectObject(&m_font);
	pDC->DrawText(m_pOrderInfo->m_strAdditional, rcDraw, DT_LEFT);
	pDC->SelectObject(pFont);
}

// 取消订单
void COrderDlg::OnBnClickedCancelOrder()
{
	CString strURL;
	strURL.LoadString(IDS_STRING_ORDERCANCEL);
	strURL = strURL +  _T("cancel/") + m_pOrderInfo->m_strOrderNum + _T("?u=") + _T("eXdtZGRqZysyMTIxOGNjYTc3ODA0ZDJiYTE5MjJjMzNlMDE1MTEwNQ==");

	CHttpClient* pHttpClient = new CHttpClient;
	LPCTSTR pJsonPostData = _T("");
	CString strResponse;
	if (pHttpClient)
	{
	//	pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
	}
	
	m_pParent->DeleteOrderInfo(m_pOrderInfo->m_strOrderNum);
}	

// 确认接单
void COrderDlg::OnBnClickedConfirmOrder()
{
 	CString strURL;
 	strURL.LoadString(IDS_STRING_ORDERRECV);
 	strURL = strURL + m_pOrderInfo->m_strOrderNum + _T("receive/");

 	CHttpClient* pHttpClient = new CHttpClient;
 	LPCTSTR pJsonPostData = _T("");
 	CString strResponse;
 	if (pHttpClient)
 	{
 		//pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
 	}

	CMachineOrderDlg pDlg;
	pDlg.SetParent(this);
	pDlg.SetMachineCount(atoi(m_pOrderInfo->m_strMachineNum));
	pDlg.DoModal();

	RecvInfo rcInfo;
	rcInfo.m_strOrderNum = m_pOrderInfo->m_strOrderNum;
	rcInfo.m_strArriveTimer = m_pOrderInfo->m_strUseTimer;
	rcInfo.m_strMachineNum = m_pOrderInfo->m_strMachineNum;
	rcInfo.m_strMachineList = m_strMachineList;
	
	// 写入到
	m_pParent->InsertVcRecv(rcInfo);
}

void COrderDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

// void COrderDlg::CloseWindow()
// {
// 	CDialog::OnCancel();
// }

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

// BOOL COrderDlg::CloseDlg(const CString& strOrderNum)
// {
// 	CDialog::OnCancel()
// }

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

	m_bTest = FALSE;
}


COrderManager::~COrderManager()
{

}

void COrderManager::ResetOrder()
{
	itOrderInfo it = m_vcOrderInfo.begin();
	for (; it != m_vcOrderInfo.end(); it++)
	{
// 		if (it->m_strOrderNum.CompareNoCase(strOrderNum) == 0)
// 		{
// 			m_vcOrderInfo.erase(it);
// 		}
		it->m_bUpdate = FALSE;
	}
}

void COrderManager::InsertOrder(OrderInfo pOrderInfo)
{
	m_vcOrderInfo.push_back(pOrderInfo);
}

void COrderManager::DeleteOrder(const CString& strOrderNum)
{
	itOrderInfo it = m_vcOrderInfo.begin();
	itOrderInfo itDelete;

	OrderInfo* pInfo = nullptr;
	for (; it != m_vcOrderInfo.end(); it++)
	{
		pInfo = &(*it);

		if (pInfo->m_strOrderNum.CompareNoCase(strOrderNum) == 0)
		{
			itDelete = it;
			m_vcOrderInfo.erase(itDelete);

			return ;
		}
	}
}

//void COrderManager::CreateOrderInfo()
//{
//	itOrderInfo it = m_vcOrderInfo.begin();
//	for (; it != m_vcOrderInfo.end(); it++)
//	{
//		COrderDlg* pOrderDlg = new COrderDlg(&(*it));
//	}
//}

// 展示订单数据
void COrderManager::ShowOrderInfo()
{
	itOrderInfo it = m_vcOrderInfo.begin();
	CRect rc;

	m_pNetBarDlg->GetClientRect(rc);
	m_pNetBarDlg->ClientToScreen(rc);
	CPoint pt(rc.TopLeft());
	
 	int nHigh = 130;

	int nCount = m_vcOrderInfo.size();
	
	for (; it != m_vcOrderInfo.end(); it++)
	{
		// 如果是新的订单
		if (it->m_bShowOrder != TRUE && m_bTest == FALSE)
		{
			m_bTest = TRUE;
			COrderDlg* pOrderDlg = new COrderDlg(&(*it), m_pNetBarDlg);
			pOrderDlg->SetParent(m_pNetBarDlg);

			pOrderDlg->Create(IDD_ORDER_DIALOG, NULL);
			pOrderDlg->SetWindowPos(NULL, pt.x + 200, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			pt.y += nHigh;
			//pOrderDlg->MoveWindow(rcDlg);
			pOrderDlg->ShowWindow(SW_SHOWNORMAL);

			it->m_bShowOrder = TRUE;
			nCount--;
			m_nOrderShowCount++;
			m_vcOrderDlg.push_back(pOrderDlg);
		}
		else
		{
			if(it->m_bUpdate == FALSE)
			{			
				HideOrderDlg(it->m_strOrderNum);
				m_nOrderShowCount--;
			}
		}
	}

	CloseCancelOrder();
}

void COrderManager::InsertRecvOrder(RecvInfo pRecvInfo)
{
	m_vcRecvInfo.push_back(pRecvInfo);
}

// 展示已接订单
void COrderManager::ShowRecvOrderInfo()
{
	//CRecvDlg* pRecvDlg = new CRecvDlg(m_pNetBarDlg);
	//pRecvDlg->SetParent(m_pNetBarDlg);

	//pRecvDlg->Create(IDD_RECV_DIALOG, NULL);
	//pRecvDlg->ShowWindow(SW_SHOWNORMAL);

	////nCount--;

	//m_vcRecvDlg.push_back(pRecvDlg);
	//return ;

	itRecvInfo it = m_vcRecvInfo.begin();
	CRect rc;
	m_pNetBarDlg->GetClientRect(rc);
	m_pNetBarDlg->ClientToScreen(rc);
	CPoint pt(rc.TopLeft());
	int nCount = m_vcRecvInfo.size();

	int nHigh = 80;
	for (; it != m_vcRecvInfo.end(); it++)
	{
		if (it->m_bShowOrder == FALSE)
		{
			it->m_bShowOrder = TRUE;
			CRecvDlg* pRecvDlg = new CRecvDlg(&(*it));
			pRecvDlg->SetParent(m_pNetBarDlg);

			pRecvDlg->Create(IDD_RECV_DIALOG, NULL);

			pRecvDlg->SetWindowPos(NULL, pt.x + 552, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			pt.y += nHigh;
			pRecvDlg->ShowWindow(SW_SHOW);

			nCount--;

			m_vcRecvDlg.push_back(pRecvDlg);
		}
	}
}

void COrderManager::MoveWindow(CRect rcClient)
{
	vector<COrderDlg*>::iterator itOrder = m_vcOrderDlg.begin();
	COrderDlg* ptemp = nullptr;

	CPoint pt(rcClient.TopLeft());
	int nHigh = 130;

	CPoint ptOrder(pt);
	for (; itOrder != m_vcOrderDlg.end(); itOrder++)
	{
		ptemp = *itOrder;
		int m = ptemp->IsWindowVisible();
		if (m)
		{
			ptemp->SetWindowPos(NULL, ptOrder.x + 200, ptOrder.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			ptOrder.y += nHigh;
		}
	}

	vector<CRecvDlg*>::iterator itRecv = m_vcRecvDlg.begin();
	CRecvDlg* pTempRecv = nullptr;

	CPoint ptRecv(pt);
	for (; itRecv != m_vcRecvDlg.end(); itRecv++)
	{
		pTempRecv = *itRecv;
		int n = pTempRecv->IsWindowVisible();
		if (n)
		{
			pTempRecv->SetWindowPos(NULL, ptRecv.x + 552, ptRecv.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
		}
	}
}

BOOL COrderManager::IsAlreadyShow(const CString& strOrder)
{
	itOrderInfo it = m_vcOrderInfo.begin();
	for (; it != m_vcOrderInfo.end(); it++)
	{
		if (it->m_strOrderNum.CompareNoCase(strOrder) == 0)
		{
			it->m_bUpdate = TRUE;
			return TRUE;
		}
	}

	return FALSE;
}

void COrderManager::UpdateOrderInfo()
{
	itOrderInfo it = m_vcOrderInfo.begin(); 
	itOrderInfo itDelete;
	for (; it != m_vcOrderInfo.end(); it++)
	{
		if (it->m_bUpdate == FALSE)
		{
			itDelete = it;
			m_vcOrderInfo.erase(itDelete);

			return;
		}
	}
}

void COrderManager::CloseCancelOrder()
{
	vector<COrderDlg*>::iterator it = m_vcOrderDlg.begin();
	CString strNum;
	COrderDlg* pTmp = nullptr;
	for (; it != m_vcOrderDlg.end(); it++)
	{
		pTmp = *it;
		strNum = pTmp->GetOrderInfoNum();
		if (/*strNum.CompareNoCase(strOrderNum)*/pTmp->GetOrderInfoUpdate() == 0)
		{
			pTmp->OnClose();
			m_vcOrderDlg.erase(it);
			DeleteOrder(strNum);

			if (pTmp)
			{
				delete pTmp;
				pTmp = NULL;
			}

			return ;
		}
	}
}

void COrderManager::HideOrderDlg(const CString& strOrderNum)
{
	vector<COrderDlg*>::iterator it = m_vcOrderDlg.begin();
	CString strNum;
	COrderDlg* pTmp = nullptr;
	for (; it != m_vcOrderDlg.end(); it++)
	{
		pTmp = *it;
		strNum = pTmp->GetOrderInfoNum();
		if (strNum.CompareNoCase(strOrderNum) == 0)
		{
			pTmp->ShowWindow(SW_HIDE);
			pTmp->SetOrderInfoUpdate(FALSE);
			return;
		}
	}
}