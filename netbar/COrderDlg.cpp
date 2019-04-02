#include "stdafx.h"
#include "COrderDlg.h"
#include "resource.h"


COrderDlg::COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent /*=NULL*/)
	: CDialog(IDD_ORDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pOrderInfo = new OrderInfo(pOrderInfo);
}

void COrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COrderDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_CANCEL_ORDER, &COrderDlg::OnBnClickedCancelOrder)
	ON_BN_CLICKED(ID_CONFIRM_ORDER, &COrderDlg::OnBnClickedConfirmOrder)
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

}

// ȷ�Ͻӵ�
void COrderDlg::OnBnClickedConfirmOrder()
{

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
		//if ()
		COrderDlg* pOrderDlg = new COrderDlg(&(*it));
		/*m_vcOrderDlg.push_back(*pOrderDlg);*/
		//it->m_pOrderDlg->MoveWindow();
	}
	
	//pOrderDlg->
	/*m_vcOrderDlg.push_back(pOrderDlg);*/
}

void COrderManager::ShowOrderInfo()
{
// 	vector<COrderDlg>::iterator it = m_vcOrderDlg.begin();
// 	for (; it != m_vcOrderDlg.end(); it++)
// 	{
// 		it->DoModal();
// 		//it->m_pOrderDlg->MoveWindow();
// 	}

	itOrderInfo it = m_vcOrderInfo.begin();
	CRect rc;
	GetClientRect(AfxGetMainWnd()->GetSafeHwnd(), rc);
	int nCount = m_vcOrderInfo.size();
	int nX = rc.left + 40;
	int nY = rc.bottom;
	for (; it != m_vcOrderInfo.end(); it++)
	{
		//if ()
		COrderDlg* pOrderDlg = new COrderDlg(&(*it));
		pOrderDlg->Create(IDD_ORDER_DIALOG, NULL);
		pOrderDlg->ShowWindow(SW_SHOW);
		pOrderDlg->MoveWindow(nX, nY, 320, 186);
		nY += 200;
		nCount--;
		/*m_vcOrderDlg.push_back(*pOrderDlg);*/
		//it->m_pOrderDlg->MoveWindow();
	}
}