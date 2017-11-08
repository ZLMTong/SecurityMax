// MyRVAToOffset.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "PERVAToOffset.h"
#include "afxdialogex.h"


// CMyRVAToOffset �Ի���

IMPLEMENT_DYNAMIC(PERVAToOffset, CDialogEx)

PERVAToOffset::PERVAToOffset(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_CALCULATE, pParent)
	, m_VA(_T(""))
	, m_RVA(_T(""))
	, m_Offset(_T(""))
{

}

PERVAToOffset::~PERVAToOffset()
{
}

void PERVAToOffset::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_VA);
	DDX_Text(pDX, IDC_EDIT4, m_RVA);
	DDX_Text(pDX, IDC_EDIT5, m_Offset);
}


DWORD PERVAToOffset::RVAToOffset(IMAGE_DOS_HEADER* pDos, DWORD dwRva)
{
	IMAGE_SECTION_HEADER* pScnHdr;

	IMAGE_NT_HEADERS* pNtHdr =
		(IMAGE_NT_HEADERS*)(pDos->e_lfanew + (DWORD)pDos);

	pScnHdr = IMAGE_FIRST_SECTION(pNtHdr);//���α�ͷ
	DWORD dwNumberOfScn = pNtHdr->FileHeader.NumberOfSections;//���ε�����

															  // 1. �������������ҵ���������
	for (int i = 0; i < dwNumberOfScn; ++i)
	{
		DWORD dwEndOfSection = pScnHdr[i].VirtualAddress + pScnHdr[i].SizeOfRawData;
		// �ж����RVA�Ƿ���һ�����εķ�Χ��
		if (dwRva >= pScnHdr[i].VirtualAddress && dwRva < dwEndOfSection)
		{
			// 2. �����RVA�������ڵ�ƫ��:rva ��ȥ�׵�ַ
			DWORD dwOffset = dwRva - pScnHdr[i].VirtualAddress;
			// 3. ��������ƫ�Ƽ������ε��ļ���ʼƫ��
			return dwOffset + pScnHdr[i].PointerToRawData;
		}
	}
	return -1;
}

BEGIN_MESSAGE_MAP(PERVAToOffset, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &PERVAToOffset::OnExecute)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMyRVAToOffset ��Ϣ�������


void PERVAToOffset::OnExecute()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	wchar_t *p = L"";
	int dword = wcstol(m_RVA.GetBuffer(), &p, 16);
	m_Offset.Format(L"%08X", RVAToOffset(m_pDosHdr, dword));
	m_VA.Format(L"%08X", m_pOptHdr->ImageBase + dword);
	UpdateData(FALSE);
}


void PERVAToOffset::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnExecute();
	CDialogEx::OnLButtonDown(nFlags, point);
}
