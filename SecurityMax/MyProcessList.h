#pragma once
#include <vector>
using namespace std;

// CMyProcessList

class CMyProcessList : public CListCtrl
{
	DECLARE_DYNAMIC(CMyProcessList)

public:
	CMyProcessList();
	virtual ~CMyProcessList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	vector<DWORD>m_processID;
	int m_Index;
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnModule();
	afx_msg void OnThread();
};


