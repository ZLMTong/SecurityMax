// ServeDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "ServeDialog.h"
#include "afxdialogex.h"
#include "Resource.h"


// CServeDialog �Ի���

IMPLEMENT_DYNAMIC(CServeDialog, CDialogEx)

CServeDialog::CServeDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3_SERVE, pParent)
{

}

CServeDialog::~CServeDialog()
{
}

void CServeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_serveList);
}


BEGIN_MESSAGE_MAP(CServeDialog, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CServeDialog::OnNMRClickList1)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32775, &CServeDialog::OnStart)
	ON_COMMAND(ID_32776, &CServeDialog::OnClose)
END_MESSAGE_MAP()


// CServeDialog ��Ϣ�������


BOOL CServeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//������չ���
	m_serveList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//����б���
	CRect rc;
	m_serveList.GetClientRect(&rc);//ָ����������С
	int nWidth = rc.Width();
	TCHAR* pcol[] = { L"����",L"PID",L"����",L"״̬" };
	for (int i = 0; i < 4; i++)
	{
		m_serveList.InsertColumn(i, pcol[i], 0, nWidth / 3);
	}
	getServeInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

int CServeDialog::getServeInfo()
{
	// ������һ����������ƹ����������ӣ�����ָ�������ݿ�
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CONNECT);
	if (NULL == hSCM)
	{
		MessageBox(L"OpenSCManager error");
		return -1;
	}

	// ��ȡ��Ҫ�Ļ�������С
	EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		NULL, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);

	// �����ô��1��������Ϣ�ĳ���
	dwBufSize = dwBufNeed + sizeof(ENUM_SERVICE_STATUS_PROCESS);
	pBuf = (char *)malloc(dwBufSize);
	if (NULL == pBuf)
	{
		MessageBox(L"malloc error");
		return -1;
	}
	memset(pBuf, 0, dwBufSize);

	// ��ȡ������Ϣ
	bRet = EnumServicesStatusEx(hSCM, SC_ENUM_PROCESS_INFO, SERVICE_WIN32, SERVICE_STATE_ALL,
		(LPBYTE)pBuf, dwBufSize, &dwBufNeed, &dwNumberOfService, NULL, NULL);
	if (bRet == FALSE)
	{
		MessageBox(L"EnumServicesStatusEx error");
		::CloseServiceHandle(hSCM);
		free(pBuf);
		return -1;
	}
	// �رմ򿪵ķ�����
	bRet = ::CloseServiceHandle(hSCM);
	if (bRet == FALSE)
	{
		MessageBox(L"CloseServiceHandle error");
	}

	pServiceInfo = (LPENUM_SERVICE_STATUS_PROCESS)pBuf;
	CString str;
	int line = 0;
	// ��ӡȡ�õķ�����Ϣ
	for (unsigned int i = 0; i < dwNumberOfService; i++)
	{
		//����
		str.Format(L"%s", pServiceInfo[i].lpServiceName);
		m_serveList.InsertItem(i, str);
		m_ServiceName.push_back(pServiceInfo[i].lpServiceName);
		//PID
		str.Format(L"%d", pServiceInfo[i].ServiceStatusProcess.dwProcessId);
		m_serveList.SetItemText(i, ++line, str);
		//����
		str.Format(L"%s", pServiceInfo[i].lpServiceName);
		m_serveList.SetItemText(i, ++line, str);
		//״̬
		getCurrentStatus(pServiceInfo[i].ServiceStatusProcess.dwCurrentState);
		m_serveList.SetItemText(i, ++line, m_strServiceStatue);
		line = 0;
	}
	free(pBuf);
	CloseServiceHandle(hSCM);
}

void CServeDialog::getCurrentStatus(DWORD dwType) {
	m_strServiceStatue = "";
	switch (dwType) {

	case SERVICE_STOPPED:
		//Not running
		m_strServiceStatue = "��ֹͣ";
		break;

	case SERVICE_START_PENDING:
		//"Starting"
		m_strServiceStatue = "��������";
		break;

	case SERVICE_STOP_PENDING:
		//Stopping
		m_strServiceStatue = "��ֹͣ";
		break;

	case SERVICE_RUNNING:
		//"Running"
		m_strServiceStatue = "��������";
		break;

	case SERVICE_CONTINUE_PENDING:
		//"Continue is pending"
		break;

	case SERVICE_PAUSE_PENDING:
		//"Pause is pending"
		break;

	case SERVICE_PAUSED:
		//"Paused"
		break;
	}
}

