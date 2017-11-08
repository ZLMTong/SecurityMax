#pragma once
#include "afxcmn.h"


// CPEExportTableDialog 对话框

class CPEExportTableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPEExportTableDialog)

public:
	CPEExportTableDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEExportTableDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_EXPORT};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	

	IMAGE_DOS_HEADER* m_pDosHdr;// DOS头
	IMAGE_OPTIONAL_HEADER* m_pOptHdr;// 扩展头
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
