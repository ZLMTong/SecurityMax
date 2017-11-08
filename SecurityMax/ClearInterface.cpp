// ClearInterface.cpp : ʵ���ļ�
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

// CClearInterface �Ի���

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

	// ����������Ҫɾ���ļ���ӵ�ListBox����ʾ����
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

//��ȡ�ļ��б�
bool CClearInterface::getFilePath(const TCHAR* pszDir, int nDeep /*= 5*/)
{
	if (nDeep == 0)
		return false;

	wstring dir;
	// 1. �ϳ�һ������ͨ�����·��,������Ҳ����ļ�.
	dir = pszDir + wstring(L"\\*");

	// �����ļ�: 
	// 2. ���ҵ�һ���ļ�.
	WIN32_FIND_DATA fData;
	HANDLE hFindHandle;
	hFindHandle = FindFirstFile(dir.c_str(), &fData);

	// 2.1 �ж���û�в��ҵ�.
	if (hFindHandle == INVALID_HANDLE_VALUE)
		return false;

	// 3. ���Һ������ļ�.
	do
	{
		// ���˵���ǰĿ¼���ϲ�Ŀ¼
		if (_tcscmp(fData.cFileName, L".") == 0
			|| _tcscmp(fData.cFileName, L"..") == 0)
		{
			continue;
		}

		// ����ļ���
		wstring path = pszDir + wstring(L"\\") + fData.cFileName;

		// �ж��ļ��Ƿ���Ŀ¼
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

	// 4. �رղ��Ҿ��
	FindClose(hFindHandle);
	return true;
}

BEGIN_MESSAGE_MAP(CClearInterface, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CClearInterface::OnScanFileBtn)
	ON_BN_CLICKED(IDC_BUTTON3, &CClearInterface::OnScanFileBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CClearInterface::OnBnClickedStartClear)
END_MESSAGE_MAP()

// CClearInterface ��Ϣ�������

void CClearInterface::OnScanFileBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����֮ǰ�����֮ǰ�������ļ���Ϣ���б������
	UpdateData(TRUE);
	if (!m_btnVS.GetCheck() && !m_btnBrowser.GetCheck() && !m_btnSystem.GetCheck() &&  m_editSuffix.IsEmpty())
	{ 
		MessageBox(L"����д��׺,��ѡ����ѡ��");
		return;
	}
	
	CreateThread(NULL, NULL, ThreadScanFile, this, NULL, NULL);
	
}

void CClearInterface::clearTrash()
{
	//��ʼ��SHQUERYRBINFO�ṹ��
	SHQUERYRBINFO RecycleBinInfo = {};
	RecycleBinInfo.cbSize = sizeof(RecycleBinInfo);

	//��ѯ����վ��Ϣ
	SHQueryRecycleBin(m_strTrashPath, &RecycleBinInfo);

	//��ջ���վ
	SHEmptyRecycleBin(NULL, NULL, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}

void CClearInterface::OnBnClickedStartClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	if (m_btnTrash.GetCheck())
// 	{
// 		clearTrash();
// 	}

// 	for (int i = 0; m_vecClearFile.size(); i++)
// 	{
// 		DeleteFile(m_vecClearFile[i].GetBuffer());
// 	}
	

}

