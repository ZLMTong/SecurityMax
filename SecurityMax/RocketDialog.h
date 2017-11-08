#pragma once


// CRocketDialog 对话框

class CRocketDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRocketDialog)

public:
	CRocketDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRocketDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6_ROCKET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


	CBitmap m_bitmap;
	BITMAP m_bitinfo;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	
};
