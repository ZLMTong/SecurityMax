
// SecurityMax.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSecurityMaxApp: 
// �йش����ʵ�֣������ SecurityMax.cpp
//

class CSecurityMaxApp : public CWinApp
{
public:
	CSecurityMaxApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSecurityMaxApp theApp;