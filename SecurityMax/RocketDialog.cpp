// RocketDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "RocketDialog.h"
#include "afxdialogex.h"
#include "Optimization.h"

CRect rt;

// CRocketDialog �Ի���

IMPLEMENT_DYNAMIC(CRocketDialog, CDialogEx)

CRocketDialog::CRocketDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6_ROCKET, pParent)
{

}

CRocketDialog::~CRocketDialog()
{
}

void CRocketDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRocketDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CRocketDialog ��Ϣ�������


BOOL CRocketDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//CRect rt;
	// ��ȡͼƬ��С��Ϣ
	m_bitmap.LoadBitmapW(IDB_BITMAP1);
	m_bitmap.GetBitmap(&m_bitinfo);
	// ���ô��ں�ͼƬһ����
	rt = { 1200,600,1200 + m_bitinfo.bmWidth,600 + m_bitinfo.bmHeight };
	MoveWindow(&rt);


	// ���ô��ڷ��Ϊ��͸��
	LONG lStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, lStyle | WS_EX_LAYERED);
	// ����͸����
	SetLayeredWindowAttributes(RGB(255, 255, 255), 0, LWA_COLORKEY);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CRocketDialog::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SelectObject(m_bitmap);
	dc.BitBlt(0, 0, m_bitinfo.bmWidth, m_bitinfo.bmHeight, &dcMem, 0, 0, SRCCOPY);

	CDialogEx::OnPaint();
}


void CRocketDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION);
	CDialogEx::OnLButtonDown(nFlags, point);
}

DWORD WINAPI ThreadProc1(LPVOID huojian)
{
	CRocketDialog* pThis = (CRocketDialog*)huojian;
	for (int i = 600; i >= 60; i--)
	{

		rt.MoveToY(i);
		pThis->MoveWindow(&rt);

	}

	Sleep(100);
	rt.MoveToY(600);
	pThis->MoveWindow(&rt);
	COptimization optimization;
	optimization.clearMemory();
	return true;
}

void CRocketDialog::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CreateThread(NULL, NULL, ThreadProc1, this, NULL, NULL);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
