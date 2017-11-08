#pragma once
#include "afxcmn.h"


// CPEResourceDialog �Ի���

class CPEResourceDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPEResourceDialog)

public:
	CPEResourceDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPEResourceDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4_RESOURCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_ResourceTree;
	DWORD m_dwResRootRva;//��Դ��Ŀ¼RVA
	IMAGE_RESOURCE_DIRECTORY* m_pResRoot;//��ԴĿ¼

	void parseResourcesTable(DWORD dwResRootDirAddr,/*��Ŀ¼���׵�ַ*/
		IMAGE_RESOURCE_DIRECTORY* pResDir,/*��Ҫ��������ԴĿ¼*/
		int nDeep /*��¼���ǵڼ���Ŀ¼*/
		);

	IMAGE_DOS_HEADER* m_pDosHdr;

	HTREEITEM hTree1 = NULL;
	HTREEITEM hTree2 = NULL;
	virtual BOOL OnInitDialog();
};
