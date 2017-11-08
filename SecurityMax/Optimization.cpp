// Optimization.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "Optimization.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <Psapi.h>



//得到内存总大小（单位MB）  
ULONG GetTotalMemorySize()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return (ULONG)((statex.ullTotalPhys) / (1024 * 1024));
}
//得到可用内存大小（单位MB）  
ULONG GetAvailMemorySize()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return (ULONG)((statex.ullAvailPhys) / (1024 * 1024));
}
//优化内存
void COptimization::clearMemory()
{
	MEMORYSTATUSEX  stcMemStatusEX = {};
	stcMemStatusEX.dwLength = sizeof(stcMemStatusEX);
	GlobalMemoryStatusEx(&stcMemStatusEX);

	DWORDLONG prUsedMem = stcMemStatusEX.ullTotalPhys - stcMemStatusEX.ullAvailPhys;

	DWORD dwPIDList[1000] = { 0 };
	DWORD bufSize = sizeof(dwPIDList);
	DWORD dwNeedSize = 0;
	EnumProcesses(dwPIDList, bufSize, &dwNeedSize);

	for (DWORD i = 0; i < dwNeedSize / sizeof(DWORD); ++i)
	{
		HANDLE hProcess = OpenProcess(PROCESS_SET_QUOTA, false, dwPIDList[i]);
		SetProcessWorkingSetSize(hProcess, -1, -1);
	}

	GlobalMemoryStatusEx(&stcMemStatusEX);
	DWORDLONG afterCleanUsedMem = stcMemStatusEX.ullTotalPhys - stcMemStatusEX.ullAvailPhys;

}

DWORD WINAPI ThreadInternal(LPVOID lpThreadParameter)
{
	COptimization* pThis = (COptimization*)lpThreadParameter;
	while (true) {
		ULONG uTotalSize = GetTotalMemorySize();
		ULONG uLeisureSize = GetAvailMemorySize();
		double dInternalRate = (double)(uTotalSize - uLeisureSize) / uTotalSize*100.0;
		pThis->m_Internal.SetPos(dInternalRate);
		pThis->m_listboxMemory.ResetContent();
		pThis->m_strMemory.Format(L"%d", (int)dInternalRate);
		pThis->m_strMemory.Append(L"%");
		pThis->m_listboxMemory.AddString(pThis->m_strMemory);

		Sleep(1000);
	}
}


DWORD WINAPI ThreadCPU(LPVOID lpThreadParameter)
{
	COptimization* pThis = (COptimization*)lpThreadParameter;
	
	HANDLE hEvent;
	FILETIME preidleTime;		//CPU当前的空闲时间
	FILETIME prekernelTime;		//CPU当前在内核层的使用时间
	FILETIME preuserTime;		//CPU当前在用户层的使用时间
	GetSystemTimes(&preidleTime, &prekernelTime, &preuserTime);

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); // 初始值为 nonsignaled ，并且每次触发后自动设置为nonsignaled  
	while (1) {

		WaitForSingleObject(hEvent, 1500); //等待1500毫秒  

		FILETIME idleTime;
		FILETIME kernelTime;
		FILETIME userTime;
		GetSystemTimes(&idleTime, &kernelTime, &userTime);

		double dPreidleTime = (double)(preidleTime.dwHighDateTime*4.294967296E9) +(double)preidleTime.dwLowDateTime;
		double dPrekernelTime = (double)(prekernelTime.dwHighDateTime*4.294967296E9) + (double)prekernelTime.dwLowDateTime;
		double dPreuserTime = (double)(preuserTime.dwHighDateTime*4.294967296E9) + (double)preuserTime.dwLowDateTime;

		double dIdleTime = (double)(idleTime.dwHighDateTime*4.294967296E9) + (double)idleTime.dwLowDateTime;
		double dKernelTime = (double)(kernelTime.dwHighDateTime*4.294967296E9) + (double)kernelTime.dwLowDateTime;
		double dUserTime = (double)(userTime.dwHighDateTime*4.294967296E9) + (double)userTime.dwLowDateTime;

		int nCPURate = (int)(100.0 - (dIdleTime - dPreidleTime) / (dKernelTime - dPrekernelTime + dUserTime - dPreuserTime) * 100.0);

		pThis->m_listboxCPU.ResetContent();
		
		pThis->m_strCPU.Format(L"%d", nCPURate);
		pThis->m_strCPU.Append(L"%");
		pThis->m_listboxCPU.AddString(pThis->m_strCPU);

		preidleTime = idleTime;
		prekernelTime = kernelTime;
		preuserTime = userTime;

		pThis->m_CPU.SetPos(nCPURate);
	}

}


// COptimization 对话框

IMPLEMENT_DYNAMIC(COptimization, CDialogEx)


COptimization::COptimization(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6_OPTIMIZE, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDB_BITMAP2);
}

COptimization::~COptimization()
{
}

void COptimization::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS2, m_Internal);
	DDX_Control(pDX, IDC_PROGRESS1, m_CPU);
	DDX_Control(pDX, IDC_LIST1, m_listboxCPU);
	DDX_Control(pDX, IDC_LIST3, m_listboxMemory);
}


BEGIN_MESSAGE_MAP(COptimization, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &COptimization::OnMemoryOptimize)
END_MESSAGE_MAP()




// COptimization 消息处理程序


BOOL COptimization::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	

	CreateThread(NULL, NULL, ThreadInternal, this, NULL, NULL);
	CreateThread(NULL, NULL, ThreadCPU, this, NULL, NULL);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void COptimization::OnMemoryOptimize()
{
	// TODO: 在此添加控件通知处理程序代码
	clearMemory();
}
