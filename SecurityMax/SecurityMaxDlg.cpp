
// SecurityMaxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "SecurityMaxDlg.h"
#include "afxdialogex.h"
#include "MyProcess.h"
#include "PEEditorDialog.h"
#include "PEDragDialog.h"
#include "USEInterface.h"
#include "ServeDialog.h"
#include "ClearInterface.h"
#include "Optimization.h"
#include "RocketDialog.h"
#include "KillVirus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSecurityMaxDlg 对话框



CSecurityMaxDlg::CSecurityMaxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SECURITYMAX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CSecurityMaxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB1, m_TabInterface);
}

BEGIN_MESSAGE_MAP(CSecurityMaxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
	ON_COMMAND(ID_32777, &CSecurityMaxDlg::OnShutdown)
	ON_COMMAND(ID_32778, &CSecurityMaxDlg::OnRebot)
	ON_COMMAND(ID_32779, &CSecurityMaxDlg::On32779)
	ON_COMMAND(ID_32780, &CSecurityMaxDlg::OnSleep)
	ON_COMMAND(ID_32781, &CSecurityMaxDlg::OnSleepOff)
	ON_COMMAND(ID_32782, &CSecurityMaxDlg::On32782)
END_MESSAGE_MAP()


// CSecurityMaxDlg 消息处理程序

DWORD WINAPI ThreadProc2(LPVOID huojian)
{
	CRocketDialog dialog;
	dialog.DoModal();
	return 0;
}

BOOL CSecurityMaxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_TabInterface.InsertTab(7, L"进程",L"应用程序",L"服务",L"PE文件解析",L"垃圾清理",L"优化内存",L"病毒查杀");
	m_TabInterface.AddDlg(7,
		new CMyProcess, IDD_DIA1_PROCESS,
		new CUSEInterface, IDD_DIALOG2_PROGRAM,
		new CServeDialog, IDD_DIALOG3_SERVE,
		new PEDragDialog,IDD_DIALOG4_PEOFFSET,
		new CClearInterface,IDD_DIALOG5_CLEAR,
		new COptimization,IDD_DIALOG6_OPTIMIZE,
		new CKillVirus ,IDD_DIALOG7_VIRUS);

	CreateThread(NULL, NULL, ThreadProc2, NULL, NULL, NULL);

	RegisterHotKey(this->GetSafeHwnd(), 0xa001, MOD_SHIFT  , 'K');

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSecurityMaxDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSecurityMaxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSecurityMaxDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static bool  b = true;
 	switch (nHotKeyId)
 	{
 	case 0xa001:
		ShowWindow(b?SW_HIDE:SW_SHOW);
		b = !b;
 		break;
 	default:
 		break;
 	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CSecurityMaxDlg::OnShutdown()
{
	// TODO: 在此添加命令处理程序代码
	system("shutdown -p");
}


void CSecurityMaxDlg::OnRebot()
{
	// TODO: 在此添加命令处理程序代码
	system("shutdown -r -t 0");
}


void CSecurityMaxDlg::On32779()
{
	// TODO: 在此添加命令处理程序代码
	system("shutdown -l");
}


void CSecurityMaxDlg::OnSleep()
{
	// TODO: 在此添加命令处理程序代码
	system("powercfg -h on");
}


void CSecurityMaxDlg::OnSleepOff()
{
	// TODO: 在此添加命令处理程序代码
	system("powercfg -h off");
}


void CSecurityMaxDlg::On32782()
{
	// TODO: 在此添加命令处理程序代码
	system("shutdown -a");
}
