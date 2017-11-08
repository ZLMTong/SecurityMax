#pragma once
#include "afxcmn.h"


// CUSEInterface 对话框

class CUSEInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CUSEInterface)

public:
	CUSEInterface(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUSEInterface();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2_PROGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_useList;
	
};
