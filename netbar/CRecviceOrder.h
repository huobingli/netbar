#pragma once
#include <afxwin.h>

class CNetbarDlg;
class CRecviceOrder
{
public:
	CRecviceOrder();
	~CRecviceOrder();
};

#define TIMER_COUNTDOWN	20190410
class CRecvDlg : public CDialog
{
public:
	CRecvDlg(CWnd* pParent =NULL);
	~CRecvDlg();
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECV_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

	void UpdateCountDown(UINT_PTR nIDEvent);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetParent(CNetbarDlg* pParent);

private:
	int		m_nHour;
	int		m_nMinute;
	int		m_nSecond;

	CNetbarDlg * m_pParent;
};

