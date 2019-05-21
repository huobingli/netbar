#include "stdafx.h"
#include "COrderDlg.h"
#include "netbarDlg.h"
#include "resource.h"
#include "CHttpClient.h"
#include "CMachineOrder.h"
#include "CUserInfo.h"

COrderDlg::COrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ORDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_font.CreateFont(15, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("宋体"));

	m_fontMessage.CreateFont(12, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("宋体"));
}

COrderDlg::COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ORDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pOrderInfo = new OrderInfo(pOrderInfo);
	//m_pParent = pParent;

	m_font.CreateFont(15, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("宋体"));

	m_fontMessage.CreateFont(12, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("宋体"));
}

COrderDlg::~COrderDlg()
{
	if (m_pOrderInfo)
	{
		delete m_pOrderInfo;
		m_pOrderInfo = NULL;
	}
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

		rcDlg.bottom -= 30;
		CRect rcDraw(rcDlg);
		
		dc.SetBkMode(TRANSPARENT);
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

void COrderDlg::SetOrderInfo(OrderInfo* pOrderInfo)
{
	m_pOrderInfo = new OrderInfo(pOrderInfo);
}

void COrderDlg::DrawFirst(CDC* pDC, CRect rcDraw)
{
	CFont* pFont = pDC->SelectObject(&m_font);
	rcDraw.top = rcDraw.top + 6;
	rcDraw.left = rcDraw.left + 5;
	rcDraw.right = rcDraw.right - 5;
	pDC->DrawText(m_pOrderInfo->m_strLocate, rcDraw, DT_LEFT);
	pDC->DrawText(m_pOrderInfo->m_strMachineNum + _T("台"), rcDraw, DT_CENTER);
	pDC->DrawText(m_pOrderInfo->m_strUseTimer + _T("小时"), rcDraw, DT_RIGHT);
	pDC->SelectObject(pFont);
}

void COrderDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{
	CFont* pFont = pDC->SelectObject(&m_font);
	rcDraw.top = rcDraw.top + 6;
	rcDraw.left = rcDraw.left + 5;
	rcDraw.right = rcDraw.right - 5;
	pDC->DrawText(m_pOrderInfo->m_strMessage, rcDraw, DT_LEFT);
	pDC->SelectObject(pFont);
}

void COrderDlg::DrawMessage(CDC* pDC, CRect rcDraw)
{
	CFont* pFont = pDC->SelectObject(&m_fontMessage);
	rcDraw.top = rcDraw.top + 6;
	rcDraw.left = rcDraw.left + 5;
	rcDraw.right = rcDraw.right - 5;
	pDC->DrawText(m_pOrderInfo->m_strAdditional, rcDraw, DT_LEFT);
	pDC->SelectObject(pFont);
}

// 取消订单
void COrderDlg::OnBnClickedCancelOrder()
{
	// http://api.ljgzh.com/order/op/cancel/365?u=eXdtZGRqZysyMTIxOGNjYTc3ODA0ZDJiYTE5MjJjMzNlMDE1MTEwNQ==&staff_id=16
	// http://api.ljgzh.com/order/op/cancel/%s/u=%s&staff_id=%s
	CString strURL;
	strURL.LoadString(IDS_STRING_ORDERCANCEL1);
	strURL.Format(strURL, m_pOrderInfo->m_strOrderNum, CUserInfoHolder::Instance()->GetUrlParam(), CUserInfoHolder::Instance()->GetStaffInfo());

	CHttpClient* pHttpClient = new CHttpClient;
	LPCTSTR pJsonPostData = _T("");
	CString strResponse;
	if (pHttpClient)
	{
		pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
	}
	
	m_pParent->DeleteOrderInfo(m_pOrderInfo->m_strOrderNum);
	m_pParent->SetOrderStatus(m_pOrderInfo->m_strOrderNum, ORDERINFO_DELETE);
	m_pOrderInfo->m_dwShowOrder = ORDERINFO_DELETE;

	if (pHttpClient)
	{
		delete pHttpClient;
		pHttpClient = NULL;
	}
	
	m_pParent->UpdateOrderInfo();

	CDialog::OnOK();
}	

// 确认接单
void COrderDlg::OnBnClickedConfirmOrder()
{
	CMachineOrderDlg pDlg;
	pDlg.SetParent(this);
	pDlg.SetMachineCount(atoi(m_pOrderInfo->m_strMachineNum));
	if (pDlg.DoModal() == IDOK)
	{
		RecvInfo rcInfo;
		rcInfo.m_strOrderNum = m_pOrderInfo->m_strOrderNum;
		rcInfo.m_strArriveTimer = m_pOrderInfo->m_strUseTimer;
		rcInfo.m_strMachineNum = m_pOrderInfo->m_strMachineNum;
		rcInfo.m_strMachineList = m_strMachineList;

		// 写入到
		m_pParent->InsertVcRecv(rcInfo);
		m_pParent->SetOrderStatus(m_pOrderInfo->m_strOrderNum, ORDERINFO_RECV);
		m_pOrderInfo->m_dwShowOrder = ORDERINFO_RECV;

		// http://api.ljgzh.com/order/op/receive/370?u=eXdtZGRqZysyMTIxOGNjYTc3ODA0ZDJiYTE5MjJjMzNlMDE1MTEwNQ==&staff_id=16&seats=1,2
		// http://api.ljgzh.com/order/op/receive/%s/u=%s&staff_id=%s&seats=%s
		
		CString strURL;
		strURL.LoadString(IDS_STRING_ORDERRECV);
		strURL.Format(strURL, m_pOrderInfo->m_strOrderNum,  CUserInfoHolder::Instance()->GetUrlParam(), CUserInfoHolder::Instance()->GetStaffInfo(), m_strMachineList);

		CHttpClient* pHttpClient = new CHttpClient;
		LPCTSTR pJsonPostData = _T("");
		CString strResponse;
		if (pHttpClient)
		{
			pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
		}

		// 删除
		if (pHttpClient)
		{
			delete pHttpClient;
			pHttpClient = NULL;
		}

		m_pParent->UpdateOrderInfo();
		
		CDialog::OnOK();
	}
}

void COrderDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
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

//////////////////////////////////////////////////////////////////////////
/// COrderManager 
COrderManager::COrderManager(CNetbarDlg* pParent)
{
	m_pNetBarDlg = pParent;
	//m_vcOrderInfo.clear();
	m_nOrderShowCount = 0;
	m_bNewOrder = FALSE;
}


COrderManager::~COrderManager()
{

}

void COrderManager::ResetOrder()
{
	itOrderInfo it = m_vcOrderInfo.begin();
	for (; it != m_vcOrderInfo.end(); it++)
	{
		it->m_dwShowOrder = ORDERINFO_INIT;
	}
}

void COrderManager::InsertOrder(OrderInfo pOrderInfo)
{
	m_vcOrderInfo.push_back(pOrderInfo);
	m_bNewOrder = TRUE;
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
		if (it->m_dwShowOrder == ORDERINFO_NEW)
		{
			//COrderDlg* pOrderDlg = new COrderDlg(&(*it), m_pNetBarDlg);
			COrderDlg* pOrderDlg = new COrderDlg(m_pNetBarDlg);
			pOrderDlg->SetParent(m_pNetBarDlg);
			it->m_dwShowOrder = ORDERINFO_SHOW;
			pOrderDlg->SetOrderInfo(&(*it));

			pOrderDlg->Create(IDD_ORDER_DIALOG, m_pNetBarDlg);
			
			pOrderDlg->SetWindowPos(NULL, pt.x + 200, pt.y + nHigh * m_nOrderShowCount + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			pOrderDlg->ShowWindow(SW_SHOWNORMAL);
			
			m_nOrderShowCount++;
			m_vcOrderDlg.push_back(pOrderDlg);
		}
		// 老的订单  存在用户取消的情况
		else
		{
			if(it->m_dwShowOrder == ORDERINFO_RECV || it->m_dwShowOrder == ORDERINFO_INIT || it->m_dwShowOrder == ORDERINFO_DELETE || it->m_dwShowOrder == ORDERINFO_REMOVE)
			{			
				HideOrderDlg(it->m_strOrderNum);
				m_nOrderShowCount--;
			}
		}
	}

	CloseCancelOrder();
}

void COrderManager::UpdateOrderInfo()
{
	CRect rc;
	m_pNetBarDlg->GetClientRect(rc);
	m_pNetBarDlg->ClientToScreen(rc);
	CPoint pt(rc.TopLeft());

	vector<COrderDlg*>::iterator it = m_vcOrderDlg.begin();
	COrderDlg* pTmp = nullptr;

	// 接单
	int nHigh = 130;
	for (; it != m_vcOrderDlg.end(); it++)
	{
		pTmp = *it;
		DWORD dwStatus = pTmp->GetOrderInfoStatus();
		if (dwStatus == ORDERINFO_SHOW)
		{
			pTmp->SetWindowPos(NULL, pt.x + 200, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			pt.y += nHigh;
			pTmp->ShowWindow(SW_SHOW);
		}
	}
}

void COrderManager::UpdateRecvInfo()
{
	CRect rc;
	m_pNetBarDlg->GetClientRect(rc);
	m_pNetBarDlg->ClientToScreen(rc);
	CPoint pt(rc.TopLeft());

	// 接单
	pt = rc.TopLeft();
	int nHighRecv = 90;
	vector<CRecvDlg*>::iterator itRecv = m_vcRecvDlg.begin();
	CRecvDlg* pTmp = nullptr;
	for (; itRecv != m_vcRecvDlg.end(); itRecv++)
	{
		pTmp = *itRecv;
		DWORD dwStatus = pTmp->GetRecvInfoStatus();
		if (dwStatus == RECVINFO_SHOW)
		{
			pTmp->SetWindowPos(NULL, pt.x + 552, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			pt.y += nHighRecv;
			pTmp->ShowWindow(SW_SHOW);
		}
	}
}

void COrderManager::DeleteRecvInfo(const CString& strOrderNum)
{
	itRecvInfo it = m_vcRecvInfo.begin();
	itRecvInfo itDelete;

	RecvInfo* pInfo = nullptr;
	for (; it != m_vcRecvInfo.end(); it++)
	{
		pInfo = &(*it);

		if (pInfo->m_strOrderNum.CompareNoCase(strOrderNum) == 0)
		{
			itDelete = it;
			m_vcRecvInfo.erase(itDelete);

			return;
		}
	}
}

void COrderManager::SetRecvStatus(const CString& strOrderNum, DWORD dwStatus)
{
	itRecvInfo it = m_vcRecvInfo.begin();
	for (; it != m_vcRecvInfo.end(); it++)
	{
		if (it->m_strOrderNum.CompareNoCase(strOrderNum) == 0)
		{
			it->m_dwShowOrder = dwStatus;
		}
	}
}

void COrderManager::CloseRecvOrder()
{
	vector<CRecvDlg*>::iterator it = m_vcRecvDlg.begin();
	CString strNum;
	CRecvDlg* pTmp = nullptr;
	for (; it != m_vcRecvDlg.end(); it++)
	{
		pTmp = *it;
		strNum = pTmp->GetOrderInfoNum();
		DWORD dwStatus = pTmp->GetRecvInfoStatus();
		if (dwStatus == RECVINFO_OVERTIME)// 判断是否需要删除的dlg
		{
			m_vcRecvDlg.erase(it);

			if (pTmp)
			{
				delete pTmp;
				pTmp = NULL;
			}

			return;
		}
	}
}

void COrderManager::InsertRecvOrder(RecvInfo pRecvInfo)
{
	m_vcRecvInfo.push_back(pRecvInfo);
}

// 展示已接订单
void COrderManager::ShowRecvOrderInfo()
{
	itRecvInfo it = m_vcRecvInfo.begin();
	CRect rc;
	m_pNetBarDlg->GetClientRect(rc);
	m_pNetBarDlg->ClientToScreen(rc);
	CPoint pt(rc.TopLeft());
	int nCount = m_vcRecvInfo.size();

	int nHigh = 90;
	for (; it != m_vcRecvInfo.end(); it++)
	{
		if (it->m_dwShowOrder == RECVINFO_INIT)
		{
			it->m_dwShowOrder = RECVINFO_SHOW;
			CRecvDlg* pRecvDlg = new CRecvDlg(&(*it));
			pRecvDlg->SetParent(m_pNetBarDlg);

			pRecvDlg->Create(IDD_RECV_DIALOG, m_pNetBarDlg);

			pRecvDlg->SetWindowPos(NULL, pt.x + 552, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			
			pRecvDlg->ShowWindow(SW_SHOW);

			m_vcRecvDlg.push_back(pRecvDlg);
		}
		pt.y += nHigh;
	}

CloseRecvOrder();
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
	int nHighRecv = 90;
	for (; itRecv != m_vcRecvDlg.end(); itRecv++)
	{
		pTempRecv = *itRecv;
		int n = pTempRecv->IsWindowVisible();
		if (n)
		{
			pTempRecv->SetWindowPos(NULL, ptRecv.x + 552, ptRecv.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			ptRecv.y += nHighRecv;
		}
	}
}

void COrderManager::SetOrderStatus(const CString& strOrderNum, DWORD dwStatus)
{
	itOrderInfo it = m_vcOrderInfo.begin();
	for (; it != m_vcOrderInfo.end(); it++)
	{
		if (it->m_strOrderNum.CompareNoCase(strOrderNum) == 0)
		{
			it->m_dwShowOrder = dwStatus;
		}
	}
}

BOOL COrderManager::IsAlreadyInit(const CString& strOrderNum)
{
	itOrderInfo it = m_vcOrderInfo.begin();
	for (; it != m_vcOrderInfo.end(); it++)
	{
		if (it->m_strOrderNum.CompareNoCase(strOrderNum) == 0)
		{
			if (it->m_dwShowOrder == ORDERINFO_INIT)
			{
				it->m_dwShowOrder = ORDERINFO_SHOW;
				return TRUE;
			}
		}
	}

	return FALSE;
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
		DWORD dwStatus = pTmp->GetOrderInfoStatus();
		if (dwStatus == ORDERINFO_DELETE || dwStatus == ORDERINFO_REMOVE )// 判断是否需要删除的dlg
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
			pTmp->SetOrderInfoStatus(ORDERINFO_DELETE);
			return;
		}
	}
}