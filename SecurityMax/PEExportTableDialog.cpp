// PEExportTableDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEExportTableDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPEExportTableDialog �Ի���

IMPLEMENT_DYNAMIC(CPEExportTableDialog, CDialogEx)

CPEExportTableDialog::CPEExportTableDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_EXPORT, pParent)

	, m_offsetValues(_T(""))
	, m_characteristics(_T(""))
	, m_base(_T(""))
	, m_name(_T(""))
	, m_nameStr(_T(""))
	, m_numberOfFunctions(_T(""))
	, m_numberOfNames(_T(""))
	, m_addressOfFunctions(_T(""))
	, m_addressOfNames(_T(""))
	, m_addressOfNameOrdinals(_T(""))
{

}

CPEExportTableDialog::~CPEExportTableDialog()
{
}

void CPEExportTableDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_offsetValues);
	DDX_Text(pDX, IDC_EDIT3, m_characteristics);
	DDX_Text(pDX, IDC_EDIT5, m_base);
	DDX_Text(pDX, IDC_EDIT7, m_name);
	DDX_Text(pDX, IDC_EDIT9, m_nameStr);
	DDX_Text(pDX, IDC_EDIT2, m_numberOfFunctions);
	DDX_Text(pDX, IDC_EDIT4, m_numberOfNames);
	DDX_Text(pDX, IDC_EDIT6, m_addressOfFunctions);
	DDX_Text(pDX, IDC_EDIT8, m_addressOfNames);
	DDX_Text(pDX, IDC_EDIT10, m_addressOfNameOrdinals);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CPEExportTableDialog, CDialogEx)
END_MESSAGE_MAP()


// CPEExportTableDialog ��Ϣ�������

void CPEExportTableDialog::getExportTableInfo()
{

	CRect rc;
	m_listCtrl.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"���",L"RVA",L"ƫ��",L"������" };
	for (int i = 0; i < 4; ++i)
	{
		m_listCtrl.InsertColumn(i, pCol[i], 0, nWidth / 4);
	}

	// 4. �ҵ�����Ŀ¼��
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	pDataDir = m_pOptHdr->DataDirectory;
	// 5. �ҵ�������
	DWORD dwExpRva = pDataDir[0].VirtualAddress;

	// 5.1 �õ�RVA���ļ�ƫ��
	DWORD dwExpOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, dwExpRva);
	IMAGE_EXPORT_DIRECTORY* pExpTab = NULL;
	pExpTab = (IMAGE_EXPORT_DIRECTORY*)(dwExpOfs + (DWORD)m_pDosHdr);


	// 1. ����DLL����

	DWORD dwNameOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpTab->Name);
	char* pDllName =
		(char*)(dwNameOfs + (DWORD)m_pDosHdr);

	m_offsetValues.Format(L"%08X", dwExpOfs);
	m_nameStr.Format(L"%S", pDllName);
	m_characteristics.Format(L"%08X", pExpTab->Characteristics);
	m_base.Format(L"%08X", pExpTab->Base);
	m_name.Format(L"%08X", pExpTab->Name);

	m_numberOfFunctions.Format(L"%08X", pExpTab->NumberOfFunctions);
	m_numberOfNames.Format(L"%08X", pExpTab->NumberOfNames);
	m_addressOfFunctions.Format(L"%08X", pExpTab->AddressOfFunctions);
	m_addressOfNames.Format(L"%08X", pExpTab->AddressOfNames);
	m_addressOfNameOrdinals.Format(L"%08X", pExpTab->AddressOfNameOrdinals);


	// �������ű�
	DWORD dwExpAddrTabOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpTab->AddressOfFunctions);
	DWORD dwExpNameTabOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpTab->AddressOfNames);
	DWORD dwExpOrdTabOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpTab->AddressOfNameOrdinals);

	// �����еĵ�ַ��,���ƶ���һ��DWORD��������
	DWORD* pExpAddr =
		(DWORD*)(dwExpAddrTabOfs + (DWORD)m_pDosHdr);

	DWORD* pExpName =
		(DWORD*)(dwExpNameTabOfs + (DWORD)m_pDosHdr);

	// ��ű���WORD���͵�����
	DWORD* pExpOrd =
		(DWORD*)(dwExpOrdTabOfs + (DWORD)m_pDosHdr);

	CString strFormat;
	int line = 0;
	// �������еĺ�����ַ
	for (int i = 0; i< pExpTab->NumberOfFunctions; ++i)
	{

		strFormat.Format(L"%04X", ((DWORD)i + pExpTab->Base));
		m_listCtrl.InsertItem(i, strFormat);

		strFormat.Format(L"%08X", pExpAddr[i]);
		m_listCtrl.SetItemText(i, ++line, strFormat);

		DWORD dFileOffset = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpAddr[i]);

		strFormat.Format(L"%08X", dFileOffset);
		m_listCtrl.SetItemText(i, ++line, strFormat);

		DWORD dwNameRva = pExpName[i];
		DWORD dwNameOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, dwNameRva);

		WCHAR* pFunctionName = nullptr;
		pFunctionName = (WCHAR*)(dwNameOfs + (DWORD)m_pDosHdr);
		strFormat.Format(L"%S", pFunctionName);
		m_listCtrl.SetItemText(i, ++line, strFormat);

		line = 0;
	}
	UpdateData(FALSE);
}


BOOL CPEExportTableDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	getExportTableInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
