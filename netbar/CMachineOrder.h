#pragma once
#include "stdafx.h"
#include "COrderDlg.h"

class CMachineOrderDlg : public CDialog
{
public:
	CMachineOrderDlg(CWnd* pParent = NULL);
	~CMachineOrderDlg();
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MACHINE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	void SetParent(COrderDlg* pParent) { m_pParent = pParent; }
	void SetMachineCount(int nCount);

	void ShowMachineEdit();

private:
	int		m_nCount;

	COrderDlg * m_pParent;

	vector<CEdit*> m_vcEdit;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};