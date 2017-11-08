// PESectorTableDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "PESectorDialog.h"
#include "afxdialogex.h"
#include "Resource.h"


// CPESectorTableDialog 对话框

IMPLEMENT_DYNAMIC(PESectorDialog, CDialogEx)

PESectorDialog::PESectorDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_SECTION, pParent)
{

}

PESectorDialog::~PESectorDialog()
{
}

void PESectorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_SectionList);
}


BEGIN_MESSAGE_MAP(PESectorDialog, CDialogEx)
END_MESSAGE_MAP()


// CPESectorTableDialog 消息处理程序


BOOL PESectorDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_SectionList.GetClientRect(&rc);//指定工作区大小
	int nWidth = rc.Width();
	TCHAR* pcol[] = { L"名称",L"VOffset",L"VSize",L"ROffset",L"RSize",L"标志" };
	for (int i = 0; i < 6; i++)
	{
		m_SectionList.InsertColumn(i, pcol[i], 0, nWidth / 6);
	}
	getSectorTableInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void PESectorDialog::getSectorTableInfo()
{
	
	//添加行内容
	int j = 0;
	CString str;
	for (int i = 0; i < m_pFileHdr->NumberOfSections; i++)
	{

		str.Format(L"%S", m_pScnHdr[i].Name);
		m_SectionList.InsertItem(i, str);

		str.Format(L"%08X", m_pScnHdr[i].VirtualAddress);
		m_SectionList.SetItemText(i, ++j, str);

		str.Format(L"%08X", m_pScnHdr[i].SizeOfRawData);
		m_SectionList.SetItemText(i, ++j, str);

		str.Format(L"%08X", m_pScnHdr[i].PointerToRawData);
		m_SectionList.SetItemText(i, ++j, str);

		str.Format(L"%08X", m_pScnHdr[i].Misc.VirtualSize);
		m_SectionList.SetItemText(i, ++j, str);

		str.Format(L"%08X", m_pScnHdr[i].Characteristics);
		m_SectionList.SetItemText(i, ++j, str);

		j = 0;
	}

	UpdateData(FALSE);

}