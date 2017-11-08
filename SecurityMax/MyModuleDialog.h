#pragma once
#include "afxcmn.h"
#include "MyModuleList.h"


// CMyModuleDialog �Ի���

class CMyModuleDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CMyModuleDialog)

public:
	CMyModuleDialog(CWnd* pParent = NULL);   // ��׼���캯��
	CMyModuleDialog(DWORD processID, CWnd* pParent = NULL);
	virtual ~CMyModuleDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_MODULE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	DWORD m_processID;
	CMyModuleList m_ModuleList;
	bool GetModuleInfo();
	virtual BOOL OnInitDialog();
};
