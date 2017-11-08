#pragma once
#include <afxdialogex.h>


// CPEDirctoryTableDialog 对话框

class CPEDirctoryTableDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPEDirctoryTableDialog)

public:
	CPEDirctoryTableDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPEDirctoryTableDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_CATALOGUE};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	IMAGE_FILE_HEADER* m_pFileHdr;		//文件头
	IMAGE_OPTIONAL_HEADER* m_pOptHdr;
	IMAGE_DOS_HEADER* m_pDosHdr;
	IMAGE_SECTION_HEADER* m_pScnHdr;
	void getDirctoryInfo(IMAGE_OPTIONAL_HEADER* pOptHdr);
	virtual BOOL OnInitDialog();

	CString m_exportRva;
	CString m_exportSize;
	CString m_importRva;
	CString m_importSize;
	CString m_resourceRva;
	CString m_resourceSize;
	CString m_exceptionRva;
	CString m_exceptionSize;
	CString m_securityRva;
	CString m_securitySize;
	CString m_baserelocRva;
	CString m_baserelocSize;
	CString m_debugRva;
	CString m_debugSize;
	CString m_architectureRva;
	CString m_architectureSize;
	CString m_globalptrRva;
	CString m_globalptrSize;
	CString m_tlsRva;
	CString m_tlsSize;
	CString m_loadRva;
	CString m_loadSize;
	CString m_importBundRva;
	CString m_importBundSize;
	CString m_iatRva;
	CString m_iatSize;
	CString m_importDelayRva;
	CString m_importDelaySize;
	CString m_comRva;
	CString m_comSize;
	CString m_retainRva;
	CString m_retainSize;
	afx_msg void OnExport();
	afx_msg void OnImport();
	afx_msg void OnDelay();
	afx_msg void OnReloction();
	afx_msg void OnTLS();
	afx_msg void OnResource();
};
