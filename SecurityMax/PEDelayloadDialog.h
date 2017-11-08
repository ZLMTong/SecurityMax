#pragma once
#include "afxcmn.h"
#include "PEImportDialog.h"


// CPEDelayloadDialog �Ի���

class CPEDelayloadDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPEDelayloadDialog)

public:
	CPEDelayloadDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEDelayloadDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_DELAY};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	IMAGE_OPTIONAL_HEADER* m_pOptHdr;
	IMAGE_DOS_HEADER* m_pDosHDr;
	void getDelayloadInfo();
	void GetImportInfo();

	CListCtrl m_DelayList;
	CListCtrl m_listB;

	IMAGE_THUNK_DATA* m_pInt = NULL;
};
