// MyDragDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "PEDragDialog.h"
#include "afxdialogex.h"


// CMyDragDialog �Ի���

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


// CMyDragDialog ��Ϣ�������


BOOL PEDragDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ChangeWindowMessageFilter(WM_DROPFILES, MSGFLT_ADD);
	ChangeWindowMessageFilter(0x0049, MSGFLT_ADD);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
