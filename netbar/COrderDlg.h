#pragma once

#include <iostream>
#include <vector>
using namespace std;


// ������Ϣ
struct OrderInfo
{
	CString			m_strOrderNum;			// �������
	CString			m_strLocate;			// λ��
	CString			m_strMachineNum;		// ����̨��
	CString			m_strUseTimer;			// ʹ��ʱ��
	CString			m_strAdditional;		// �û�Ҫ��
	CString			m_strMessage;			// �û�����
	BOOL			m_bShowOrder;			// ������ʾ

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
class CRecvDlg;
struct OrderDlgInfo
{
	COrderDlg* m_pOrderDlg;
	OrderInfo* m_pOrderInfo;
};

typedef vector<OrderDlgInfo> vcOrderDlg;
typedef vcOrderDlg::iterator	itOrderDlg;

// CNetbarDlg �Ի���
class CNetbarDlg;
class COrderDlg : public CDialog
{
	// ����
public:
	COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent = NULL);	// ��׼���캯��

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
	
	void DrawFirst(CDC* pDC, CRect rcDraw);
	void DrawSecond(CDC* pDC, CRect rcDraw);
	void DrawMessage(CDC* pDC, CRect rcDraw);

	// ����
public:
	afx_msg void OnBnClickedCancelOrder();
	afx_msg void OnBnClickedConfirmOrder();
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);

	//CString GetOrderNum();
	OrderInfo* m_pOrderInfo;
	
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetParent(CNetbarDlg* pParent);
private:
	CNetbarDlg* m_pParent;
public:
	
};

// ����������
class COrderManager
{
public:
	COrderManager(CNetbarDlg* pParent);
	~COrderManager();


	void InsertOrder(OrderInfo pOrderInfo);
	void DeleteOrder(const CString& strOrderNum);

	void CreateOrderInfo();
	void ShowOrderInfo();
	void MoveWindow(CRect rcClient);
	// 	BOOL DeleteOrder();
	// 	BOOL DeleteOrder();

private:
	CNetbarDlg * m_pNetBarDlg;		// ������

	vcOrderInfo		m_vcOrderInfo;
	//vcOrderDlg		m_vcOrderDlg;	// ����vc
	vector<COrderDlg*>	m_vcOrderDlg;	// ��������
	vector<CRecvDlg*>	m_vcRecvDlg;	// �ѽӶ�������
	
};