#pragma once
#include "afxcmn.h"


// CPEImportDialog 对话框

class CPEImportDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPEImportDialog)

public:
	CPEImportDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEImportDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_IMPORT};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	IMAGE_OPTIONAL_HEADER* m_pOptHdr;
	IMAGE_DOS_HEADER* m_pDosHdr;

	IMAGE_THUNK_DATA* pInt = NULL;
	IMAGE_THUNK_DATA* pIat = NULL;

	virtual BOOL OnInitDialog();
	void getImportTableInfo();

	CListCtrl m_ListCtrlA;
	CListCtrl m_ListCtrlB;
};
