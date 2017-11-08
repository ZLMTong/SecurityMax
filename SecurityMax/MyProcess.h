#pragma once
#include "afxcmn.h"
#include<windows.h>
#include <TlHelp32.h>
#include "MyProcessList.h"

// CMyProcess 对话框

class CMyProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CMyProcess)

public:
	CMyProcess(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyProcess();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyProcessList m_ProcessList;
	virtual BOOL OnInitDialog();
	PROCESSENTRY32 Pe32;			//进程快照信息
	void TraversalProcess();		//遍历进程

};
