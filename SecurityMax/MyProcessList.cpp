// MyProcessList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyProcessList.h"
#include "MyModuleDialog.h"
#include "MyThreadDialog.h"


// CMyProcessList

IMPLEMENT_DYNAMIC(CMyProcessList, CListCtrl)

CMyProcessList::CMyProcessList()
{

}

CMyProcessList::~CMyProcessList()
{
}


BEGIN_MESSAGE_MAP(CMyProcessList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CMyProcessList::OnNMRClick)
	ON_COMMAND(ID_MODULE, &CMyProcessList::OnModule)
	ON_COMMAND(ID_THREAD, &CMyProcessList::OnThread)
END_MESSAGE_MAP()



// CMyProcessList ��Ϣ�������




void CMyProcessList::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_Index = pNMItemActivate->iItem;

	CMenu mu;
	mu.LoadMenuW(IDR_MENU1);
	CMenu *pmuSub = mu.GetSubMenu(0);

	CPoint pt;
	GetCursorPos(&pt);
	TrackPopupMenu(pmuSub->m_hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, m_hWnd, 0);

	*pResult = 0;
}


void CMyProcessList::OnModule()
{
	// TODO: �ڴ���������������
	CMyModuleDialog module(m_processID[m_Index]);
	module.DoModal();
}


void CMyProcessList::OnThread()
{
	// TODO: �ڴ���������������
	CMyThreadDialog Thread(m_processID[m_Index]);
	Thread.DoModal();
}
