// RocketDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "RocketDialog.h"
#include "afxdialogex.h"
#include "Optimization.h"

CRect rt;

// CRocketDialog 对话框

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


// CRocketDialog 消息处理程序


BOOL CRocketDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//CRect rt;
	// 获取图片大小信息
	m_bitmap.LoadBitmapW(IDB_BITMAP1);
	m_bitmap.GetBitmap(&m_bitinfo);
	// 设置窗口和图片一样大
	rt = { 1200,600,1200 + m_bitinfo.bmWidth,600 + m_bitinfo.bmHeight };
	MoveWindow(&rt);


	// 设置窗口风格为可透明
	LONG lStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, lStyle | WS_EX_LAYERED);
	// 设置透明度
	SetLayeredWindowAttributes(RGB(255, 255, 255), 0, LWA_COLORKEY);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CRocketDialog::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CPaintDC dc(this); // 用于绘制的设备上下文
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	dcMem.SelectObject(m_bitmap);
	dc.BitBlt(0, 0, m_bitinfo.bmWidth, m_bitinfo.bmHeight, &dcMem, 0, 0, SRCCOPY);

	CDialogEx::OnPaint();
}


void CRocketDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CreateThread(NULL, NULL, ThreadProc1, this, NULL, NULL);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
