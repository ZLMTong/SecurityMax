#pragma once
#include <windows.h>

#define NAMELENGTH 50
#define MESSAGEBUF 1024
enum MESSAGETYPE
{
	query=1,		//��ѯ��Ϣ
	over			//�������
	
};

typedef struct _MESSAGE
{
	MESSAGETYPE type;	// ��Ϣ����
	DWORD		len;	// ��Ϣ����
	union
	{
		CHAR	buf[MESSAGEBUF];// ƽʱ������Ϣ�����
	}info;
}MESSAGE;