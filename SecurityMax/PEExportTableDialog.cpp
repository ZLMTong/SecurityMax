// PEExportTableDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PEExportTableDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPEExportTableDialog 对话框

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


// CPEExportTableDialog 消息处理程序

void CPEExportTableDialog::getExportTableInfo()
{

	CRect rc;
	m_listCtrl.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"序号",L"RVA",L"偏移",L"函数名" };
	for (int i = 0; i < 4; ++i)
	{
		m_listCtrl.InsertColumn(i, pCol[i], 0, nWidth / 4);
	}

	// 4. 找到数据目录表
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	pDataDir = m_pOptHdr->DataDirectory;
	// 5. 找到导出表
	DWORD dwExpRva = pDataDir[0].VirtualAddress;

	// 5.1 得到RVA的文件偏移
	DWORD dwExpOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, dwExpRva);
	IMAGE_EXPORT_DIRECTORY* pExpTab = NULL;
	pExpTab = (IMAGE_EXPORT_DIRECTORY*)(dwExpOfs + (DWORD)m_pDosHdr);


	// 1. 解析DLL的名

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


	// 解析三张表
	DWORD dwExpAddrTabOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpTab->AddressOfFunctions);
	DWORD dwExpNameTabOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpTab->AddressOfNames);
	DWORD dwExpOrdTabOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pExpTab->AddressOfNameOrdinals);

	// 三张中的地址表,名称都是一个DWORD类型数组
	DWORD* pExpAddr =
		(DWORD*)(dwExpAddrTabOfs + (DWORD)m_pDosHdr);

	DWORD* pExpName =
		(DWORD*)(dwExpNameTabOfs + (DWORD)m_pDosHdr);

	// 序号表是WORD类型的数组
	DWORD* pExpOrd =
		(DWORD*)(dwExpOrdTabOfs + (DWORD)m_pDosHdr);

	CString strFormat;
	int line = 0;
	// 遍历所有的函数地址
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

	// TODO:  在此添加额外的初始化
	getExportTableInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
