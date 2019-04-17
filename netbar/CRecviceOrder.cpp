#include "CRecviceOrder.h"
#include "resource.h"


CRecviceOrder::CRecviceOrder()
{
}


CRecviceOrder::~CRecviceOrder()
{
}


CRecvDlg::CRecvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RECV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

CRecvDlg::~CRecvDlg()
{

}

void CRecvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRecvDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CNetbarDlg ��Ϣ�������

BOOL CRecvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_nHour = 59;
	m_nMinute = 59;
	m_nSecond = 59;


	SetTimer(TIMER_COUNTDOWN, 1000, NULL);
	//SetTimer(NULL, TIMER_COUNTDOWN)
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRecvDlg::OnPaint()
{
	if (IsIconic())
	{

	}
	else
	{
 		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
 		CRect rcDlg;
 		GetClientRect(rcDlg);
		CDC* pDC = &dc;
// 
// 		rcDlg.bottom -= 40;
// 		CRect rcDraw(rcDlg);
// 
// 		// ��һ�л��� 
// 		// λ��  ̨��  ʹ��ʱ��
// 		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
// 		DrawFirst(&dc, rcDraw);
// 
// 		// �ڶ��л���
// 		// �û�Ҫ��
// 		rcDraw.top = rcDraw.bottom;
// 		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 3;
// 		DrawSecond(&dc, rcDraw);
// 
// 		// �����л���
// 		// �û�����
// 		rcDraw.top = rcDraw.bottom;
// 		rcDraw.bottom = rcDlg.bottom;
// 		DrawMessage(&dc, rcDraw);

		CString str;
		str.Format(_T("%02d : %02d : %02d"), m_nHour, m_nMinute, m_nSecond);
		pDC->DrawText(str, rcDlg, DT_LEFT | DT_VCENTER);
		

		CDialog::OnPaint();
	}
}

void CRecvDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CDialog::OnClose();
}

BOOL CRecvDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	else
	{
		return CDialog::PreTranslateMessage(pMsg);
	}
}

void CRecvDlg::SetParent(CNetbarDlg* pParent)
{
	m_pParent = pParent;
}

void CRecvDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (TIMER_COUNTDOWN == nIDEvent)
	{
		UpdateCountDown(nIDEvent);
	}

	CDialog::OnTimer(nIDEvent);
}

void CRecvDlg::UpdateCountDown(UINT_PTR nIDEvent)
{
	CString str(_T(""));
#define MAX_VALUE 59
	///*static*/ int nHour = MAX_VALUE;
	///*static*/ int nMinute = MAX_VALUE;
	///*static*/ int nSecond = MAX_VALUE;
	--m_nSecond;

	if (!m_nSecond)
	{
		--m_nMinute;
		if (!m_nMinute)
		{
			--m_nHour;
			if (!m_nHour)
			{
				//SetDlgItemText(IDC_EDIT1, _T("00 : 00 : 00"));
				//::SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_EDIT1, strTime);
				KillTimer(nIDEvent);
				AfxMessageBox(_T("Game Over!"));
				return;
			}
			m_nMinute = MAX_VALUE;
		}
		m_nSecond = MAX_VALUE;
	}

	Invalidate(TRUE);
	//str.Format(_T("%02d : %02d : %02d"), m_nHour, m_nMinute, m_nSecond);
	//SetDlgItemText(IDC_EDIT1, str);
}
