#pragma once
#include "afxcmn.h"


typedef struct TypeOffset {
	WORD Offset : 12;  // (1) 大小为12Bit的重定位偏移
	WORD Type : 4;    // (2) 大小为4Bit的重定位信息类型值
}TypeOffset;	    // 这个结构体是A1Pass总结的


// CPERelocationDialog 对话框

class CPERelocationDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPERelocationDialog)

public:
	CPERelocationDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPERelocationDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4_RELOCATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	IMAGE_OPTIONAL_HEADER* m_pOptHdr;
	IMAGE_DOS_HEADER* m_pDosHDr;
	void getRelocationInfo();
	virtual BOOL OnInitDialog();
	CListCtrl m_ListA;
	CListCtrl m_ListB;
};
