#pragma once
#include "afxcmn.h"


// PESectorDialog �Ի���

class PESectorDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PESectorDialog)

public:
	PESectorDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~PESectorDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {IDD = IDD_DIALOG4_SECTION};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRect rc;
	CListCtrl m_SectionList;
	IMAGE_SECTION_HEADER* m_pScnHdr;//��չͷ
	IMAGE_FILE_HEADER* m_pFileHdr;//�ļ�ͷ
	virtual BOOL OnInitDialog();
	void getSectorTableInfo();
};
