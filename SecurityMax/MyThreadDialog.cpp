// MyThreadDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyThreadDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CMyThreadDialog 对话框

IMPLEMENT_DYNAMIC(CMyThreadDialog, CDialogEx)

CMyThreadDialog::CMyThreadDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1_THREAD, pParent)
{

}

CMyThreadDialog::CMyThreadDialog(DWORD processID, CWnd* pParent /*= NULL*/)
	: CDialogEx(IDD_DIALOG1_THREAD, pParent)
{
	m_processID = processID;
}

CMyThreadDialog::~CMyThreadDialog()
{
}

void CMyThreadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ThreadList);
}


bool CMyThreadDialog::GetThreadInfo(DWORD dwProceId)
{
	//设置扩展风格
	m_ThreadList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//添加列标题
	CRect rc;
	m_ThreadList.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"PID",L"TID",L"优先级" };
	for (int i = 0; i < 3; ++i)
	{
		m_ThreadList.InsertColumn(i, pCol[i], 0, nWidth / 3);
	}

	// 创建线程快照
	HANDLE hSnThread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hSnThread == INVALID_HANDLE_VALUE) {
		
		CString err = L"创建线程快照失败,错误码:";
		m_stcInfo.Format(L"%d", GetLastError());
		err + m_stcInfo;
		MessageBox(m_stcInfo);
		return false;
	}

	// 开始遍历线程
	THREADENTRY32 threadEntry = { sizeof(THREADENTRY32) };

	// 获取快照中的第一个线程的信息
	Thread32First(hSnThread, &threadEntry);

	int m_nLine = 0;
	int m_nLie = 0;
	DWORD dwSuspendCount = 0;
	do {

		// 判断遍历到的线程是否属于这个进程的.
		if (threadEntry.th32OwnerProcessID == dwProceId) {

			m_stcInfo.Format(L"%d", threadEntry.th32OwnerProcessID);
			m_ThreadList.InsertItem(m_nLine, m_stcInfo);

			m_stcInfo.Format(L"%d", threadEntry.th32ThreadID);
			m_ThreadList.SetItemText(m_nLine, ++m_nLie, m_stcInfo);

			m_stcInfo.Format(L"%d", threadEntry.tpBasePri);
			m_ThreadList.SetItemText(m_nLine, ++m_nLie, m_stcInfo);

			++m_nLine;
			m_nLie = 0;
		}

		// 获取快照中的下一个线程信息
	} while (Thread32Next(hSnThread, &threadEntry));
}

BEGIN_MESSAGE_MAP(CMyThreadDialog, CDialogEx)
END_MESSAGE_MAP()


// CMyThreadDialog 消息处理程序


BOOL CMyThreadDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetThreadInfo(m_processID);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
