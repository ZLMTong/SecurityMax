#pragma once
#include "afxcmn.h"


// PESectorDialog 对话框

class PESectorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PESectorDialog)

public:
	PESectorDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~PESectorDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_SECTION};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRect rc;
	CListCtrl m_SectionList;
	IMAGE_SECTION_HEADER* m_pScnHdr;//扩展头
	IMAGE_FILE_HEADER* m_pFileHdr;//文件头
	virtual BOOL OnInitDialog();
	void getSectorTableInfo();
};
