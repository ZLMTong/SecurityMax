// PERelocationDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PERelocationDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPERelocationDialog �Ի���

IMPLEMENT_DYNAMIC(CPERelocationDialog, CDialogEx)

CPERelocationDialog::CPERelocationDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_RELOCATION, pParent)
{

}

CPERelocationDialog::~CPERelocationDialog()
{
}

void CPERelocationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListA);
	DDX_Control(pDX, IDC_LIST2, m_ListB);
}


BEGIN_MESSAGE_MAP(CPERelocationDialog, CDialogEx)
END_MESSAGE_MAP()


// CPERelocationDialog ��Ϣ�������


BOOL CPERelocationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListA.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListB.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rc;
	m_ListA.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"����",/*L"����",*/L"RVA",L"��Ŀ" };
	for (int i = 0; i < 3; ++i)
	{
		m_ListA.InsertColumn(i, pCol[i], 0, nWidth / 3);
	}

	TCHAR* pCol2[] = { L"����",L"RVA",L"ƫ��",L"����",L"FAR��ַ"/*,L"���ݽ���"*/ };
	for (int i = 0; i < 5; ++i)
	{
		m_ListB.InsertColumn(i, pCol2[i], 0, nWidth / 5);
	}

	getRelocationInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
void CPERelocationDialog::getRelocationInfo()
{
	// �õ�����Ŀ¼��
	IMAGE_DATA_DIRECTORY* pDataDir = m_pOptHdr->DataDirectory;

	// ��ȡ�ض�λ��
	/*
	�ض�λ��ṹ��
	�ض�λ����һ����һ�����ϵ��ض�λ��ṹ�����
	�ض�λ����һ�����ض�λ��ṹ��ļ���(Ҳ����һ������),��������һ��ȫ0��Ԫ����Ϊ
	�����ı�־.
	typedef struct _IMAGE_BASE_RELOCATION {
	DWORD   VirtualAddress; // �����ʼRVA
	DWORD   SizeOfBlock;    // ������Ĵ�С(����VirtualAddress��SizeOfBlock�����ֶεĴ�С)
	//WORD    TypeOffset[1];
	} IMAGE_BASE_RELOCATION;
	*/
	IMAGE_BASE_RELOCATION* pBaseRel;
	pBaseRel = (IMAGE_BASE_RELOCATION*)(PERVAToOffset::RVAToOffset(m_pDosHDr, pDataDir[5].VirtualAddress) + (DWORD)m_pDosHDr);

	CString strFormat;
	int lcow = 0;
	int  line = 0;
	while (pBaseRel->VirtualAddress != 0)
	{
		// �õ��ض�λ��ĸ���
		DWORD dwCount =
			(pBaseRel->SizeOfBlock - (sizeof(IMAGE_BASE_RELOCATION))) / sizeof(WORD);

		strFormat.Format(L"%d", lcow + 1);
		m_ListA.InsertItem(lcow, strFormat);

		strFormat.Format(L"%08X", pBaseRel->VirtualAddress);
		m_ListA.SetItemText(lcow, ++line, strFormat);


		strFormat.Format(L"%0Xh/%d\d", dwCount, dwCount);
		m_ListA.SetItemText(lcow, ++line, strFormat);

		// �õ��ض�λ��Ŀ�ʼ��ַ
		TypeOffset* pTypeOffset = (TypeOffset*)(pBaseRel + 1);
		int lcow2 = 0;
		int line2 = 0;
		for (DWORD i = 0; i < dwCount; ++i)
		{
			if (pTypeOffset[i].Type == IMAGE_REL_BASED_HIGHLOW) {

				strFormat.Format(L"%d", i + 1);
				m_ListB.InsertItem(lcow2, strFormat);

				// �õ���Ҫ�޸���RVA
				DWORD dwRva = pBaseRel->VirtualAddress + pTypeOffset[i].Offset;
				strFormat.Format(L"%08X", dwRva);
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				DWORD dwOffset = PERVAToOffset::RVAToOffset(m_pDosHDr, dwRva);
				strFormat.Format(L"%08X", dwOffset);
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				strFormat.Format(L"%s", L"HIGHLOW (3)");
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				// �õ���Ҫ�޸���opcode��ַ�����������ڵĵ�ַ
				DWORD* pAddress = (DWORD*)(dwOffset + (DWORD)m_pDosHDr);
				strFormat.Format(L"%08X", *pAddress);
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				++lcow2;
				line2 = 0;
			}
		}

		// �ҵ���һ���ض�λ��
		pBaseRel = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseRel + pBaseRel->SizeOfBlock);
		++lcow;
		line = 0;
	}
}