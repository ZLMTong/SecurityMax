#pragma once
#include "afxcmn.h"


typedef struct TypeOffset {
	WORD Offset : 12;  // (1) ��СΪ12Bit���ض�λƫ��
	WORD Type : 4;    // (2) ��СΪ4Bit���ض�λ��Ϣ����ֵ
}TypeOffset;	    // ����ṹ����A1Pass�ܽ��


// CPERelocationDialog �Ի���

class CPERelocationDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPERelocationDialog)

public:
	CPERelocationDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPERelocationDialog();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4_RELOCATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	IMAGE_OPTIONAL_HEADER* m_pOptHdr;
	IMAGE_DOS_HEADER* m_pDosHDr;
	void getRelocationInfo();
	virtual BOOL OnInitDialog();
	CListCtrl m_ListA;
	CListCtrl m_ListB;
};
