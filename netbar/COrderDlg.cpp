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

		CRect rcDraw(rcDlg);
		rcDraw.bottom -= 40;
		// ��һ�л��� 
		// λ��  ̨��  ʹ��ʱ��
		DrawFirst(&dc, rcDraw);

		// �ڶ��л���
		// �û�Ҫ��
		DrawSecond(&dc, rcDraw);

		// �����л���
		// �û�����
		DrawMessage(&dc, rcDraw);
		
		CDialog::OnPaint();
	}
}

void COrderDlg::DrawFirst(CDC* pDC, CRect rcDraw)
{

}

void COrderDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{

}

void COrderDlg::DrawMessage(CDC* pDC, CRect rcDraw)
{

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
	for (; it != m_vcOrderInfo.end(); it++)
	{
		//if ()
		COrderDlg* pOrderDlg = new COrderDlg(&(*it));
		/*m_vcOrderDlg.push_back(*pOrderDlg);*/
		//it->m_pOrderDlg->MoveWindow();
	}
}