#pragma once
#include "PEDragListBox.h"
#include <afxdialogex.h>


// CMyDragDialog �Ի���

class PEDragDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PEDragDialog)

public:
	PEDragDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PEDragDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4_PEOFFSET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	PEDragListBox m_DragListBox;
	virtual BOOL OnInitDialog();
};
