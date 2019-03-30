#pragma once

// 订单信息
struct OrderInfo {
	DWORD			m_dwOrderNum;			// 订单编号
	CString			m_strLocate;			// 位置
	DWORD			m_dwMachineNum;			// 电脑台数
	DWORD			m_dwUseTimer;			// 使用时间
	CString			m_strUserAsk;			// 用户要求
	CString			m_strMessage;			// 用户留言
};

// CNetbarDlg 对话框
class COrderDlg : public CDialog
{
	// 构造
public:
	COrderDlg(CWnd* pParent = NULL);	// 标准构造函数

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

	// 绘制
public:
	afx_msg void OnBnClickedCancelOrder();
	afx_msg void OnBnClickedConfirmOrder();
};