void CServeDialog::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	m_Index = pNMItemActivate->iItem;

	CMenu mu;
	mu.LoadMenuW(IDR_MENU2);
	CMenu *pmuSub = mu.GetSubMenu(0);

	CPoint pt;
	GetCursorPos(&pt);
	TrackPopupMenu(pmuSub->m_hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, m_hWnd, 0);
	*pResult = 0;
}

//��������
VOID __stdcall CServeDialog::DoStartSvc(LPCTSTR szSvcName)
{
	SERVICE_STATUS_PROCESS ssStatus;
	DWORD dwOldCheckPoint;
	DWORD dwStartTickCount;
	DWORD dwWaitTime;
	DWORD dwBytesNeeded;
	SC_HANDLE schSCManager = NULL;
	SC_HANDLE schService = NULL;
	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // servicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		
		//printf("OpenSCManager failed (%d)\n", GetLastError());
		return;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,         // SCM database 
		szSvcName,            // name of service 
		SERVICE_ALL_ACCESS);  // full access 

	if (schService == NULL)
	{
		MessageBox(L"�򿪷���ʧ��");
		//printf("OpenService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}

	// Check the status in case the service is not stopped. 
	//���״̬���Է�����û��ֹͣ��

	if (!QueryServiceStatusEx(
		schService,                     // handle to service 
		SC_STATUS_PROCESS_INFO,         // information level
		(LPBYTE)&ssStatus,             // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // size needed if buffer is too small
	{
		MessageBox(L"������״̬ʧ��!");
		//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}

	// Check if the service is already running. It would be possible 
	// to stop the service here, but for simplicity this example just returns. 
	//�������Ƿ��Ѿ����С�������ֹͣ�����ǿ��ܵ�,
	//����Ϊ�˼�������������ֻ�Ƿ��ء�
	if (ssStatus.dwCurrentState != SERVICE_STOPPED && ssStatus.dwCurrentState != SERVICE_STOP_PENDING)
	{
		MessageBox(L"�����Ѿ�������״̬!��������!");
		//printf("Cannot start the service because it is already running\n");
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}

	// Save the tick count and initial checkpoint.����δ�����ͳ�ʼ���㡣

	dwStartTickCount = GetTickCount();
	dwOldCheckPoint = ssStatus.dwCheckPoint;

	// Wait for the service to stop before attempting to start it.
	//�ڳ�������֮ǰ���ȴ�����ֹͣ��
	while (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
	{
		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth of the wait hint but not less than 1 second  
		// and not more than 10 seconds. 
		//��Ҫ�ȴ���ʱ�䳬���ȴ��İ�ʾ��һ���õļ���ǵȴ���ʾ��ʮ��֮һ��
		//��������1�룬Ҳ������10�롣
		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		// Check the status until the service is no longer stop pending. 
		//���״ֱ̬��������ֹͣ�ȴ�
		if (!QueryServiceStatusEx(
			schService,                     // handle to service 
			SC_STATUS_PROCESS_INFO,         // information level
			(LPBYTE)&ssStatus,             // address of structure
			sizeof(SERVICE_STATUS_PROCESS), // size of structure
			&dwBytesNeeded))              // size needed if buffer is too small
		{
			MessageBox(L"��ѯ����״̬ʧ��");
			//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			CloseServiceHandle(schService);
			CloseServiceHandle(schSCManager);
			return;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckPoint)
		{
			// Continue to wait and check.�����ȴ��ͼ��

			dwStartTickCount = GetTickCount();
			dwOldCheckPoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				MessageBox(L"�ȴ�����ֹͣ�ĳ�ʱ");
				//printf("Timeout waiting for service to stop\n");
				CloseServiceHandle(schService);
				CloseServiceHandle(schSCManager);
				return;
			}
		}
	}

	// Attempt to start the service.������������

	if (!StartService(
		schService,  // handle to service 
		0,           // number of arguments 
		NULL))      // no arguments 
	{
		MessageBox(L"��������ʧ��");
		//printf("StartService failed (%d)\n", GetLastError());
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}
	//else MessageBox(L"�ȴ���������");	//printf("Service start pending...\n");

	// Check the status until the service is no longer start pending. 
	//���״̬��ֱ�������ٿ�ʼ����
	if (!QueryServiceStatusEx(
		schService,                     // handle to service 
		SC_STATUS_PROCESS_INFO,         // info level
		(LPBYTE)&ssStatus,             // address of structure
		sizeof(SERVICE_STATUS_PROCESS), // size of structure
		&dwBytesNeeded))              // if buffer too small
	{
		MessageBox(L"��ѯ����״̬ʧ��");
		//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return;
	}

	// Save the tick count and initial checkpoint.
	//����δ�����ͳ�ʼ���㡣
	dwStartTickCount = GetTickCount();
	dwOldCheckPoint = ssStatus.dwCheckPoint;

	while (ssStatus.dwCurrentState == SERVICE_START_PENDING)
	{
		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth the wait hint, but no less than 1 second and no 
		// more than 10 seconds. 

		dwWaitTime = ssStatus.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		// Check the status again. 

		if (!QueryServiceStatusEx(
			schService,             // handle to service 
			SC_STATUS_PROCESS_INFO, // info level
			(LPBYTE)&ssStatus,             // address of structure
			sizeof(SERVICE_STATUS_PROCESS), // size of structure
			&dwBytesNeeded))              // if buffer too small
		{
			MessageBox(L"��ѯ����״̬ʧ��");
			//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			break;
		}

		if (ssStatus.dwCheckPoint > dwOldCheckPoint)
		{
			// Continue to wait and check.

			dwStartTickCount = GetTickCount();
			dwOldCheckPoint = ssStatus.dwCheckPoint;
		}
		else
		{
			if (GetTickCount() - dwStartTickCount > ssStatus.dwWaitHint)
			{
				// No progress made within the wait hint.
				//�ڵȴ���ʾ��û���κν�չ��
				break;
			}
		}
	}

	// Determine whether the service is running.ȷ�������Ƿ��������С�

	if (ssStatus.dwCurrentState == SERVICE_RUNNING)
	{
		//MessageBox(L"���������ɹ�");
		//printf("Service started successfully.\n");
		m_serveList.SetItemText(m_Index, 3, L"��������");
	}
	else
	{
		MessageBox(L"��������ʧ��");
		//printf("Service not started. \n");
		//printf("  Current State: %d\n", ssStatus.dwCurrentState);
		//printf("  Exit Code: %d\n", ssStatus.dwWin32ExitCode);
		//printf("  Check Point: %d\n", ssStatus.dwCheckPoint);
		//printf("  Wait Hint: %d\n", ssStatus.dwWaitHint);
	}

	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}

//�رշ���
VOID __stdcall CServeDialog::DoStopSvc(LPCTSTR szSvcName)
{
	SERVICE_STATUS_PROCESS ssp;
	DWORD dwStartTime = GetTickCount();
	DWORD dwBytesNeeded;
	DWORD dwTimeout = 30000; // 30-second time-out
	DWORD dwWaitTime;
	SC_HANDLE schSCManager = NULL;
	SC_HANDLE schService = NULL;
	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS);  // full access rights 

	if (NULL == schSCManager)
	{
		printf("OpenSCManager failed (%d)\n", GetLastError());
		return;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,         // SCM database 
		szSvcName,            // name of service 
		SERVICE_STOP |
		SERVICE_QUERY_STATUS |
		SERVICE_ENUMERATE_DEPENDENTS);

	if (schService == NULL)
	{
		MessageBox(L"�򿪷���ʧ��");
		//printf("OpenService failed (%d)\n", GetLastError());
		CloseServiceHandle(schSCManager);
		return;
	}

	// Make sure the service is not already stopped.

	if (!QueryServiceStatusEx(
		schService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&ssp,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded))
	{
		//MessageBox(L"QueryServiceStatusEx failed");
		//printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
		goto stop_cleanup;
	}

	if (ssp.dwCurrentState == SERVICE_STOPPED)
	{
		MessageBox(L"Service is already stopped");
		printf("Service is already stopped.\n");
		goto stop_cleanup;
	}

	// If a stop is pending, wait for it.

	while (ssp.dwCurrentState == SERVICE_STOP_PENDING)
	{
		printf("Service stop pending...\n");

		// Do not wait longer than the wait hint. A good interval is 
		// one-tenth of the wait hint but not less than 1 second  
		// and not more than 10 seconds. 

		dwWaitTime = ssp.dwWaitHint / 10;

		if (dwWaitTime < 1000)
			dwWaitTime = 1000;
		else if (dwWaitTime > 10000)
			dwWaitTime = 10000;

		Sleep(dwWaitTime);

		if (!QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{
			printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			goto stop_cleanup;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
		{
			printf("Service stopped successfully.\n");
			goto stop_cleanup;
		}

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			printf("Service stop timed out.\n");
			goto stop_cleanup;
		}
	}

	// If the service is running, dependencies must be stopped first.

	StopDependentServices(schService,schSCManager);

	// Send a stop code to the service.

	if (!ControlService(
		schService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&ssp))
	{
		MessageBox(L"ControlService failed");
		//printf("ControlService failed (%d)\n", GetLastError());
		goto stop_cleanup;
	}

	// Wait for the service to stop.

	while (ssp.dwCurrentState != SERVICE_STOPPED)
	{
		Sleep(ssp.dwWaitHint);
		if (!QueryServiceStatusEx(
			schService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&ssp,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded))
		{
			printf("QueryServiceStatusEx failed (%d)\n", GetLastError());
			goto stop_cleanup;
		}

		if (ssp.dwCurrentState == SERVICE_STOPPED)
			break;

		if (GetTickCount() - dwStartTime > dwTimeout)
		{
			printf("Wait timed out\n");
			goto stop_cleanup;
		}
	}
	m_serveList.SetItemText(m_Index, 3, L"��ֹͣ");
	//printf("Service stopped successfully\n");

stop_cleanup:
	CloseServiceHandle(schService);
	CloseServiceHandle(schSCManager);
}

BOOL __stdcall CServeDialog::StopDependentServices(SC_HANDLE schService, SC_HANDLE schSCManager)
{
	DWORD i;
	DWORD dwBytesNeeded;
	DWORD dwCount;

	LPENUM_SERVICE_STATUS   lpDependencies = NULL;
	ENUM_SERVICE_STATUS     ess;
	SC_HANDLE               hDepService;
	SERVICE_STATUS_PROCESS  ssp;

	DWORD dwStartTime = GetTickCount();
	DWORD dwTimeout = 30000; // 30-second time-out

							 // Pass a zero-length buffer to get the required buffer size.
	if (EnumDependentServices(schService, SERVICE_ACTIVE,
		lpDependencies, 0, &dwBytesNeeded, &dwCount))
	{
		// If the Enum call succeeds, then there are no dependent
		// services, so do nothing.
		return TRUE;
	}
	else
	{
		if (GetLastError() != ERROR_MORE_DATA)
			return FALSE; // Unexpected error

						  // Allocate a buffer for the dependencies.
		lpDependencies = (LPENUM_SERVICE_STATUS)HeapAlloc(
			GetProcessHeap(), HEAP_ZERO_MEMORY, dwBytesNeeded);

		if (!lpDependencies)
			return FALSE;

		__try {
			// Enumerate the dependencies.
			if (!EnumDependentServices(schService, SERVICE_ACTIVE,
				lpDependencies, dwBytesNeeded, &dwBytesNeeded,
				&dwCount))
				return FALSE;

			for (i = 0; i < dwCount; i++)
			{
				ess = *(lpDependencies + i);
				// Open the service.
				hDepService = OpenService(schSCManager,
					ess.lpServiceName,
					SERVICE_STOP | SERVICE_QUERY_STATUS);

				if (!hDepService)
					return FALSE;

				__try {
					// Send a stop code.
					if (!ControlService(hDepService,
						SERVICE_CONTROL_STOP,
						(LPSERVICE_STATUS)&ssp))
						return FALSE;

					// Wait for the service to stop.
					while (ssp.dwCurrentState != SERVICE_STOPPED)
					{
						Sleep(ssp.dwWaitHint);
						if (!QueryServiceStatusEx(
							hDepService,
							SC_STATUS_PROCESS_INFO,
							(LPBYTE)&ssp,
							sizeof(SERVICE_STATUS_PROCESS),
							&dwBytesNeeded))
							return FALSE;

						if (ssp.dwCurrentState == SERVICE_STOPPED)
							break;

						if (GetTickCount() - dwStartTime > dwTimeout)
							return FALSE;
					}
				}
				__finally
				{
					// Always release the service handle.
					CloseServiceHandle(hDepService);
				}
			}
		}
		__finally
		{
			// Always free the enumeration buffer.
			HeapFree(GetProcessHeap(), 0, lpDependencies);
		}
	}
	return TRUE;
}

void CServeDialog::OnStart()
{
	// TODO: �ڴ���������������
	DoStartSvc(m_ServiceName[m_Index]);
}


void CServeDialog::OnClose()
{
	// TODO: �ڴ���������������
	DoStopSvc(m_ServiceName[m_Index]);
}
