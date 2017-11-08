// PEImportDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PEImportDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPEImportDialog 对话框

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


// CPEImportDialog 消息处理程序


BOOL CPEImportDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrlA.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrlB.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rc;
	m_ListCtrlA.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"DLL名称",L"OriginalFirstThunk",L"日期时间标志",L"ForwarderChain",L"名称",L"FirstThunk" };
	for (int i = 0; i < 6; ++i)
	{
		m_ListCtrlA.InsertColumn(i, pCol[i], 0, nWidth / 6);
	}

	TCHAR* pCol2[] = { L"ThunkRVA",L"Thunk偏移",L"Thunk值",L"提示",L"API名称" };
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
				  // 异常: OCX 属性页应返回 FALSE
}

void CPEImportDialog::getImportTableInfo()
{

	// 4. 找到数据目录表
	IMAGE_DATA_DIRECTORY* pDataDir = NULL;
	pDataDir = m_pOptHdr->DataDirectory;
	// 5. 得到导入表的RVA
	DWORD dwImpRva = pDataDir[1].VirtualAddress;

	IMAGE_IMPORT_DESCRIPTOR  *pImpArray;

	pImpArray = (IMAGE_IMPORT_DESCRIPTOR*)
		(PERVAToOffset::RVAToOffset(m_pDosHdr, dwImpRva) + (DWORD)m_pDosHdr);

	// 导入表数组的个数并没有其它字段记录.
	// 结束的标志是以一个全0的元素作为结尾
	CString strFormat;
	int line = 0;
	int lcow = 0;

	while (pImpArray->Name != 0)
	{

		// 导入的Dll的名字(Rva)
		DWORD dwNameOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pImpArray->Name);
		WCHAR* pDllName = (WCHAR*)(dwNameOfs + (DWORD)m_pDosHdr);

		strFormat.Format(L"%S", pDllName);
		m_ListCtrlA.InsertItem(lcow, strFormat);

		// 解析,在这个dll中,一共导入哪些函数
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

		// INT(导入名表)
		// 记录着一个从一个dll中导入了哪些函数
		// 这些函数要么是以名称导入,要么是以序号导入的
		// 到记录在一个数组中. 这个数组是IMAGE_THUNK_DATA
		// 类型的结构体数组.
		// FirstThunk保存着数组的RVA
		pImpArray->FirstThunk;
		DWORD INTOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pImpArray->FirstThunk);
		DWORD IATOfs = PERVAToOffset::RVAToOffset(m_pDosHdr, pImpArray->FirstThunk);
		
		/*
		这是一个只有4个字节的结构体.里面联合体中的每一个字段保存的
		值都是一样.
		这些值, 就是导入函数的信息.
		导入函数的信息有以下部分:
		1. 导入函数的序号
		2. 导入函数的名称(可能有可能没有)
		可以根据结构体中的字段的最高位判断, 导入信息
		是以名称导入还是以序号导入
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
