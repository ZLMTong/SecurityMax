#pragma once
#include "afxcmn.h"


// CPEImportDialog �Ի���

class CPEImportDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPEImportDialog)

public:
	CPEImportDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEImportDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_IMPORT};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
