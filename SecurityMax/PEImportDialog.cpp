// PEImportDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEImportDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPEImportDialog �Ի���

IMPLEMENT_DYNAMIC(CPEImportDialog, CDialogEx)

CPEImportDialog::CPEImportDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_IMPORT, pParent)
{

}

CPEImportDialog::~CPEImportDialog()
{
}

void CPEImportDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrlA);
	DDX_Control(pDX, IDC_LIST2, m_ListCtrlB);
}


BEGIN_MESSAGE_MAP(CPEImportDialog, CDialogEx)
END_MESSAGE_MAP()


// CPEImportDialog ��Ϣ�������


BOOL CPEImportDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ListCtrlA.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlB.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rc;
	m_ListCtrlA.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"DLL����",L"OriginalFirstThunk",L"����ʱ���־",L"ForwarderChain",L"����",L"FirstThunk" };
	for (int i = 0; i < 6; ++i)
	{
		m_ListCtrlA.InsertColumn(i, pCol[i], 0, nWidth / 6);
	}

	TCHAR* pCol2[] = { L"ThunkRVA",L"Thunkƫ��",L"Thunkֵ",L"��ʾ",L"API����" };
	for (int i = 0; i < 5; ++i)
	{
		if (i <= 3)
		{
			m_ListCtrlB.InsertColumn(i, pCol2[i], 0, nWidth / 8);
		}
		else
			m_ListCtrlB.InsertColumn(i, pCol2[i], 0, nWidth / 2);
	}
	
	getImportTableInfo();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void CPEImportDialog::getImportTableInfo()
{

	// 4. �ҵ�����Ŀ¼��
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	pDataDir = m_pOptHdr->DataDirectory;
	// 5. �õ�������RVA
	DWORD dwImpRva = pDataDir[1].VirtualAddress;

	IMAGE_IMPORT_DESCRIPTOR  *pImpArray;

	pImpArray = (IMAGE_IMPORT_DESCRIPTOR*)
		(PERVAToOffset::RVAToOffset(m_pDosHdr, dwImpRva) + (DWORD)m_pDosHdr);

	// ���������ĸ�����û�������ֶμ�¼.
	// �����ı�־����һ��ȫ0��Ԫ����Ϊ��β
	CString strFormat;
	int line = 0;
	int lcow = 0;

	while (pImpArray->Name != 0)
	{

		// �����Dll������(Rva)
		DWORD dwNameOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pImpArray->Name);
		WCHAR* pDllName = (WCHAR*)(dwNameOfs + (DWORD)m_pDosHdr);

		strFormat.Format(L"%S", pDllName);
		m_ListCtrlA.InsertItem(lcow, strFormat);

		// ����,�����dll��,һ��������Щ����
		strFormat.Format(L"%08X", pImpArray->OriginalFirstThunk);
		m_ListCtrlA.SetItemText(lcow, ++line, strFormat);

		strFormat.Format(L"%08X", pImpArray->TimeDateStamp);
		m_ListCtrlA.SetItemText(lcow, ++line, strFormat);

		strFormat.Format(L"%08X", pImpArray->ForwarderChain);
		m_ListCtrlA.SetItemText(lcow, ++line, strFormat);

		strFormat.Format(L"%08X", pImpArray->Name);
		m_ListCtrlA.SetItemText(lcow, ++line, strFormat);

		strFormat.Format(L"%08X", pImpArray->FirstThunk);
		m_ListCtrlA.SetItemText(lcow, ++line, strFormat);

		// INT(��������)
		// ��¼��һ����һ��dll�е�������Щ����
		// ��Щ����Ҫô�������Ƶ���,Ҫô������ŵ����
		// ����¼��һ��������. ���������IMAGE_THUNK_DATA
		// ���͵Ľṹ������.
		// FirstThunk�����������RVA
		pImpArray->FirstThunk;
		DWORD INTOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pImpArray->FirstThunk);
		DWORD IATOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pImpArray->FirstThunk);
		
		/*
		����һ��ֻ��4���ֽڵĽṹ��.�����������е�ÿһ���ֶα����
		ֵ����һ��.
		��Щֵ, ���ǵ��뺯������Ϣ.
		���뺯������Ϣ�����²���:
		1. ���뺯�������
		2. ���뺯��������(�����п���û��)
		���Ը��ݽṹ���е��ֶε����λ�ж�, ������Ϣ
		�������Ƶ��뻹������ŵ���
		typedef struct _IMAGE_THUNK_DATA32 {
		union {
		DWORD ForwarderString;      // PBYTE
		DWORD Function;             // PDWORD
		DWORD Ordinal;
		DWORD AddressOfData;        // PIMAGE_IMPORT_BY_NAME
		} u1;
		} IMAGE_THUNK_DATA32;
		*/
		pInt = (IMAGE_THUNK_DATA*)(INTOfs + (DWORD)m_pDosHdr);
		pIat = (IMAGE_THUNK_DATA*)(IATOfs + (DWORD)m_pDosHdr);

		int lcow2 = 0;
		int line2 = 0;
		int add4 = 0;

		while (pInt->u1.Function != 0)
		{
	
			IMAGE_IMPORT_BY_NAME* pImpName;
			DWORD dwImpNameOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pInt->u1.Function);
			pImpName = (IMAGE_IMPORT_BY_NAME*)
				(dwImpNameOfs + (DWORD)m_pDosHdr);

			strFormat.Format(L"%08X", pImpArray->OriginalFirstThunk + add4 * 4);
			m_ListCtrlB.InsertItem(lcow2, strFormat);

			strFormat.Format(L"%08X", PERVAToOffset::RVAToOffset(m_pDosHdr, pImpArray->OriginalFirstThunk) + add4 * 4);
			m_ListCtrlB.SetItemText(lcow2, ++line2, strFormat);

			strFormat.Format(L"%08X", pInt->u1.Function);
			m_ListCtrlB.SetItemText(lcow2, ++line2, strFormat);

			strFormat.Format(L"%04X", pImpName->Hint);
			m_ListCtrlB.SetItemText(lcow2, ++line2, strFormat);

			strFormat.Format(L"%S", pImpName->Name);
			m_ListCtrlB.SetItemText(lcow2, ++line2, strFormat);

			++pInt;
			line2 = 0;
			lcow2++;
			++add4;

		}
		line = 0;
		lcow++;
		++pImpArray;

	}
}
