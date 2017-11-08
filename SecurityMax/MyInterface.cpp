// MyInterface.cpp : 实现文件
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



// CMyInterface 消息处理程序




void CMyInterface::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	GetClientRect(rect);				//获取客户区大小
	rect.DeflateRect(0, 22, 0,0);		//去掉客户区选项卡标题栏部分
	DWORD dwSel = this->GetCurSel();	//获取当前选中的选项卡
	for (DWORD i = 0; i < m_dwCount; i++)
	{
		if (dwSel == i)
		{
			m_pDlg[i]->ShowWindow(SW_SHOW);			//只显示选中的
			m_pDlg[i]->MoveWindow(rect);			//将对话框移动到客户区范围内
		}
		else
		{
			m_pDlg[i]->ShowWindow(SW_HIDE);			//其他部分设置为隐藏
		}
	}
	*pResult = 0;
}

//插入选项卡
void CMyInterface::InsertTab(DWORD dwCount, ...)
{
	//定义一个变参变量
	va_list va;
	//告诉变参变量第一个变参的起始位置
	//把第一个变参地址给va
	va_start(va, dwCount);
	for (DWORD i = 0; i < dwCount; i++)
	{
		TCHAR* pSrtTabName = va_arg(va, TCHAR*);		//获取参数
		InsertItem(i, pSrtTabName);						//插入现有
	}
	va_end(va);		//结束获取参数
	m_dwCount = dwCount;
}

//增加对话框
void CMyInterface::AddDlg(DWORD dwCount, ...)
{
	va_list va;
	va_start(va, dwCount);	//初始化
	for (DWORD i = 0; i < dwCount; i++)
	{
		m_pDlg[i] = va_arg(va, CDialogEx*);
		UINT uId = va_arg(va, UINT);		//获取参数
		m_pDlg[i]->Create(uId, this);
	}
	va_end(va);		//结束获取参数

					// 默认显示第1个对话框
	SetSelAndShow(NULL);
}

//设置当前选中的对话框并显示
void CMyInterface::SetSelAndShow(int nSel)
{
	//默认显示第一个
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

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(rect);				//获取客户区大小
	rect.DeflateRect(1, 22, 3, 3);		//去掉客户区选项卡标题栏部分
	DWORD dwSel = this->GetCurSel();	//获取当前选中的选项卡
	for (DWORD i = 0; i < m_dwCount; i++)
	{
		if (dwSel == i)
		{
			m_pDlg[i]->ShowWindow(SW_SHOW);			//只显示选中的
			m_pDlg[i]->MoveWindow(rect);			//将对话框移动到客户区范围内
		}
		else
		{
			m_pDlg[i]->ShowWindow(SW_HIDE);			//其他部分设置为隐藏
		}
	}

}



