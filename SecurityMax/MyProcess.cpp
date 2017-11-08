// MyProcess.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyProcess.h"
#include "afxdialogex.h"


// CMyProcess 对话框

IMPLEMENT_DYNAMIC(CMyProcess, CDialogEx)

CMyProcess::CMyProcess(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIA1_PROCESS, pParent)
{

}

CMyProcess::~CMyProcess()
{
}

void CMyProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ProcessList);
}


BEGIN_MESSAGE_MAP(CMyProcess, CDialogEx)

END_MESSAGE_MAP()


// CMyProcess 消息处理程序


BOOL CMyProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//设置扩展风格
	m_ProcessList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//添加列标题
	CRect rc;
	m_ProcessList.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pcol[] = { L"名称", L"进程ID", L"线程数" , L"父进程ID"};
	for (int i = 0; i < 4; i++)
	{
		m_ProcessList.InsertColumn(i, pcol[i], 0, 150);
		if (i > 0)
		{
			m_ProcessList.SetColumnWidth(i, nWidth / 4);
		}
	}

	TraversalProcess();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CMyProcess::TraversalProcess()
{
	
	HANDLE hProcessHnd;			//快照句柄
	HANDLE hProcess;			//进程句柄

	Pe32.dwSize = sizeof(PROCESSENTRY32);

	//1.创建一个进程相关的快照句柄
	hProcessHnd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessHnd == INVALID_HANDLE_VALUE)
	{
		return;
	}
	//2.通过进程快照句柄获取第一个进程信息
	if (!Process32First(hProcessHnd, &Pe32))
	{
		CloseHandle(hProcessHnd);
		return;
	}
	CString stran;
	int nHang = 0;	//行
	int nlie = 0;	//列
					//3.循环遍历进程信息
	do
	{
		//3.2获取优先级信息
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, Pe32.th32ProcessID);
		if (hProcess)
		{
			//获取进程优先级
			int nPriority = GetPriorityClass(hProcess);
			//关闭句柄
			CloseHandle(hProcess);
		}

		//3.3获取进程的其他相关信息	
		stran.Format(L"%s", Pe32.szExeFile);
		m_ProcessList.InsertItem(nHang, stran);

		stran.Format(L"%d", Pe32.th32ProcessID);
		m_ProcessList.SetItemText(nHang, ++nlie, stran);

		m_ProcessList.m_processID.push_back(Pe32.th32ProcessID);

		stran.Format(L"%d", Pe32.cntThreads);
		m_ProcessList.SetItemText(nHang, ++nlie, stran);

		stran.Format(L"%d", Pe32.th32ParentProcessID);
		m_ProcessList.SetItemText(nHang, ++nlie, stran);

		nHang++;
		nlie = 0;
	} while (Process32Next(hProcessHnd, &Pe32));

	//关闭句柄退出函数
	CloseHandle(hProcessHnd);
}



