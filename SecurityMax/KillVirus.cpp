// KillVirus.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "KillVirus.h"
#include "afxdialogex.h"
#include <windows.h>
#include <TlHelp32.h>
#include "Message.h"



// CKillVirus 对话框

IMPLEMENT_DYNAMIC(CKillVirus, CDialogEx)

CKillVirus::CKillVirus(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG7_VIRUS, pParent)
{

}

CKillVirus::~CKillVirus()
{
}

void CKillVirus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_VirusList);
	DDX_Control(pDX, IDC_BUTTON1, m_btnMd5);
	DDX_Control(pDX, IDC_BUTTON16, m_btnAllPathKill);
	DDX_Control(pDX, IDC_BUTTON17, m_btnWhiteName);
}

DWORD WINAPI ThreadMD5(LPVOID lpThreadMD5)
{
	CKillVirus* pThis = (CKillVirus*)lpThreadMD5;

	pThis->m_veMd5File.clear();
	pThis->m_veMd5Data.clear();
	pThis->m_VirusList.ResetContent();

	pThis->getFilePath(L"D:\\新建文件夹", 3);
	char md5[33] = {};
	strcpy(md5, md5FileValue("D:\\新建文件夹\\123.txt"));
	CString md55;
	md55.Format(L"%S", md5);
	pThis->m_veMd5Data.push_back(md55);
	
	for (int i = 0; i < (int)pThis->m_vctUpdataMd5Data.size(); ++i)
	{
		for (int j = 0; j < (int)pThis->m_veMd5Data.size(); ++j)
		{
			if (pThis->m_veMd5Data[j] == pThis->m_vctUpdataMd5Data[i])
			{
				continue;
			}
			pThis->m_veMd5Data.push_back(pThis->m_vctUpdataMd5Data[i]);
			break;
		}
	}

	int nCont1 = 0;
	int nCont2 = 0;
	for (nCont1 = 0; nCont1 <pThis->m_veMd5Data.size(); nCont1++)
	{
		char cMd5Data[100] = {};
		WCHAR_TO_CHAR(pThis->m_veMd5Data[nCont1], cMd5Data);
		for (nCont2 = 0; nCont2 <pThis->m_veMd5File.size(); nCont2++)
		{
			char cMd5File[100] = {};
			WCHAR_TO_CHAR(pThis->m_veMd5File[nCont2], cMd5File);
			CHAR* md5Values = md5FileValue(cMd5File);

			if (strcmp(cMd5Data, md5Values) == 0)
			{
				//DeleteFile(m_veMd5File[nCont2].GetBuffer());

				pThis->m_VirusList.AddString(pThis->m_veMd5File[nCont2]);

			}
		}
		nCont2 = 0;
	}
	if (pThis->m_VirusList.GetCount()==0)
	{
		pThis->m_VirusList.AddString(L"没有找到病毒");
	}

	pThis->m_isClickVirus = false;
	pThis->m_btnAllPathKill.EnableWindow(TRUE);
	pThis->m_btnWhiteName.EnableWindow(TRUE);
	return 0;

}

DWORD WINAPI ThreadMD5AndPath(LPVOID lpThreadMD5AndPath)
{
	CKillVirus* pThis = (CKillVirus*)lpThreadMD5AndPath;

	
	pThis->m_VirusList.ResetContent();

	pThis->m_veMd5File.clear();
	pThis->getFilePath(L"D:", 2);

	if (pThis->m_vePathAndMd5.empty())
	{
		pThis->MessageBox(L"没有找到病毒");
		return 0;
	}

	
	int nCont1 = 0;
	int nCont2 = 0;
	for (nCont1 = 0; nCont1 < pThis->m_veMd5File.size(); nCont1++)
	{
		char cMd5File[100] = {};
		WCHAR_TO_CHAR(pThis->m_veMd5File[nCont1], cMd5File);
		CHAR* md5Values = md5FileValue(cMd5File);

		for (nCont2 = 0; nCont2 < pThis->m_vePathAndMd5.size(); nCont2++)
		{
			if (strcmp(pThis->m_vePathAndMd5[nCont2].cMd5Value, md5Values) == 0
				&& 
				pThis->m_vePathAndMd5[nCont2].cFilePath== pThis->m_veMd5File[nCont1])
			{
				//DeleteFile(m_veMd5File[nCont2].GetBuffer());

				pThis->m_VirusList.AddString(pThis->m_veMd5File[nCont1]);

			}

		}
		nCont2 = 0;
	}
	if (pThis->m_VirusList.GetCount() == 0)
	{
		pThis->m_VirusList.AddString(L"没有找到病毒");
	}
	pThis->m_isClickVirus = false;
	pThis->m_btnMd5.EnableWindow(TRUE);
	pThis->m_btnWhiteName.EnableWindow(TRUE);
	return 0;
}

