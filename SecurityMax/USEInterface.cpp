// USEInterface.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "USEInterface.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;

vector<CString> g_vctStr;
vector<CString> g_vctClassName;

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	if (GetParent(hWnd) == NULL && IsWindowVisible(hWnd))   //�ж��Ƿ񶥲㴰�ڲ��ҿɼ�
	{
		WCHAR WindowTitle[100] = { 0 };
		::GetWindowText(hWnd, WindowTitle, 100);
		WCHAR windowsClassName[100] = { 0 };
		GetClassName(hWnd, windowsClassName, 100);
		if (wcscmp(WindowTitle,L"") != 0)
		{
			g_vctStr.push_back(WindowTitle);
			g_vctClassName.push_back(windowsClassName);
		}

	}
	return true;
}


// CUSEInterface �Ի���

IMPLEMENT_DYNAMIC(CUSEInterface, CDialogEx)

CUSEInterface::CUSEInterface(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2_PROGRAM, pParent)
{

}

CUSEInterface::~CUSEInterface()
{
}

void CUSEInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_useList);
}


BEGIN_MESSAGE_MAP(CUSEInterface, CDialogEx)
END_MESSAGE_MAP()


// CUSEInterface ��Ϣ�������


BOOL CUSEInterface::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//������չ���
	m_useList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//����б���
	CRect rc;
	m_useList.GetClientRect(&rc);//ָ����������С
	int nWidth = rc.Width();
	TCHAR* pcol[] = { L"���洰��",L"����" };
	for (int i = 0; i < 2; i++)
	{
		m_useList.InsertColumn(i, pcol[i], 0, nWidth / 2);
	}
	EnumWindows(EnumWindowsProc, NULL);
	for (int i = 0; i <(int) g_vctStr.size();++i)
	{
		m_useList.InsertItem(i, g_vctStr[i]);
		m_useList.SetItemText(i, 1, g_vctClassName[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

