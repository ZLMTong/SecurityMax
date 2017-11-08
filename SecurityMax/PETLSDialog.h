#pragma once


// CPETLSDialog 对话框

class CPETLSDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPETLSDialog)

public:
	CPETLSDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPETLSDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4_TLS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	

	IMAGE_OPTIONAL_HEADER* m_pOptHdr;
	IMAGE_DOS_HEADER* m_pDosHDr;
	void getTLSInfo();
	virtual BOOL OnInitDialog();
	CString m_startAddressOfRawData;
	CString m_endAddressOfRawData;
	CString m_addressOfIndex;
	CString m_addressOfCallBacks;
	CString m_sizeOfZeroFill;
	CString m_characteristics;
};
