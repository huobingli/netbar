#pragma once
#include "CRecviceOrder.h"
#include <iostream>
#include <vector>
using namespace std;

#define ORDERINFO_MASK			0x000F
// vcOrderInfo
#define ORDERINFO_INIT			0x0000		// ������Ĭ��״̬			����֮��Ĭ��Ϊ�������
#define ORDERINFO_NEW			0x0001		// �¶���				
#define ORDERINFO_SHOW			0x0002		// �Ѿ���ʾ�Ķ���
#define ORDERINFO_DELETE		0x0003		// ���ӵĶ���			�����������Ҫɾ��info ��dlg
#define ORDERINFO_REMOVE		0x0004		// ɾ���Ķ���			�����������Ҫɾ��info ��dlg

// vcOrderRecvInfo		�����ѽӶ����Ĳ���
#define	ORDERINFO_RECV			0x0005		// �Ѿ��ӵĶ���			���������
#define ORDERINFO_ARRIVE		0x0006		// �Ѿ�����Ķ���


// ������Ϣ
struct OrderInfo
{
	CString			m_strOrderNum;			// �������
	CString			m_strLocate;			// λ��
	CString			m_strMachineNum;		// ����̨��
	CString			m_strUseTimer;			// ʹ��ʱ��
	CString			m_strAdditional;		// �û�Ҫ��
	CString			m_strMessage;			// �û�����
	DWORD			m_dwShowOrder;			// ������ʾ �¶���ΪFALSE  ��ʾ֮����¶���ΪTRUE

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

// CNetbarDlg �Ի���
class CNetbarDlg;
class COrderDlg : public CDialog
{
	// ����
public:
	COrderDlg(CWnd* pParent = NULL);	// ��׼���캯��
	COrderDlg(OrderInfo* pOrderInfo, CWnd* pParent = NULL);	// ��׼���캯��
	~COrderDlg();
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
	CFont		m_font;			// ����
	CFont		m_fontMessage;	
	OrderInfo*  m_pOrderInfo;
	CString		m_strMachineList;
public:
	
};

// ����������
class COrderManager
{
public:
	COrderManager(CNetbarDlg* pParent);
	~COrderManager();

	// �������� ����
	void ResetOrder();
	void InsertOrder(OrderInfo pOrderInfo);
	void DeleteOrder(const CString& strOrderNum);

	void ShowOrderInfo();								// ��ʾ��������
	void HideOrderDlg(const CString& strOrderNum);		// �Ȳ�ɾ����ֻ�����أ�֮���ڽ���ɾ��
	void UpdateOrderInfo();								// ���ڸ��¶���
	void CloseCancelOrder();							// �ر��Ѿ�ȡ���Ķ���
	void SetOrderStatus(const CString& strOrderNum, DWORD dwStatus);

	// �Ƿ����¶���
	BOOL IsHasNewOrder() { return m_bNewOrder; }
	void SetNewOrder(BOOL bFlag) { m_bNewOrder = bFlag; }

	BOOL IsAlreadyInit(const CString& strOrderNum);

	// �ӵ����� ����
	void ShowRecvOrderInfo();
	void InsertRecvOrder(RecvInfo pRecvInfo);
	void UpdateRecvInfo();																// ���½ӵ���Ϣ
	void DeleteRecvInfo(const CString& strOrderNum);									// ɾ���ӵ���Ϣ
	void SetRecvStatus(const CString& strOrderNum, DWORD dwStatus);						// ���ýӵ�״̬
	void CloseRecvOrder();


	// ���÷���
	void MoveWindow(CRect rcClient);

	
private:
	CNetbarDlg * m_pNetBarDlg;			// ������

	// ��������
	vcOrderInfo		m_vcOrderInfo;		// ��������
	vector<COrderDlg*>	m_vcOrderDlg;	// ��������dlg

	// �ӵ�����
	vcRecvInfo		m_vcRecvInfo;		// �ӵ�����
	vector<CRecvDlg*>	m_vcRecvDlg;	// �ѽӶ���dlg
	
	int				m_nOrderShowCount;	// ʵ����ʾ�Ķ�������

	BOOL			m_bNewOrder;		// �Ƿ����¶���
};