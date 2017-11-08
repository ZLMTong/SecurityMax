// PEDelayloadDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PEDelayloadDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPEDelayloadDialog 对话框

IMPLEMENT_DYNAMIC(CPEDelayloadDialog, CDialogEx)

CPEDelayloadDialog::CPEDelayloadDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_DELAY, pParent)
{
	
}

CPEDelayloadDialog::~CPEDelayloadDialog()
{
}

void CPEDelayloadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_DelayList);
	DDX_Control(pDX, IDC_LIST2, m_listB);
}


BEGIN_MESSAGE_MAP(CPEDelayloadDialog, CDialogEx)
END_MESSAGE_MAP()


// CPEDelayloadDialog 消息处理程序


BOOL CPEDelayloadDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_DelayList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rc;
	m_DelayList.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"grAttrs", L"DLLName",L"Hmod(R)VA",L"IAT(R)VA",L"INT(R)VA",L"BoundIAT(R)VA", L"UnloadIAT(R)VA",L"TimeDateStamp" };
	for (int i = 0; i < 8; ++i)
	{
		m_DelayList.InsertColumn(i, pCol[i], 0, nWidth / 8);
	}

	m_listB.GetClientRect(&rc);
	int nWidthB = rc.Width();
	TCHAR* pColB[] = { L"Ordinal/Hint", L"API Name" };
	for (int i = 0; i < 2; ++i)
	{
		m_listB.InsertColumn(i, pColB[i], 0, nWidthB / 2);
	}

	getDelayloadInfo();
	GetImportInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CPEDelayloadDialog::getDelayloadInfo()
{
	// 4. 找到数据目录表
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	pDataDir = m_pOptHdr->DataDirectory;
	// 5. 得到导入表的RVA
	DWORD dwImpRva = pDataDir[13].VirtualAddress;
	if (!dwImpRva)
	{
		MessageBox(L"没有延迟导入表!");
		return;
	}
	IMAGE_DELAYLOAD_DESCRIPTOR* pDelayLoadHeader;
	pDelayLoadHeader = (IMAGE_DELAYLOAD_DESCRIPTOR*)
		(PERVAToOffset::RVAToOffset(m_pDosHDr, dwImpRva) + (DWORD)m_pDosHDr);

	CString strFormat;
	int lcow = 0;
	int  line = 0;
	while (pDelayLoadHeader->DllNameRVA != 0)
	{
		DWORD dwNameOf = PERVAToOffset::RVAToOffset(m_pDosHDr, pDelayLoadHeader->DllNameRVA);
		CHAR* dwNameDll = (CHAR*)(dwNameOf + (DWORD)m_pDosHDr);

		strFormat.Format(L"%08X", pDelayLoadHeader->Attributes);
		m_DelayList.InsertItem(lcow, strFormat);

		//DLL名
		strFormat = CString(dwNameDll);
		m_DelayList.SetItemText(lcow, ++line, strFormat);

		
		//模块句柄RVA
		strFormat.Format(L"%08X", pDelayLoadHeader->ModuleHandleRVA);
		m_DelayList.SetItemText(lcow, ++line, strFormat);
		//IAT
		strFormat.Format(L"%08X", pDelayLoadHeader->ImportAddressTableRVA);
		m_DelayList.SetItemText(lcow, ++line, strFormat);
		//INT
		strFormat.Format(L"%08X", pDelayLoadHeader->ImportNameTableRVA);
		m_DelayList.SetItemText(lcow, ++line, strFormat);
		//绑定IAT的RVA
		strFormat.Format(L"%08X", pDelayLoadHeader->BoundImportAddressTableRVA);
		m_DelayList.SetItemText(lcow, ++line, strFormat);

		strFormat.Format(L"%08X", pDelayLoadHeader->UnloadInformationTableRVA);
		m_DelayList.SetItemText(lcow, ++line, strFormat);

		strFormat.Format(L"%08X", pDelayLoadHeader->TimeDateStamp);
		m_DelayList.SetItemText(lcow, ++line, strFormat);


		++lcow;
		line = 0;
		++pDelayLoadHeader;
	}
}

void CPEDelayloadDialog::GetImportInfo()
{
	// 4. 找到数据目录表
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	pDataDir = m_pOptHdr->DataDirectory;
	// 5. 得到导入表的RVA
	DWORD dwImpRva = pDataDir[1].VirtualAddress;

	IMAGE_IMPORT_DESCRIPTOR  *pImpArray;

	pImpArray = (IMAGE_IMPORT_DESCRIPTOR*)
		(PERVAToOffset::RVAToOffset(m_pDosHDr, dwImpRva) + (DWORD)m_pDosHDr);

	pImpArray->FirstThunk;
	DWORD INTOfs = PERVAToOffset::RVAToOffset(m_pDosHDr, pImpArray->FirstThunk);

	m_pInt = (IMAGE_THUNK_DATA*)(INTOfs + (DWORD)m_pDosHDr);


	int lcowB = 0;
	int lineB = 0;
	CString strB;

	while (m_pInt->u1.Function != 0)
	{
		IMAGE_IMPORT_BY_NAME* pImpName;
		DWORD dwImpNameOfs = PERVAToOffset::RVAToOffset(m_pDosHDr, m_pInt->u1.Function);
		pImpName = (IMAGE_IMPORT_BY_NAME*)(dwImpNameOfs + (DWORD)m_pDosHDr);

		strB.Format(L"%d", pImpName->Hint);
		m_listB.InsertItem(lcowB, strB);

		strB.Format(L"%S", pImpName->Name);
		m_listB.SetItemText(lcowB, ++lineB, strB);

		++m_pInt;
		lineB = 0;
		lcowB++;
	}

}
