#pragma once
#include <afxwin.h>
#include <vector>

using namespace std;

// 订单信息
struct RecvInfo
{
	CString			m_strOrderNum;			// 订单编号
	CString			m_strMachineNum;		// 电脑台数
	CString			m_strMachineList;		// 电脑位置
	CString			m_strArriveTimer;		// 使用时间
	BOOL			m_bShowOrder;			// 订单显示 新订单为FALSE  显示之后的新订单为TRUE

	BOOL			m_bUpdate;				// 更新标志

	RecvInfo()
	{
		m_bShowOrder = FALSE;
		m_bUpdate = TRUE;
	}

	RecvInfo(RecvInfo* pRecvInfo)
	{
		m_strOrderNum = pRecvInfo->m_strOrderNum;
		m_strMachineNum = pRecvInfo->m_strMachineNum;
		m_strMachineList = pRecvInfo->m_strMachineList;
		m_strArriveTimer = pRecvInfo->m_strArriveTimer;
		m_bShowOrder = pRecvInfo->m_bShowOrder;
		m_bUpdate = pRecvInfo->m_bUpdate;
	}
};

typedef vector<RecvInfo> vcRecvInfo;
typedef vcRecvInfo::iterator  itRecvInfo;

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
	CRecvDlg(RecvInfo* pInfo, CWnd* pParent =NULL);
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

	void DrawFirst(CDC* pDC, CRect rcDraw);
	void DrawSecond(CDC* pDC, CRect rcDraw);


	void UpdateCountDown(UINT_PTR nIDEvent);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void SetParent(CNetbarDlg* pParent);

private:
	int		m_nHour;
	int		m_nMinute;
	int		m_nSecond;

	CNetbarDlg *	m_pParent;

	RecvInfo*		m_pRecvInfo;
	CFont			m_font;
};

