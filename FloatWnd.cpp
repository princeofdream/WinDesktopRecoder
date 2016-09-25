// FloatWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Main.h"
#include "FloatWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd dialog


CFloatWnd::CFloatWnd(CWnd* pParent /*=NULL*/)
	: CDialog(CFloatWnd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFloatWnd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFloatWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFloatWnd)
	DDX_Control(pDX, IDC_LOGO, m_Logo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFloatWnd, CDialog)
	//{{AFX_MSG_MAP(CFloatWnd)	
	ON_WM_NCHITTEST()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_SHOW, OnShow)
	ON_WM_NCLBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatWnd message handlers

BOOL CFloatWnd::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CBitmap m_Bitmap;
	HBITMAP hBitmap = m_Logo.GetBitmap();
	ASSERT(hBitmap);

	m_Bitmap.Attach(hBitmap);
	BITMAP bmp;
	m_Bitmap.GetBitmap(&bmp);

	int nX = bmp.bmWidth;
	int nY = bmp.bmHeight;

	MoveWindow(0,0,nX,nY);	
	m_Logo.MoveWindow(0,0,nX,nY);
	CenterWindow();
	::SetWindowPos(m_hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);

	m_Bitmap.Detach();
	
	//����WS_EX_LAYERED��չ����
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CFloatWnd::OnNcHitTest(CPoint pt)
{
	LRESULT nHitTest = CDialog::OnNcHitTest(pt);

	if (nHitTest == HTCLIENT &&
				::GetAsyncKeyState(MK_LBUTTON) < 0) // ������������£�GetAsyncKeyState�����ķ���ֵС��0

		nHitTest = HTCAPTION;

	return nHitTest;
}


void CFloatWnd::OnOK()
{
	// TODO: Add extra cleanup here

	//OnOK();
}

void CFloatWnd::OnCancel() 
{
	// TODO: Add extra cleanup here

	//	CDialog::OnCancel();
}

void CFloatWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu m_Right;
	m_Right.LoadMenu(IDR_MENU1);
	CMenu *pSub = m_Right.GetSubMenu(0);

	ClientToScreen(&point);
	pSub->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this,NULL);
	
	CDialog::OnRButtonUp(nFlags, point);
}

void CFloatWnd::OnExit() 
{
	// TODO: Add your command handler code here
	CWnd *pParent = GetParent();
	ASSERT(pParent);

	pParent->PostMessage(WM_QUIT,0,0);
}

void CFloatWnd::OnShow() 
{
	// TODO: Add your command handler code here
	CWnd *pParent = GetParent();
	ASSERT(pParent);
	
	if(pParent->IsWindowVisible())
		pParent->ShowWindow(SW_HIDE);
	else
		pParent->ShowWindow(SW_SHOW);
}

void CFloatWnd::OnUpdateTransparent(int iTransparent)
{
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	if(hInst)
	{
		typedef BOOL (WINAPI *SLWA)(HWND,COLORREF,BYTE,DWORD);
		SLWA pFun = NULL;
		//ȡ��SetLayeredWindowAttributes����ָ�� 
		pFun = (SLWA)GetProcAddress(hInst,"SetLayeredWindowAttributes");
		if(pFun)
		{
			pFun(m_hWnd,0,iTransparent,2);
		}
		FreeLibrary(hInst); 
	}
}

void CFloatWnd::OnNcLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CWnd *pParent = GetParent();
	ASSERT(pParent);
	
	if(!pParent->IsWindowVisible())
		pParent->ShowWindow(SW_SHOW);

	pParent->SetForegroundWindow();

	CDialog::OnNcLButtonDblClk(nFlags, point);
}