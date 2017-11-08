#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// COptimization 对话框

class COptimization : public CDialogEx
{
	DECLARE_DYNAMIC(COptimization)

public:
	COptimization(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COptimization();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6_OPTIMIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMemoryOptimize();
	void clearMemory();
	HICON m_hIcon;
	CProgressCtrl m_Internal;
	CProgressCtrl m_CPU;
	CListBox m_listboxCPU;
	CListBox m_listboxMemory;
	CString m_strCPU;
	CString m_strMemory;
};
