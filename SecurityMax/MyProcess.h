#pragma once
#include "afxcmn.h"
#include<windows.h>
#include <TlHelp32.h>
#include "MyProcessList.h"

// CMyProcess �Ի���

class CMyProcess : public CDialogEx
{
	DECLARE_DYNAMIC(CMyProcess)

public:
	CMyProcess(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyProcess();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyProcessList m_ProcessList;
	virtual BOOL OnInitDialog();
	PROCESSENTRY32 Pe32;			//���̿�����Ϣ
	void TraversalProcess();		//��������

};
