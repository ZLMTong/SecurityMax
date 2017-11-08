// MyModuleDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyModuleDialog.h"
#include "afxdialogex.h"
#include <TlHelp32.h>


// CMyModuleDialog �Ի���

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
	// 1. ����һ��ģ����صĿ��վ��
	hModuleSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPMODULE,  // ָ�����յ�����
		m_processID);            // ָ������
	if (hModuleSnap == INVALID_HANDLE_VALUE)
		return false;
	// 2. ͨ��ģ����վ����ȡ��һ��ģ����Ϣ
	if (!Module32First(hModuleSnap, &me32)) {
		CloseHandle(hModuleSnap);
		return false;
	}
	//3.ѭ����ȡģ����Ϣ
	CString stran;
	int nHang = 0;	//��
	int nlie = 0;	//��
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
	//4.�رվ�����˳�����
	CloseHandle(hModuleSnap);
	return true;
}

BEGIN_MESSAGE_MAP(CMyModuleDialog, CDialogEx)
END_MESSAGE_MAP()


// CMyModuleDialog ��Ϣ�������


BOOL CMyModuleDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//������չ���
	m_ModuleList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//����б���
	CRect rc;
	m_ModuleList.GetClientRect(&rc);//ָ����������С
	int nWidth = rc.Width();
	TCHAR* pcol[] = { L"ģ����" ,L"���ػ�ַ",L"ģ����" };
	for (int i = 0; i < 3; i++)
	{
		m_ModuleList.InsertColumn(i, pcol[i], 0, nWidth / 3);
	}

	GetModuleInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
