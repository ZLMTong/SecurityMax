// MyInterface.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityMax.h"
#include "MyInterface.h"


// CMyInterface

IMPLEMENT_DYNAMIC(CMyInterface, CTabCtrl)

CMyInterface::CMyInterface()
{

}

CMyInterface::~CMyInterface()
{
}


BEGIN_MESSAGE_MAP(CMyInterface, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyInterface::OnTcnSelchange)
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CMyInterface ��Ϣ�������




void CMyInterface::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect rect;
	GetClientRect(rect);				//��ȡ�ͻ�����С
	rect.DeflateRect(0, 22, 0,0);		//ȥ���ͻ���ѡ�����������
	DWORD dwSel = this->GetCurSel();	//��ȡ��ǰѡ�е�ѡ�
	for (DWORD i = 0; i < m_dwCount; i++)
	{
		if (dwSel == i)
		{
			m_pDlg[i]->ShowWindow(SW_SHOW);			//ֻ��ʾѡ�е�
			m_pDlg[i]->MoveWindow(rect);			//���Ի����ƶ����ͻ�����Χ��
		}
		else
		{
			m_pDlg[i]->ShowWindow(SW_HIDE);			//������������Ϊ����
		}
	}
	*pResult = 0;
}

//����ѡ�
void CMyInterface::InsertTab(DWORD dwCount, ...)
{
	//����һ����α���
	va_list va;
	//���߱�α�����һ����ε���ʼλ��
	//�ѵ�һ����ε�ַ��va
	va_start(va, dwCount);
	for (DWORD i = 0; i < dwCount; i++)
	{
		TCHAR* pSrtTabName = va_arg(va, TCHAR*);		//��ȡ����
		InsertItem(i, pSrtTabName);						//��������
	}
	va_end(va);		//������ȡ����
	m_dwCount = dwCount;
}

//���ӶԻ���
void CMyInterface::AddDlg(DWORD dwCount, ...)
{
	va_list va;
	va_start(va, dwCount);	//��ʼ��
	for (DWORD i = 0; i < dwCount; i++)
	{
		m_pDlg[i] = va_arg(va, CDialogEx*);
		UINT uId = va_arg(va, UINT);		//��ȡ����
		m_pDlg[i]->Create(uId, this);
	}
	va_end(va);		//������ȡ����

					// Ĭ����ʾ��1���Ի���
	SetSelAndShow(NULL);
}

//���õ�ǰѡ�еĶԻ�����ʾ
void CMyInterface::SetSelAndShow(int nSel)
{
	//Ĭ����ʾ��һ��
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(1, 23, 3, 3);
	this->SetCurSel(nSel);
	m_pDlg[nSel]->ShowWindow(SW_SHOW);
	m_pDlg[nSel]->MoveWindow(rect);
}


void CMyInterface::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(rect);				//��ȡ�ͻ�����С
	rect.DeflateRect(1, 22, 3, 3);		//ȥ���ͻ���ѡ�����������
	DWORD dwSel = this->GetCurSel();	//��ȡ��ǰѡ�е�ѡ�
	for (DWORD i = 0; i < m_dwCount; i++)
	{
		if (dwSel == i)
		{
			m_pDlg[i]->ShowWindow(SW_SHOW);			//ֻ��ʾѡ�е�
			m_pDlg[i]->MoveWindow(rect);			//���Ի����ƶ����ͻ�����Χ��
		}
		else
		{
			m_pDlg[i]->ShowWindow(SW_HIDE);			//������������Ϊ����
		}
	}

}



