#pragma once

#include <iostream>
#include <vector>
using namespace std;

// 订单信息
struct OrderInfo
{
	CString			m_strOrderNum;			// 订单编号
	CString			m_strLocate;			// 位置
	CString			m_strMachineNum;			// 电脑台数
	CString			m_strUseTimer;			// 使用时间
	CString			m_strAdditional;		// 用户要求
	CString			m_strMessage;			// 用户留言
	BOOL			m_bShowOrder;			// 订单显示

	OrderInfo()
	{
	}

	OrderInfo(OrderInfo* pOrderInfo)
	{
		m_strOrderNum = pOrderInfo->m_strOrderNum;
		m_strLocate = pOrderInfo->m_strLocate;
		m_strMachineNum = pOrderInfo->m_strMachineNum;
		m_strUseTimer = pOrderInfo->m_strUseTimer;
		m_strAdditional = pOrderInfo->m_strAdditional;
		m_strMessage = pOrderInfo->m_strMessage;
		m_bShowOrder = pOrderInfo->m_bShowOrder;
	}
};

typedef vector<OrderInfo> vcOrderInfo;
typedef vcOrderInfo::iterator  itOrderInfo;

class COrderDlg;
struct OrderDlgInfo
{
	COrderDlg* m_pOrderDlg;
	OrderInfo* m_pOrderInfo;
};

typedef vector<OrderDlgInfo> vcOrderDlg;
typedef vcOrderDlg::iterator	itOrderDlg;

// CNetbarDlg 对话框
class COrderDlg : public CDialog
{
	// 构造
public:
	COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent = NULL);	// 标准构造函数

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORDER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	void DrawFirst(CDC* pDC, CRect rcDraw);
	void DrawSecond(CDC* pDC, CRect rcDraw);
	void DrawMessage(CDC* pDC, CRect rcDraw);

	// 绘制
public:
	afx_msg void OnBnClickedCancelOrder();
	afx_msg void OnBnClickedConfirmOrder();

	//CString GetOrderNum();
	OrderInfo* m_pOrderInfo;
};

// 订单管理类
class COrderManager
{
public:
	COrderManager();
	~COrderManager();


	void InsertOrder(OrderInfo pOrderInfo);
	void DeleteOrder(const CString& strOrderNum);

	void CreateOrderInfo();
	void ShowOrderInfo();
	// 	BOOL DeleteOrder();
	// 	BOOL DeleteOrder();

private:
	vcOrderInfo		m_vcOrderInfo;
	//vcOrderDlg		m_vcOrderDlg;	// 订单vc
	vector<COrderDlg>	m_vcOrderDlg;
};