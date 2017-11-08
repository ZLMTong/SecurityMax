// MyProcess.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyProcess.h"
#include "afxdialogex.h"


// CMyProcess �Ի���

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


// CMyProcess ��Ϣ�������


BOOL CMyProcess::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//������չ���
	m_ProcessList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//����б���
	CRect rc;
	m_ProcessList.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pcol[] = { L"����", L"����ID", L"�߳���" , L"������ID"};
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
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CMyProcess::TraversalProcess()
{
	
	HANDLE hProcessHnd;			//���վ��
	HANDLE hProcess;			//���̾��

	Pe32.dwSize = sizeof(PROCESSENTRY32);

	//1.����һ��������صĿ��վ��
	hProcessHnd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessHnd == INVALID_HANDLE_VALUE)
	{
		return;
	}
	//2.ͨ�����̿��վ����ȡ��һ��������Ϣ
	if (!Process32First(hProcessHnd, &Pe32))
	{
		CloseHandle(hProcessHnd);
		return;
	}
	CString stran;
	int nHang = 0;	//��
	int nlie = 0;	//��
					//3.ѭ������������Ϣ
	do
	{
		//3.2��ȡ���ȼ���Ϣ
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, Pe32.th32ProcessID);
		if (hProcess)
		{
			//��ȡ�������ȼ�
			int nPriority = GetPriorityClass(hProcess);
			//�رվ��
			CloseHandle(hProcess);
		}

		//3.3��ȡ���̵����������Ϣ	
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

	//�رվ���˳�����
	CloseHandle(hProcessHnd);
}



