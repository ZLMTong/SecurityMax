#pragma once
#include <windows.h>

#define NAMELENGTH 50
#define MESSAGEBUF 1024
enum MESSAGETYPE
{
	query=1,		//查询消息
	over			//发送完毕
	
};

typedef struct _MESSAGE
{
	MESSAGETYPE type;	// 消息类型
	DWORD		len;	// 消息长度
	union
	{
		CHAR	buf[MESSAGEBUF];// 平时发送消息用这个
	}info;
}MESSAGE;