#pragma once
#include "CRecviceOrder.h"
#include <iostream>
#include <vector>
using namespace std;

#define ORDERINFO_MASK			0x000F
// vcOrderInfo
#define ORDERINFO_INIT			0x0000		// 订单的默认状态			请求之后默认为这个属性
#define ORDERINFO_NEW			0x0001		// 新订单				
#define ORDERINFO_SHOW			0x0002		// 已经显示的订单
#define ORDERINFO_DELETE		0x0003		// 不接的订单			有这个属性需要删除info 和dlg
#define ORDERINFO_REMOVE		0x0004		// 删除的订单			有这个属性需要删除info 和dlg

// vcOrderRecvInfo		对于已接订单的操作
#define	ORDERINFO_RECV			0x0005		// 已经接的订单			有这个属性
#define ORDERINFO_ARRIVE		0x0006		// 已经到店的订单


// 订单信息
struct OrderInfo
{
	CString			m_strOrderNum;			// 订单编号
	CString			m_strLocate;			// 位置
	CString			m_strMachineNum;		// 电脑台数
	CString			m_strUseTimer;			// 使用时间
	CString			m_strAdditional;		// 用户要求
	CString			m_strMessage;			// 用户留言
	DWORD			m_dwShowOrder;			// 订单显示 新订单为FALSE  显示之后的新订单为TRUE

	OrderInfo()
	{
		m_dwShowOrder = ORDERINFO_NEW;
	}

	OrderInfo(OrderInfo* pOrderInfo)
	{
		m_strOrderNum = pOrderInfo->m_strOrderNum;
		m_strLocate = pOrderInfo->m_strLocate;
		m_strMachineNum = pOrderInfo->m_strMachineNum;
		m_strUseTimer = pOrderInfo->m_strUseTimer;
		m_strAdditional = pOrderInfo->m_strAdditional;
		m_strMessage = pOrderInfo->m_strMessage;
		m_dwShowOrder = pOrderInfo->m_dwShowOrder;
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
	COrderDlg(CWnd* pParent = NULL);	// 标准构造函数
	COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent = NULL);	// 标准构造函数
	~COrderDlg();
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

	BOOL GetOrderInfoStatus() { return m_pOrderInfo->m_dwShowOrder; }
	void SetOrderInfoStatus(DWORD dwStatus) { m_pOrderInfo->m_dwShowOrder = dwStatus; }

	void SetMachineList(const CString& strList) { m_strMachineList = strList; }

	void SetOrderInfo(OrderInfo* pOrderInfo);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetParent(CNetbarDlg* pParent);
	CNetbarDlg* GetParent() { return m_pParent; }
private:
	CNetbarDlg* m_pParent;
	CFont		m_font;			// 字体
	CFont		m_fontMessage;	
	OrderInfo*  m_pOrderInfo;
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

	void ShowOrderInfo();								// 显示订单函数
	void HideOrderDlg(const CString& strOrderNum);		// 先不删除，只是隐藏，之后在进行删除
	void UpdateOrderInfo();								// 用于更新订单
	void CloseCancelOrder();							// 关闭已经取消的订单
	void SetOrderStatus(const CString& strOrderNum, DWORD dwStatus);

	// 是否有新订单
	BOOL IsHasNewOrder() { return m_bNewOrder; }
	void SetNewOrder(BOOL bFlag) { m_bNewOrder = bFlag; }

	BOOL IsAlreadyInit(const CString& strOrderNum);

	// 接单处理 方法
	void ShowRecvOrderInfo();
	void InsertRecvOrder(RecvInfo pRecvInfo);
	void UpdateRecvInfo();																// 更新接单信息
	void DeleteRecvInfo(const CString& strOrderNum);									// 删除接单信息
	void SetRecvStatus(const CString& strOrderNum, DWORD dwStatus);						// 设置接单状态
	void CloseRecvOrder();


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

	BOOL			m_bNewOrder;		// 是否有新订单
};