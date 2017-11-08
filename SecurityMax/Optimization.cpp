// Optimization.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "Optimization.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <Psapi.h>



//�õ��ڴ��ܴ�С����λMB��  
ULONG GetTotalMemorySize()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return (ULONG)((statex.ullTotalPhys) / (1024 * 1024));
}
//�õ������ڴ��С����λMB��  
ULONG GetAvailMemorySize()
{
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return (ULONG)((statex.ullAvailPhys) / (1024 * 1024));
}
//�Ż��ڴ�
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
	FILETIME preidleTime;		//CPU��ǰ�Ŀ���ʱ��
	FILETIME prekernelTime;		//CPU��ǰ���ں˲��ʹ��ʱ��
	FILETIME preuserTime;		//CPU��ǰ���û����ʹ��ʱ��
	GetSystemTimes(&preidleTime, &prekernelTime, &preuserTime);

	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL); // ��ʼֵΪ nonsignaled ������ÿ�δ������Զ�����Ϊnonsignaled  
	while (1) {

		WaitForSingleObject(hEvent, 1500); //�ȴ�1500����  

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


// COptimization �Ի���

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




// COptimization ��Ϣ�������


BOOL COptimization::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	

	CreateThread(NULL, NULL, ThreadInternal, this, NULL, NULL);
	CreateThread(NULL, NULL, ThreadCPU, this, NULL, NULL);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void COptimization::OnMemoryOptimize()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	clearMemory();
}
