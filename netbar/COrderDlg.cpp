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


// CNetbarDlg ��Ϣ�������

BOOL COrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COrderDlg::OnPaint()
{
	if (IsIconic())
	{
		
	}
	else
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		CRect rcDlg;
		GetClientRect(rcDlg);

		rcDlg.bottom -= 40;
		CRect rcDraw(rcDlg);
		
		dc.SetBkMode(TRANSPARENT);
		// ��һ�л��� 
		// λ��  ̨��  ʹ��ʱ��
		rcDraw.bottom = rcDraw.top + rcDlg.Height() / 3;
		DrawFirst(&dc, rcDraw);

		// �ڶ��л���
		// �û�Ҫ��
		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDraw.top + rcDlg.Height() / 3;
		DrawSecond(&dc, rcDraw);

		// �����л���
		// �û�����
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
	pDC->DrawText(m_pOrderInfo->m_strMachineNum + _T("̨"), rcDraw, DT_CENTER);
	pDC->DrawText(m_pOrderInfo->m_strUseTimer + _T("Сʱ"), rcDraw, DT_RIGHT);
	pDC->SelectObject(pFont);
}

void COrderDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{
	CFont* pFont = pDC->SelectObject(&m_font);
	rcDraw.top = rcDraw.top + 6;
	rcDraw.left = rcDraw.left + 5;
	rcDraw.right = rcDraw.right - 5;
	pDC->DrawText(m_pOrderInfo->m_strAdditional.Mid(10), rcDraw, DT_LEFT);
	pDC->SelectObject(pFont);
}

void COrderDlg::DrawMessage(CDC* pDC, CRect rcDraw)
{
	CFont* pFont = pDC->SelectObject(&m_font);
	rcDraw.top = rcDraw.top + 6;
	rcDraw.left = rcDraw.left + 5;
	rcDraw.right = rcDraw.right - 5;
	pDC->DrawText(m_pOrderInfo->m_strAdditional, rcDraw, DT_LEFT);
	pDC->SelectObject(pFont);
}

// ȡ������
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

	if (pHttpClient)
	{
		delete pHttpClient;
		pHttpClient = NULL;
	}
}	

// ȷ�Ͻӵ�
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

		// д�뵽
		m_pParent->InsertVcRecv(rcInfo);
		m_pParent->SetOrderStatus(m_pOrderInfo->m_strOrderNum, ORDERINFO_RECV);

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

		// ɾ��
		if (pHttpClient)
		{
			delete pHttpClient;
			pHttpClient = NULL;
		}
		
		CDialog::OnOK();
	}
}

void COrderDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

BOOL COrderDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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

	// TODO: �ڴ˴������Ϣ����������
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
		it->m_dwShowOrder = ORDERINFO_INIT;
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

// չʾ��������
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
		// ������µĶ���
		if (it->m_dwShowOrder == ORDERINFO_NEW)
		{
			m_bTest = TRUE;
			COrderDlg* pOrderDlg = new COrderDlg(&(*it), m_pNetBarDlg);
			pOrderDlg->SetParent(m_pNetBarDlg);

			pOrderDlg->Create(IDD_ORDER_DIALOG, m_pNetBarDlg);
			pOrderDlg->SetWindowPos(NULL, pt.x + 200, pt.y + 68, 380, 150, SWP_SHOWWINDOW | SWP_NOSIZE);
			pt.y += nHigh;
			pOrderDlg->ShowWindow(SW_SHOWNORMAL);

			it->m_dwShowOrder = ORDERINFO_SHOW;
			nCount--;
			m_nOrderShowCount++;
			m_vcOrderDlg.push_back(pOrderDlg);
		}
		// �ϵĶ���  �����û�ȡ�������
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

void COrderManager::InsertRecvOrder(RecvInfo pRecvInfo)
{
	m_vcRecvInfo.push_back(pRecvInfo);
}

// չʾ�ѽӶ���
void COrderManager::ShowRecvOrderInfo()
{
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

			pRecvDlg->Create(IDD_RECV_DIALOG, m_pNetBarDlg);

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
		if (dwStatus == ORDERINFO_DELETE || dwStatus == ORDERINFO_REMOVE )// �ж��Ƿ���Ҫɾ����dlg
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