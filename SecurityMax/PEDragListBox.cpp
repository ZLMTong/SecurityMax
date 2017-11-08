// PEDragListBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "PEDragListBox.h"
#include "PEEditorDialog.h"


// PEDragListBox

IMPLEMENT_DYNAMIC(PEDragListBox, CListBox)

PEDragListBox::PEDragListBox()
{

}

PEDragListBox::~PEDragListBox()
{
}


BEGIN_MESSAGE_MAP(PEDragListBox, CListBox)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()



// PEDragListBox ��Ϣ�������




void PEDragListBox::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	TCHAR szPath[MAX_PATH] = {};
	// ͳ����ק���ļ��е���Ŀ
	int nCount = DragQueryFile(hDropInfo, -1, szPath, MAX_PATH);
	// �ֱ��ȡÿ���ļ��е�·��
	for (int i = 0; i < nCount; i++)
	{
		DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
		if (LB_ERR == FindString(0, szPath))
		{// ���m_ListBox����û������µ��ļ���·��������ӽ�m_ListBox
			AddString(szPath);
		}
		PEEditorDialog dialog;
		dialog.m_FilePath = szPath;
		dialog.DoModal();

	}

	CListBox::OnDropFiles(hDropInfo);
}
