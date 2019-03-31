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

		CRect rcDraw(rcDlg);
		rcDraw.bottom -= 40;
		// 第一行绘制 
		// 位置  台数  使用时间
		DrawFirst(&dc, rcDraw);

		// 第二行绘制
		// 用户要求
		DrawSecond(&dc, rcDraw);

		// 第三行绘制
		// 用户留言
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

// 取消订单
void COrderDlg::OnBnClickedCancelOrder()
{

}

// 确认接单
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