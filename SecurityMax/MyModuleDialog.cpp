// MyModuleDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyModuleDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CMyModuleDialog 对话框

IMPLEMENT_DYNAMIC(CMyModuleDialog, CDialogEx)

CMyModuleDialog::CMyModuleDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1_MODULE, pParent)
{

}

CMyModuleDialog::CMyModuleDialog(DWORD processID, CWnd* pParent /*= NULL*/)
	: CDialogEx(IDD_DIALOG1_MODULE, pParent)
{
	m_processID = processID;
}

CMyModuleDialog::~CMyModuleDialog()
{
}

void CMyModuleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ModuleList);
}


bool CMyModuleDialog::GetModuleInfo()
{
	

	HANDLE        hModuleSnap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me32 = { sizeof(MODULEENTRY32) };
	// 1. 创建一个模块相关的快照句柄
	hModuleSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE,  // 指定快照的类型
		m_processID);            // 指定进程
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return false;
	// 2. 通过模块快照句柄获取第一个模块信息
	if (!Module32First(hModuleSnap, &me32)) {
		CloseHandle(hModuleSnap);
		return false;
	}
	//3.循环获取模块信息
	CString stran;
	int nHang = 0;	//行
	int nlie = 0;	//列
	do
	{
		stran.Format(L"%d", me32.hModule);
		m_ModuleList.InsertItem(nHang, stran);

		stran.Format(L"%d", me32.modBaseAddr);
		m_ModuleList.SetItemText(nHang, ++nlie, stran);

		stran.Format(L"%s", me32.szExePath);
		m_ModuleList.SetItemText(nHang, ++nlie, stran);

		nHang++;
		nlie = 0;
	} while (Module32Next(hModuleSnap, &me32));
	//4.关闭句柄并退出函数
	CloseHandle(hModuleSnap);
	return true;
}

BEGIN_MESSAGE_MAP(CMyModuleDialog, CDialogEx)
END_MESSAGE_MAP()


// CMyModuleDialog 消息处理程序


BOOL CMyModuleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//设置扩展风格
	m_ModuleList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//添加列标题
	CRect rc;
	m_ModuleList.GetClientRect(&rc);//指定工作区大小
	int nWidth = rc.Width();
	TCHAR* pcol[] = { L"模块句柄" ,L"加载基址",L"模块名" };
	for (int i = 0; i < 3; i++)
	{
		m_ModuleList.InsertColumn(i, pcol[i], 0, nWidth / 3);
	}

	GetModuleInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
