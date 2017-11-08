#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;


// CClearInterface 对话框

class CClearInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CClearInterface)

public:
	CClearInterface(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CClearInterface();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5_CLEAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	vector<CString>m_vecClearFile;

	CButton m_btnVS;
	CButton m_btnSystem;
	CButton m_btnBrowser;		//浏览器
	CButton m_btnTrash;			//回收站

	CString m_editSuffix;		//编辑框后缀
	CListBox m_listBoxFolder;	

	CString m_strSystemPath = L"C:\\Windows\\Temp";																//系统垃圾路径
	CString m_strUsePath = L"C:\\Users\\kevin\\AppData\\Local\\Temp";											//用户临时文件路径
	CString m_strWinErrPath = L"C:\\Users\\kevin\\AppData\\Local\\Microsoft\\Windows\\WER\\ReportQueue";		//womdpws错误报告																							//windows错误报告路径
	CString m_strBrowserPath = L"C:\\Users\\卢漫瞳\\AppData\\Local\\Tencent\\QQBrowser\\User Data\\Default";	//浏览器
	CString m_strVSPath = L"D:\\VS";																			//VS路径
	CString m_strTrashPath = L"C:";																				//回收站路径
	CString m_strVSPosfix = L".db.obj.tlog.lastbuildstate.idb.pdb.pch.res.ilk.exe.sdf.ipch.log";				//vs垃圾后缀
	CString m_strOtherPosfix = L".tlog.obj.log.pch.ilk.pdb";													//其他系统垃圾后缀

	bool getFilePath(const TCHAR* pszDir, int nDeep = 2);
	afx_msg void OnScanFileBtn();
	afx_msg void OnBnClickedStartClear();
	void  clearTrash();

	CRect rt;
};
