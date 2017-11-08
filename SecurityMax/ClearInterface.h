#pragma once
#include "afxwin.h"
#include <vector>
using namespace std;


// CClearInterface �Ի���

class CClearInterface : public CDialogEx
{
	DECLARE_DYNAMIC(CClearInterface)

public:
	CClearInterface(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CClearInterface();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5_CLEAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	vector<CString>m_vecClearFile;

	CButton m_btnVS;
	CButton m_btnSystem;
	CButton m_btnBrowser;		//�����
	CButton m_btnTrash;			//����վ

	CString m_editSuffix;		//�༭���׺
	CListBox m_listBoxFolder;	

	CString m_strSystemPath = L"C:\\Windows\\Temp";																//ϵͳ����·��
	CString m_strUsePath = L"C:\\Users\\kevin\\AppData\\Local\\Temp";											//�û���ʱ�ļ�·��
	CString m_strWinErrPath = L"C:\\Users\\kevin\\AppData\\Local\\Microsoft\\Windows\\WER\\ReportQueue";		//womdpws���󱨸�																							//windows���󱨸�·��
	CString m_strBrowserPath = L"C:\\Users\\¬��ͫ\\AppData\\Local\\Tencent\\QQBrowser\\User Data\\Default";	//�����
	CString m_strVSPath = L"D:\\VS";																			//VS·��
	CString m_strTrashPath = L"C:";																				//����վ·��
	CString m_strVSPosfix = L".db.obj.tlog.lastbuildstate.idb.pdb.pch.res.ilk.exe.sdf.ipch.log";				//vs������׺
	CString m_strOtherPosfix = L".tlog.obj.log.pch.ilk.pdb";													//����ϵͳ������׺

	bool getFilePath(const TCHAR* pszDir, int nDeep = 2);
	afx_msg void OnScanFileBtn();
	afx_msg void OnBnClickedStartClear();
	void  clearTrash();

	CRect rt;
};
