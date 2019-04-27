#include "CRecviceOrder.h"
#include "resource.h"


// CRecviceOrder::CRecviceOrder()
// {
// }
// 
// 
// CRecviceOrder::~CRecviceOrder()
// {
// }


CRecvDlg::CRecvDlg(RecvInfo* pInfo, CWnd* pParent /* =NULL */)
	: CDialog(IDD_RECV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pRecvInfo = new RecvInfo(pInfo);

	m_font.CreateFont(15, 0, 0, 0, 600,
		FALSE, FALSE, FALSE, 0, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN, _T("Arial"));
}

CRecvDlg::~CRecvDlg()
{
	if (m_pRecvInfo)
	{
		delete m_pRecvInfo;
		m_pRecvInfo = NULL;
	}
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

	m_nHour = atoi(m_pRecvInfo->m_strArriveTimer) - 1;
	m_nMinute = 59;
	m_nSecond = 59;

	SetTimer(TIMER_COUNTDOWN, 1000, NULL);
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
 
 		rcDlg.bottom -= 20;
 		CRect rcDraw(rcDlg);
 
 		// ��һ�л��� 
 		// λ��  ̨��  ʹ��ʱ��
 		rcDraw.bottom = rcDraw.top + rcDraw.Height() / 2;
 		DrawFirst(&dc, rcDraw);
 
 		// �ڶ��л���
 		// �û�Ҫ��
 		rcDraw.top = rcDraw.bottom;
		rcDraw.bottom = rcDlg.bottom;
 		DrawSecond(&dc, rcDraw);


// 		CString str;
// 		str.Format(_T("%02d : %02d : %02d"), m_nHour, m_nMinute, m_nSecond);
// 		pDC->DrawText(str, rcDlg, DT_LEFT | DT_VCENTER);
		

		CDialog::OnPaint();
	}
}

void CRecvDlg::DrawFirst(CDC* pDC, CRect rcDraw)
{
	CRect rcText(rcDraw);
	
	CFont* pFont = pDC->SelectObject(&m_font);

	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(_T("������"), rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(_T("���Ż���"), rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcDraw.right;
	pDC->DrawText(_T("����ʱ"), rcText, DT_CENTER | DT_VCENTER);
	pDC->SelectObject(pFont);
}

void CRecvDlg::DrawSecond(CDC* pDC, CRect rcDraw)
{
	CRect rcText(rcDraw);

	CFont* pFont = pDC->SelectObject(&m_font);

	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(m_pRecvInfo->m_strOrderNum, rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcText.left + rcDraw.Width() / 3;
	pDC->DrawText(m_pRecvInfo->m_strMachineList, rcText, DT_CENTER | DT_VCENTER);

	rcText.left = rcText.right;
	rcText.right = rcDraw.right;
	CString str;
	str.Format(_T("%02d : %02d : %02d"), m_nHour, m_nMinute, m_nSecond);
	pDC->DrawText(str, rcText, DT_CENTER | DT_VCENTER);
	pDC->SelectObject(pFont);
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
