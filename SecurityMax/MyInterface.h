#pragma once


// CMyInterface

class CMyInterface : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyInterface)

public:
	CMyInterface();
	virtual ~CMyInterface();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	DWORD m_dwCount;			//当前选项卡对话框数量
	CDialogEx* m_pDlg[20];		//选项卡中存储的对话框数组
	void InsertTab(DWORD dwCount, ...);		//插入选项卡
	void AddDlg(DWORD dwCount, ...);		//增加对话框
	void SetSelAndShow(int nSel);			//设置当前选中的对话框并显示
	afx_msg void OnSize(UINT nType, int cx, int cy);


	
};


