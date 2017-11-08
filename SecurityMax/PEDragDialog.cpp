// MyDragDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "PEDragDialog.h"
#include "afxdialogex.h"


// CMyDragDialog 对话框

IMPLEMENT_DYNAMIC(PEDragDialog, CDialogEx)

PEDragDialog::PEDragDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4_PEOFFSET, pParent)
{

}

PEDragDialog::~PEDragDialog()
{
}

void PEDragDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_DragListBox);
}


BEGIN_MESSAGE_MAP(PEDragDialog, CDialogEx)
END_MESSAGE_MAP()


// CMyDragDialog 消息处理程序


BOOL PEDragDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
