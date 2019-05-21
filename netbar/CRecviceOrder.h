#pragma once
#include <afxwin.h>
#include <vector>

using namespace std;

//
#define RECVINFO_INIT			0x0000		// ������Ĭ��״̬	
#define RECVINFO_NEW			0x0001		// �ѽ��¶���				
#define RECVINFO_SHOW			0x0002		// �ѽ���ʾ�Ķ���
#define RECVINFO_OVERTIME		0x0003		// �ѽӶ�������


// ������Ϣ
struct RecvInfo
{
	CString			m_strOrderNum;			// �������
	CString			m_strMachineNum;		// ����̨��
	CString			m_strMachineList;		// ����λ��
	CString			m_strArriveTimer;		// ʹ��ʱ��
	DWORD			m_dwShowOrder;			// ������ʾ �¶���ΪFALSE  ��ʾ֮����¶���ΪTRUE

	BOOL			m_bUpdate;				// ���±�־

	RecvInfo()
	{
		m_dwShowOrder = RECVINFO_INIT;
		m_bUpdate = TRUE;
	}

	RecvInfo(RecvInfo* pRecvInfo)
	{
		m_strOrderNum = pRecvInfo->m_strOrderNum;
		m_strMachineNum = pRecvInfo->m_strMachineNum;
		m_strMachineList = pRecvInfo->m_strMachineList;
		m_strArriveTimer = pRecvInfo->m_strArriveTimer;
		m_dwShowOrder = pRecvInfo->m_dwShowOrder;
		m_bUpdate = pRecvInfo->m_bUpdate;
	}
};

typedef vector<RecvInfo> vcRecvInfo;
typedef vcRecvInfo::iterator  itRecvInfo;

class CNetbarDlg;

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
	DWORD GetRecvInfoStatus() { return m_pRecvInfo->m_dwShowOrder; }
	CString GetOrderInfoNum() { return m_pRecvInfo->m_strOrderNum; }
private:
	int		m_nHour;
	int		m_nMinute;
	int		m_nSecond;

	CNetbarDlg*		m_pParent;

	RecvInfo*		m_pRecvInfo;
	CFont			m_font;
	CFont			m_fontMessage;
public:
	afx_msg void OnBnClickedCancelDaodian();
};

