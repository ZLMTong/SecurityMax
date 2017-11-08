// PERelocationDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PERelocationDialog.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "PERVAToOffset.h"


// CPERelocationDialog 对话框

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


// CPERelocationDialog 消息处理程序


BOOL CPERelocationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListA.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListB.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CRect rc;
	m_ListA.GetClientRect(&rc);
	int nWidth = rc.Width();
	TCHAR* pCol[] = { L"索引",/*L"区段",*/L"RVA",L"项目" };
	for (int i = 0; i < 3; ++i)
	{
		m_ListA.InsertColumn(i, pCol[i], 0, nWidth / 3);
	}

	TCHAR* pCol2[] = { L"索引",L"RVA",L"偏移",L"类型",L"FAR地址"/*,L"数据解释"*/ };
	for (int i = 0; i < 5; ++i)
	{
		m_ListB.InsertColumn(i, pCol2[i], 0, nWidth / 5);
	}

	getRelocationInfo();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CPERelocationDialog::getRelocationInfo()
{
	// 得到数据目录表
	IMAGE_DATA_DIRECTORY* pDataDir = m_pOptHdr->DataDirectory;

	// 获取重定位表
	/*
	重定位块结构体
	重定位表由一个或一个以上的重定位块结构体组成
	重定位表是一个由重定位块结构体的集合(也就是一个数组),数组是以一个全0的元素最为
	结束的标志.
	typedef struct _IMAGE_BASE_RELOCATION {
	DWORD   VirtualAddress; // 块的起始RVA
	DWORD   SizeOfBlock;    // 整个块的大小(包括VirtualAddress和SizeOfBlock两个字段的大小)
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
		// 得到重定位项的个数
		DWORD dwCount =
			(pBaseRel->SizeOfBlock - (sizeof(IMAGE_BASE_RELOCATION))) / sizeof(WORD);

		strFormat.Format(L"%d", lcow + 1);
		m_ListA.InsertItem(lcow, strFormat);

		strFormat.Format(L"%08X", pBaseRel->VirtualAddress);
		m_ListA.SetItemText(lcow, ++line, strFormat);


		strFormat.Format(L"%0Xh/%d\d", dwCount, dwCount);
		m_ListA.SetItemText(lcow, ++line, strFormat);

		// 得到重定位项的开始地址
		TypeOffset* pTypeOffset = (TypeOffset*)(pBaseRel + 1);
		int lcow2 = 0;
		int line2 = 0;
		for (DWORD i = 0; i < dwCount; ++i)
		{
			if (pTypeOffset[i].Type == IMAGE_REL_BASED_HIGHLOW) {

				strFormat.Format(L"%d", i + 1);
				m_ListB.InsertItem(lcow2, strFormat);

				// 得到需要修复的RVA
				DWORD dwRva = pBaseRel->VirtualAddress + pTypeOffset[i].Offset;
				strFormat.Format(L"%08X", dwRva);
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				DWORD dwOffset = PERVAToOffset::RVAToOffset(m_pDosHDr, dwRva);
				strFormat.Format(L"%08X", dwOffset);
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				strFormat.Format(L"%s", L"HIGHLOW (3)");
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				// 得到需要修复的opcode地址操作数的所在的地址
				DWORD* pAddress = (DWORD*)(dwOffset + (DWORD)m_pDosHDr);
				strFormat.Format(L"%08X", *pAddress);
				m_ListB.SetItemText(lcow2, ++line2, strFormat);

				++lcow2;
				line2 = 0;
			}
		}

		// 找到下一个重定位块
		pBaseRel = (IMAGE_BASE_RELOCATION*)((DWORD)pBaseRel + pBaseRel->SizeOfBlock);
		++lcow;
		line = 0;
	}
}