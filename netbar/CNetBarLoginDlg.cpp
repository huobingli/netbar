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


// CNetBarLoginDlg 消息处理程序

BOOL CNetBarLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

									// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNetBarLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNetBarLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 登录
void CNetBarLoginDlg::OnBnClickedOk()
{
	OnCancel();
	CNetbarDlg* pNetBarDlg = new CNetbarDlg;
	//pNetBarDlg->SetParam(strUsername, strPassword);
	pNetBarDlg->DoModal();

	return;

	// 请求
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

		// 解析json 如果成功，即可登录
		if (!strResponse.IsEmpty())
		{
			// 返回成功
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
				AfxMessageBox(_T("登录失败。。"));
			}
		}
		else
		{
			AfxMessageBox(_T("错误代码101，请求无返回！"));
		}
	}
	else
	{
		AfxMessageBox(_T("错误代码100，http请求失败！"));
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

