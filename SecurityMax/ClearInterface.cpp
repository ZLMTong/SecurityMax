// ClearInterface.cpp : 实现文件
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "ClearInterface.h"
#include "afxdialogex.h"
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")
#include <string>
#include <afxwin.h>
using namespace std;

// CClearInterface 对话框

DWORD WINAPI ThreadScanFile(LPVOID lpThreadClear)
{

	CClearInterface* pThis = (CClearInterface*)lpThreadClear;
	pThis->m_vecClearFile.clear();
	pThis->m_listBoxFolder.ResetContent();

	if (pThis->m_btnVS.GetCheck())
	{
		pThis->getFilePath(pThis->m_strVSPath);
	}

	if (pThis->m_btnBrowser.GetCheck())
	{
		pThis->getFilePath(pThis->m_strBrowserPath);
	}

	if (pThis->m_btnSystem.GetCheck())
	{
		pThis->getFilePath(pThis->m_strSystemPath,5);
	}
	if (!pThis->m_editSuffix.IsEmpty())
	{
		pThis->getFilePath(L"G:");
	}

	// 将遍历到的要删除文件添加到ListBox内显示出来
	for (DWORD i = 0; i < pThis->m_vecClearFile.size(); i++)
	{
		pThis->m_listBoxFolder.AddString(pThis->m_vecClearFile[i]);

	}
	return 0;
}

IMPLEMENT_DYNAMIC(CClearInterface, CDialogEx)

CClearInterface::CClearInterface(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5_CLEAR, pParent)
	, m_editSuffix(_T(""))
{

}

CClearInterface::~CClearInterface()
{
}

void CClearInterface::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_btnVS);
	DDX_Text(pDX, IDC_EDIT1, m_editSuffix);
	DDX_Control(pDX, IDC_LIST1, m_listBoxFolder);
	DDX_Control(pDX, IDC_CHECK3, m_btnSystem);
	DDX_Control(pDX, IDC_CHECK2, m_btnBrowser);
	DDX_Control(pDX, IDC_CHECK4, m_btnTrash);
}

//获取文件列表
bool CClearInterface::getFilePath(const TCHAR* pszDir, int nDeep /*= 5*/)
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
		if (FILE_ATTRIBUTE_DIRECTORY&fData.dwFileAttributes)
		{
			getFilePath(path.c_str(), nDeep - 1);
		}
		else
		{
			PTSTR pExtension = PathFindExtension(path.c_str());

			if (m_btnVS.GetCheck())
			{
				if (-1 != m_strVSPosfix.Find(pExtension))
				{
					m_vecClearFile.push_back(path.c_str());
				}
			}
			else
			{
				if (!m_editSuffix.IsEmpty())
				{
					if (-1 != m_editSuffix.Find(pExtension))
					{
						m_vecClearFile.push_back(path.c_str());
					}
				}

				if (m_btnBrowser.GetCheck()|| m_btnSystem.GetCheck())
				{
					m_vecClearFile.push_back(path.c_str());
				}
			}
		}

	} while (FindNextFile(hFindHandle, &fData));

	// 4. 关闭查找句柄
	FindClose(hFindHandle);
	return true;
}

BEGIN_MESSAGE_MAP(CClearInterface, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CClearInterface::OnScanFileBtn)
	ON_BN_CLICKED(IDC_BUTTON3, &CClearInterface::OnScanFileBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CClearInterface::OnBnClickedStartClear)
END_MESSAGE_MAP()

// CClearInterface 消息处理程序

void CClearInterface::OnScanFileBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	// 遍历之前先清空之前遍历的文件信息和列表框内容
	UpdateData(TRUE);
	if (!m_btnVS.GetCheck() && !m_btnBrowser.GetCheck() && !m_btnSystem.GetCheck() &&  m_editSuffix.IsEmpty())
	{ 
		MessageBox(L"请填写后缀,或勾选清理选项");
		return;
	}
	
	CreateThread(NULL, NULL, ThreadScanFile, this, NULL, NULL);
	
}

void CClearInterface::clearTrash()
{
	//初始化SHQUERYRBINFO结构体
	SHQUERYRBINFO RecycleBinInfo = {};
	RecycleBinInfo.cbSize = sizeof(RecycleBinInfo);

	//查询回收站信息
	SHQueryRecycleBin(m_strTrashPath, &RecycleBinInfo);

	//清空回收站
	SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}

void CClearInterface::OnBnClickedStartClear()
{
	// TODO: 在此添加控件通知处理程序代码
// 	if (m_btnTrash.GetCheck())
// 	{
// 		clearTrash();
// 	}

// 	for (int i = 0; m_vecClearFile.size(); i++)
// 	{
// 		DeleteFile(m_vecClearFile[i].GetBuffer());
// 	}
	

}

