#pragma once
#include <afxwin.h>
#include <vector>

using namespace std;

// ������Ϣ
struct RecvInfo
{
	CString			m_strOrderNum;			// �������
	CString			m_strMachineNum;		// ����̨��
	CString			m_strMachineList;		// ����λ��
	CString			m_strArriveTimer;		// ʹ��ʱ��
	BOOL			m_bShowOrder;			// ������ʾ �¶���ΪFALSE  ��ʾ֮����¶���ΪTRUE

	BOOL			m_bUpdate;				// ���±�־

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
	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECV_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

