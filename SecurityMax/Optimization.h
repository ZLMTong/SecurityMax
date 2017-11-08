#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// COptimization �Ի���

class COptimization : public CDialogEx
{
	DECLARE_DYNAMIC(COptimization)

public:
	COptimization(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptimization();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6_OPTIMIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
