#pragma once
#include "afxcmn.h"


// CUSEInterface �Ի���

class CUSEInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CUSEInterface)

public:
	CUSEInterface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUSEInterface();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2_PROGRAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_useList;
	
};
