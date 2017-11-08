#pragma once
#include <windows.h>
#include "Md5.h"
#include <vector>
#include "afxwin.h"
using namespace std;

#define  WCHAR_TO_CHAR(lpW_Char, lpChar) \
    WideCharToMultiByte(CP_ACP, NULL, lpW_Char, -1, lpChar, _countof(lpChar), NULL, FALSE);


struct PathAndMd5
{
	char* cMd5Value;
	CString cFilePath;
};


// CKillVirus 对话框

class CKillVirus : public CDialogEx
{
	DECLARE_DYNAMIC(CKillVirus)

public:
	CKillVirus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKillVirus();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIALOG7_VIRUS
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	
	
public:
	bool getFilePath(const TCHAR* pszDir, int nDeep = 5);
	
	vector<CString> m_vctUpdataMd5Data;
	vector<CString>m_veMd5Data;
	vector<CString>m_veMd5File;
	vector<PathAndMd5>m_vePathAndMd5;
	vector<CString>m_vePreocess;
	CListBox m_VirusList;
	bool m_isClickVirus = false;

	afx_msg void OnStartVirus();
	afx_msg void OnFullPathKill();
	afx_msg void OnWhiteList();
	bool linkServer();
	SOCKET m_socketClient;
	CButton m_btnMd5;
	CButton m_btnAllPathKill;
	CButton m_btnWhiteName;
	afx_msg void OnYun();
};
