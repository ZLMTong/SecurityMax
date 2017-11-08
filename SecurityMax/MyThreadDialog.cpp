// MyThreadDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyThreadDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CMyThreadDialog �Ի���

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
	//������չ���
	m_ThreadList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//����б���
	CRect rc;
	m_ThreadList.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"PID",L"TID",L"���ȼ�" };
	for (int i = 0; i < 3; ++i)
	{
		m_ThreadList.InsertColumn(i, pCol[i], 0, nWidth / 3);
	}

	// �����߳̿���
	HANDLE hSnThread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hSnThread == INVALID_HANDLE_VALUE) {
		
		CString err = L"�����߳̿���ʧ��,������:";
		m_stcInfo.Format(L"%d", GetLastError());
		err + m_stcInfo;
		MessageBox(m_stcInfo);
		return false;
	}

	// ��ʼ�����߳�
	THREADENTRY32 threadEntry = { sizeof(THREADENTRY32) };

	// ��ȡ�����еĵ�һ���̵߳���Ϣ
	Thread32First(hSnThread, &threadEntry);

	int m_nLine = 0;
	int m_nLie = 0;
	DWORD dwSuspendCount = 0;
	do {

		// �жϱ��������߳��Ƿ�����������̵�.
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

		// ��ȡ�����е���һ���߳���Ϣ
	} while (Thread32Next(hSnThread, &threadEntry));
}

BEGIN_MESSAGE_MAP(CMyThreadDialog, CDialogEx)
END_MESSAGE_MAP()


// CMyThreadDialog ��Ϣ�������


BOOL CMyThreadDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetThreadInfo(m_processID);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
