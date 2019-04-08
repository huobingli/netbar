#include "stdafx.h"
#include "COrderDlg.h"
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
		
		// ��һ�л��� 
		// λ��  ̨��  ʹ��ʱ��
		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
		DrawFirst(&dc, rcDraw);

		// �ڶ��л���
		// �û�Ҫ��
		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
		DrawSecond(&dc, rcDraw);

		// �����л���
		// �û�����
		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDlg.bottom;
		DrawMessage(&dc, rcDraw);
		
		CDialog::OnPaint();
	}
}

void COrderDlg::DrawFirst(CDC* pDC, CRect rcDraw)
{
	pDC->DrawText(m_pOrderInfo->m_strLocate, rcDraw, DT_LEFT);
	pDC->DrawText(m_pOrderInfo->m_strMachineNum + _T("̨"), rcDraw, DT_CENTER);
	pDC->DrawText(m_pOrderInfo->m_strUseTimer + _T("Сʱ"), rcDraw, DT_RIGHT);
}

void COrderDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{
	pDC->DrawText(m_pOrderInfo->m_strMessage, rcDraw, DT_LEFT);
}

void COrderDlg::DrawMessage(CDC* pDC, CRect rcDraw)
{
	pDC->DrawText(m_pOrderInfo->m_strAdditional, rcDraw, DT_LEFT);
}

// ȡ������
void COrderDlg::OnBnClickedCancelOrder()
{
	CString strURL;
	strURL.LoadString(IDS_STRING_ORDEROP);
	strURL = strURL +  _T("cancel/") + m_pOrderInfo->m_strOrderNum + _T("?u=") + ;

	CHttpClient* pHttpClient = new CHttpClient;
	LPCTSTR pJsonPostData = _T("");
	CString strResponse;
	if (pHttpClient)
	{
		pHttpClient->HttpPost(strURL, pJsonPostData, strResponse);
	}
}	

// ȷ�Ͻӵ�
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
}

void COrderDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CDialog::OnClose();
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

// CString COrderDlg::GetOrderNum()
// {
// 	if (m_pOrderInfo)
// 	{
// 		m_pOrderInfo->m_strOrderNum;
// 	}
// }


//////////////////////////////////////////////////////////////////////////
/// COrderManager 
COrderManager::COrderManager()
{
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
	int nCount = m_vcOrderInfo.size();
	int nX = rc.left + 40;
	int nY = rc.bottom;
	for (; it != m_vcOrderInfo.end(); it++)
	{
		COrderDlg* pOrderDlg = new COrderDlg(&(*it));
		pOrderDlg->Create(IDD_ORDER_DIALOG, NULL);
		pOrderDlg->ShowWindow(SW_SHOW);
		pOrderDlg->MoveWindow(nX, nY, 320, 186);
		nY += 200;
		nCount--;
	}
}