DWORD WINAPI ThreadWhiteList(LPVOID lpThreadProcess)
{
	CKillVirus* pThis = (CKillVirus*)lpThreadProcess;

	pThis->m_VirusList.ResetContent();

	HANDLE hProcessHnd;			//快照句柄
	HANDLE hProcess;			//进程句柄
	PROCESSENTRY32 Pe32;		//进程快照信息
	Pe32.dwSize = sizeof(PROCESSENTRY32);

	//1.创建一个进程相关的快照句柄
	hProcessHnd = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessHnd == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	//2.通过进程快照句柄获取第一个进程信息
	if (!Process32First(hProcessHnd, &Pe32))
	{
		CloseHandle(hProcessHnd);
		return 0;
	}

	CString strProc;
	//3.获取进程名称
	do
	{
		strProc.Format(L"%s", Pe32.szExeFile);
		for (int nCont1 = 0; nCont1 < pThis->m_vePreocess.size(); nCont1++)
		{
			if (pThis->m_vePreocess[nCont1] == strProc)
			{
				pThis->m_VirusList.AddString(strProc);
			}
		}
	} while (Process32Next(hProcessHnd, &Pe32));
	
	if (pThis->m_VirusList.GetCount() == 0)
	{
		pThis->m_VirusList.AddString(L"没有找到病毒");
	}
	pThis->m_isClickVirus = false;
	pThis->m_btnMd5.EnableWindow(TRUE);
	pThis->m_btnAllPathKill.EnableWindow(TRUE);
	//关闭句柄退出函数
	CloseHandle(hProcessHnd);
}

bool CKillVirus::getFilePath(const TCHAR* pszDir, int nDeep /*= 5*/)
{
	if (nDeep == 0)
		return false;

	wstring dir;
	// 1. 合成一个带有通配符的路径,否则查找不到文件.
	dir = pszDir + wstring(L"\\*");

	// 遍历文件: 
	// 2. 查找第一个文件.
	WIN32_FIND_DATA fData;
	HANDLE hFindHandle;
	hFindHandle = FindFirstFile(dir.c_str(), &fData);

	// 2.1 判断有没有查找到.
	if (hFindHandle == INVALID_HANDLE_VALUE)
		return false;

	// 3. 查找后续的文件.
	do
	{
		// 过滤掉当前目录和上层目录
		if (_tcscmp(fData.cFileName, L".") == 0
			|| _tcscmp(fData.cFileName, L"..") == 0)
		{
			continue;
		}
		// 输出文件名
		wstring path = pszDir + wstring(L"\\") + fData.cFileName;

		// 判断文件是否是目录
		if (FILE_ATTRIBUTE_DIRECTORY & fData.dwFileAttributes)
		{
			getFilePath(path.c_str(), nDeep - 1);
		}
		else
		{
			m_veMd5File.push_back(path.c_str());
		}

	} while (FindNextFile(hFindHandle, &fData));

	// 4. 关闭查找句柄
	FindClose(hFindHandle);
	return true;
}

