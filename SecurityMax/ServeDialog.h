#pragma once
#include "afxcmn.h"
#include <winsvc.h>
#include <vector>
using namespace std;


// CServeDialog 对话框

class CServeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CServeDialog)

public:
	CServeDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3_SERVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_serveList;
	CString m_strServiceStatue;
	vector<CString>m_ServiceName;
	int m_Index;
	int getServeInfo();
	LONG lRet = 0;
	BOOL bRet = FALSE;
	SC_HANDLE hSCM = NULL;              // 服务数据库句柄
	char *pBuf = NULL;                  // 缓冲区指针
	DWORD dwBufSize = 0;                // 传入的缓冲长度
	DWORD dwBufNeed = 0;                // 须要的缓冲长度
	DWORD dwNumberOfService = 0;        // 返回的服务个数
	ENUM_SERVICE_STATUS_PROCESS *pServiceInfo = NULL;   // 服务信息
	void getCurrentStatus(DWORD dwType);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	VOID __stdcall DoStartSvc(LPCTSTR szSvcName);
	VOID __stdcall DoStopSvc(LPCTSTR szSvcName);
	BOOL __stdcall StopDependentServices(SC_HANDLE schService, SC_HANDLE schSCManager);
	afx_msg void OnStart();
	afx_msg void OnClose();
};
