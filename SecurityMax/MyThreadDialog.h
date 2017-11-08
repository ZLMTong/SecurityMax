#pragma once
#include "afxcmn.h"


// CMyThreadDialog 对话框

class CMyThreadDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyThreadDialog)

public:
	CMyThreadDialog(CWnd* pParent = NULL);   // 标准构造函数
	CMyThreadDialog(DWORD processID, CWnd* pParent = NULL);
	virtual ~CMyThreadDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_THREAD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ThreadList;
	DWORD m_processID;
	CString m_stcInfo;		//错误码
	DWORD m_dwProcId;		//进程ID
	bool GetThreadInfo(DWORD dwProceId);
	virtual BOOL OnInitDialog();
};