BEGIN_MESSAGE_MAP(CKillVirus, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CKillVirus::OnStartVirus)
	ON_BN_CLICKED(IDC_BUTTON16, &CKillVirus::OnFullPathKill)
	ON_BN_CLICKED(IDC_BUTTON17, &CKillVirus::OnWhiteList)
ON_BN_CLICKED(IDC_BUTTON15, &CKillVirus::OnYun)
END_MESSAGE_MAP()


// CKillVirus 消息处理程序
DWORD WINAPI  threadUpdataVirus(_In_ LPVOID lpParameter)
{
	CKillVirus* pThis = (CKillVirus*)lpParameter;
	MESSAGE message = {};
	CString str;
	pThis->m_vctUpdataMd5Data.clear();
	while (true)
	{
		recv(pThis->m_socketClient, (CHAR*)&message, sizeof(message), 0);
		if (message.type == over)
		{
			break;
		}
		str.Format(L"%S", message.info.buf);
		pThis->m_vctUpdataMd5Data.push_back(str);
	}
	//pThis->MessageBox(L"更新成功");
	return 0;
}



void CKillVirus::OnStartVirus()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_isClickVirus)
	{
		MessageBox(L"正在杀毒");
		return;
	}
	m_isClickVirus = true;
	m_btnAllPathKill.EnableWindow(FALSE);
	m_btnWhiteName.EnableWindow(FALSE);
	CreateThread(NULL, NULL, ThreadMD5, this, NULL, NULL);
	
}


void CKillVirus::OnFullPathKill()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_isClickVirus)
	{
		MessageBox(L"正在杀毒");
		return;
	}
	m_isClickVirus = true;
	
	m_btnMd5.EnableWindow(FALSE);
	m_btnWhiteName.EnableWindow(FALSE);

	PathAndMd5 file;
	file.cMd5Value = "d6c1c3161a648d9800104e486605aa63";
	file.cFilePath = "D:\\新建文件夹\\123.txt";
	m_vePathAndMd5.push_back(file);

	CreateThread(NULL, NULL, ThreadMD5AndPath, this, NULL, NULL);
}


void CKillVirus::OnWhiteList()
{
	// TODO: 在此添加控件通知处理程序代码
	
	if (m_isClickVirus)
	{
		MessageBox(L"正在杀毒");
		return;
	}
	m_isClickVirus = true;
	m_btnMd5.EnableWindow(FALSE);
	m_btnAllPathKill.EnableWindow(FALSE);
	m_vePreocess.clear();
	CString cProcess = L"System";
	m_vePreocess.push_back(cProcess);
	CreateThread(NULL, NULL, ThreadWhiteList, this, NULL, NULL);
}


bool CKillVirus::linkServer()
{
	//检测信号
	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	WORD wSig = MAKEWORD(2, 2);
	WSADATA wsData;
	int err = WSAStartup(wSig, &wsData);
	if (err)
	{
		MessageBox(L"链接失败,请检查");
		return false;
	}

	if (LOBYTE(wsData.wVersion) != 2 || HIBYTE(wsData.wVersion) != 2) 
	{
		WSACleanup();
		MessageBox(L"链接失败,请检查");
		return false;
	}

	//创建socket
	m_socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socketClient == INVALID_SOCKET)
	{
		WSACleanup();
		MessageBox(L"链接失败,请检查");
		return false;
	}

	//绑定socket
	SOCKADDR_IN serverAddr = {};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons((short)(12345));
	int nRet = connect(m_socketClient, (sockaddr*)&serverAddr, sizeof(SOCKADDR_IN));
	//是否绑定成功
	if (nRet == SOCKET_ERROR)
	{
		closesocket(m_socketClient);
		WSACleanup();
		MessageBox(L"链接失败,请检查");
		return false;
	}
	return true;
}


void CKillVirus::OnYun()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!linkServer())
	{
		return ;
	}
	MESSAGE message = {};
	message.type = query;
	send(m_socketClient, (CHAR*)&message, sizeof(MESSAGE), 0);
	CreateThread(NULL, NULL, threadUpdataVirus, this, NULL, NULL);
}
