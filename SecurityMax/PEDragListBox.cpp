// PEDragListBox.cpp : 实现文件
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



// PEDragListBox 消息处理程序




void PEDragListBox::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	TCHAR szPath[MAX_PATH] = {};
	// 统计拖拽的文件夹的数目
	int nCount = DragQueryFile(hDropInfo, -1, szPath, MAX_PATH);
	// 分别获取每个文件夹的路径
	for (int i = 0; i < nCount; i++)
	{
		DragQueryFile(hDropInfo, i, szPath, MAX_PATH);
		if (LB_ERR == FindString(0, szPath))
		{// 如果m_ListBox里面没有这个新的文件夹路径，再添加进m_ListBox
			AddString(szPath);
		}
		PEEditorDialog dialog;
		dialog.m_FilePath = szPath;
		dialog.DoModal();

	}

	CListBox::OnDropFiles(hDropInfo);
}
