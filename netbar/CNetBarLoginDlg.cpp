#include "stdafx.h"
#include "CNetBarLoginDlg.h"
#include "resource.h"
#include "netbarDlg.h"
#include "CUserInfo.h"
#include "global.h"

CNetBarLoginDlg::CNetBarLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOGIN_DIALOG, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetBarLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNetBarLoginDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNetBarLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNetBarLoginDlg ��Ϣ�������

BOOL CNetBarLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

									// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CNetBarLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CNetBarLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ��¼
void CNetBarLoginDlg::OnBnClickedOk()
{
	OnCancel();
	CNetbarDlg* pNetBarDlg = new CNetbarDlg;
	//pNetBarDlg->SetParam(strUsername, strPassword);
	pNetBarDlg->DoModal();

	return;

	// ����
	CHttpClient* pHttpClient = new CHttpClient;
	CString strResponse;
	LPCTSTR pJsonPostData = _T("");

	CString strLoginURL;
	strLoginURL.LoadStringA(IDS_STRING_LOGIN);
	CString strUsername;
	GetDlgItem(IDC_USERNAME_EDIT)->GetWindowText(strUsername);
	CString strPassword;
	GetDlgItem(IDC_PASSWORD_EDIT)->GetWindowText(strPassword);
	strLoginURL.Format(strLoginURL, strUsername, strPassword);
	if (pHttpClient)
	{
		pHttpClient->HttpPost(strLoginURL, pJsonPostData, strResponse);

		// ����json ����ɹ������ɵ�¼
		if (!strResponse.IsEmpty())
		{
			// ���سɹ�
			if (ParseJson(strResponse) == 0)
			{
				OnCancel();
				CNetbarDlg* pNetBarDlg = new CNetbarDlg;
				CUserInfoHolder::Instance()->SetUrlParam(strUsername, strPassword);
				//pNetBarDlg->SetParam(strUsername, strPassword);
				pNetBarDlg->DoModal();
			}
			else
			{
				AfxMessageBox(_T("��¼ʧ�ܡ���"));
			}
		}
		else
		{
			AfxMessageBox(_T("�������101�������޷��أ�"));
		}
	}
	else
	{
		AfxMessageBox(_T("�������100��http����ʧ�ܣ�"));
	}

	GetDlgItem(IDC_PASSWORD_EDIT)->SetWindowText(_T(""));
	GetDlgItem(IDC_PASSWORD_EDIT)->SetFocus();
}


BOOL CNetBarLoginDlg::ParseJson(CString& strJson)
{
	Json::Value jsonRoot;
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());

	CString strError;
	BOOL bError = TRUE;
	JSONCPP_STRING errs;
	bool ok = reader->parse(strJson.GetBuffer(0), strJson.GetBuffer() + strJson.GetLength(), &jsonRoot, &errs);
	if (ok && errs.empty())
	{
		//strError = jsonRoot["error"].asInt();
		bError = jsonRoot["error"].asInt();
	}

	return bError;

// 	if (strError.CompareNoCase(_T("0")) == 0)
// 	{
// 		return TRUE;
// 	}
// 	return FALSE;
}

