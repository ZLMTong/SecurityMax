
// SecurityMaxDlg.cpp : ʵ���ļ�
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


// CSecurityMaxDlg �Ի���



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


// CSecurityMaxDlg ��Ϣ�������

DWORD WINAPI ThreadProc2(LPVOID huojian)
{
	CRocketDialog dialog;
	dialog.DoModal();
	return 0;
}

BOOL CSecurityMaxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_TabInterface.InsertTab(7, L"����",L"Ӧ�ó���",L"����",L"PE�ļ�����",L"��������",L"�Ż��ڴ�",L"������ɱ");
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSecurityMaxDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSecurityMaxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSecurityMaxDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
	system("shutdown -p");
}


void CSecurityMaxDlg::OnRebot()
{
	// TODO: �ڴ���������������
	system("shutdown -r -t 0");
}


void CSecurityMaxDlg::On32779()
{
	// TODO: �ڴ���������������
	system("shutdown -l");
}


void CSecurityMaxDlg::OnSleep()
{
	// TODO: �ڴ���������������
	system("powercfg -h on");
}


void CSecurityMaxDlg::OnSleepOff()
{
	// TODO: �ڴ���������������
	system("powercfg -h off");
}


void CSecurityMaxDlg::On32782()
{
	// TODO: �ڴ���������������
	system("shutdown -a");
}
