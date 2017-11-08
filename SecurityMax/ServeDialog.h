#pragma once
#include "afxcmn.h"
#include <winsvc.h>
#include <vector>
using namespace std;


// CServeDialog �Ի���

class CServeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CServeDialog)

public:
	CServeDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServeDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3_SERVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	SC_HANDLE hSCM = NULL;              // �������ݿ���
	char *pBuf = NULL;                  // ������ָ��
	DWORD dwBufSize = 0;                // ����Ļ��峤��
	DWORD dwBufNeed = 0;                // ��Ҫ�Ļ��峤��
	DWORD dwNumberOfService = 0;        // ���صķ������
	ENUM_SERVICE_STATUS_PROCESS *pServiceInfo = NULL;   // ������Ϣ
	void getCurrentStatus(DWORD dwType);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	VOID __stdcall DoStartSvc(LPCTSTR szSvcName);
	VOID __stdcall DoStopSvc(LPCTSTR szSvcName);
	BOOL __stdcall StopDependentServices(SC_HANDLE schService, SC_HANDLE schSCManager);
	afx_msg void OnStart();
	afx_msg void OnClose();
};
