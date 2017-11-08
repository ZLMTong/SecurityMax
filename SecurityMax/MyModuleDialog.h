#pragma once
#include "afxcmn.h"
#include "MyModuleList.h"


// CMyModuleDialog 对话框

class CMyModuleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyModuleDialog)

public:
	CMyModuleDialog(CWnd* pParent = NULL);   // 标准构造函数
	CMyModuleDialog(DWORD processID, CWnd* pParent = NULL);
	virtual ~CMyModuleDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	DWORD m_processID;
	CMyModuleList m_ModuleList;
	bool GetModuleInfo();
	virtual BOOL OnInitDialog();
};
