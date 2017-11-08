#pragma once


// PERVAToOffset 对话框

class PERVAToOffset : public CDialogEx
{
	DECLARE_DYNAMIC(PERVAToOffset)

public:
	PERVAToOffset(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PERVAToOffset();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4_CALCULATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_VA;
	CString m_RVA;
	CString m_Offset;

	IMAGE_DOS_HEADER* m_pDosHdr;
	IMAGE_OPTIONAL_HEADER* m_pOptHdr;
	IMAGE_SECTION_HEADER* m_pScnHdr;

	static DWORD RVAToOffset(IMAGE_DOS_HEADER* pDos, DWORD dwRva);
	afx_msg void OnExecute();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
