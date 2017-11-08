#pragma once
#include "PEDragListBox.h"
#include <afxdialogex.h>


// CMyDragDialog 对话框

class PEDragDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PEDragDialog)

public:
	PEDragDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PEDragDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4_PEOFFSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	PEDragListBox m_DragListBox;
	virtual BOOL OnInitDialog();
};
