#pragma once

// ������Ϣ
struct OrderInfo {
	DWORD			m_dwOrderNum;			// �������
	CString			m_strLocate;			// λ��
	DWORD			m_dwMachineNum;			// ����̨��
	DWORD			m_dwUseTimer;			// ʹ��ʱ��
	CString			m_strUserAsk;			// �û�Ҫ��
	CString			m_strMessage;			// �û�����
};

// CNetbarDlg �Ի���
class COrderDlg : public CDialog
{
	// ����
public:
	COrderDlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORDER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

	// ����
public:
	afx_msg void OnBnClickedCancelOrder();
	afx_msg void OnBnClickedConfirmOrder();
};
