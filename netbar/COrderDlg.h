#pragma once
#include "CRecviceOrder.h"
#include <iostream>
#include <vector>
using namespace std;


// 订单信息
struct OrderInfo
{
	CString			m_strOrderNum;			// 订单编号
	CString			m_strLocate;			// 位置
	CString			m_strMachineNum;		// 电脑台数
	CString			m_strUseTimer;			// 使用时间
	CString			m_strAdditional;		// 用户要求
	CString			m_strMessage;			// 用户留言
	BOOL			m_bShowOrder;			// 订单显示 新订单为FALSE  显示之后的新订单为TRUE

	BOOL			m_bUpdate;				// 更新标志

	OrderInfo()
	{
		m_bShowOrder = FALSE;
		m_bUpdate = TRUE;
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
		m_bUpdate = pOrderInfo->m_bUpdate;
	}
};

typedef vector<OrderInfo> vcOrderInfo;
typedef vcOrderInfo::iterator  itOrderInfo;

class COrderDlg;
class CRecvDlg;
struct OrderDlgInfo
{
	COrderDlg* m_pOrderDlg;
	OrderInfo* m_pOrderInfo;
};

typedef vector<OrderDlgInfo> vcOrderDlg;
typedef vcOrderDlg::iterator	itOrderDlg;

// CNetbarDlg 对话框
class CNetbarDlg;
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
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);

	CString GetOrderInfoNum() { return m_pOrderInfo->m_strOrderNum; }
	BOOL GetOrderInfoUpdate() { return m_pOrderInfo->m_bUpdate; }
	void SetOrderInfoUpdate(BOOL bUpdate) { m_pOrderInfo->m_bUpdate = bUpdate; }
	void CloseDlg() { CDialog::OnClose(); }

	void SetMachineList(const CString& strList) { m_strMachineList = strList; }
	//CString GetOrderNum();
	OrderInfo* m_pOrderInfo;
	
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetParent(CNetbarDlg* pParent);
private:
	CNetbarDlg* m_pParent;
	CFont		m_font;			// 字体

	CString		m_strMachineList;
public:
	
};

// 订单管理类
class COrderManager
{
public:
	COrderManager(CNetbarDlg* pParent);
	~COrderManager();

	// 订单数据 方法
	void ResetOrder();
	void InsertOrder(OrderInfo pOrderInfo);
	void DeleteOrder(const CString& strOrderNum);

//	void CreateOrderInfo();
	void ShowOrderInfo();								// 显示订单函数
	void HideOrderDlg(const CString& strOrderNum);		// 先不删除，只是隐藏，之后在进行删除
	void UpdateOrderInfo();								// 更新订单信息，对于已经取消的订单
	void CloseCancelOrder();							// 关闭已经取消的订单
	
	BOOL IsAlreadyShow(const CString& strOrder);

	// 接单处理 方法
	void ShowRecvOrderInfo();
	void InsertRecvOrder(RecvInfo pRecvInfo);

	// 公用方法
	void MoveWindow(CRect rcClient);
private:
	CNetbarDlg * m_pNetBarDlg;			// 父窗口

	// 订单数据
	vcOrderInfo		m_vcOrderInfo;		// 订单数据
	vector<COrderDlg*>	m_vcOrderDlg;	// 订单数据dlg

	// 接单数据
	vcRecvInfo		m_vcRecvInfo;		// 接单数据
	vector<CRecvDlg*>	m_vcRecvDlg;	// 已接订单dlg
	
	int				m_nOrderShowCount;	// 实际显示的订单数据
};