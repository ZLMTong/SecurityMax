#pragma once
#include "afxcmn.h"


// CPEExportTableDialog �Ի���

class CPEExportTableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPEExportTableDialog)

public:
	CPEExportTableDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEExportTableDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_EXPORT};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	

	IMAGE_DOS_HEADER* m_pDosHdr;// DOSͷ
	IMAGE_OPTIONAL_HEADER* m_pOptHdr;// ��չͷ
	void getExportTableInfo();
	virtual BOOL OnInitDialog();
	CString m_offsetValues;
	CString m_characteristics;
	CString m_base;
	CString m_name;
	CString m_nameStr;
	CString m_numberOfFunctions;
	CString m_numberOfNames;
	CString m_addressOfFunctions;
	CString m_addressOfNames;
	CString m_addressOfNameOrdinals;
	CListCtrl m_listCtrl;
};
