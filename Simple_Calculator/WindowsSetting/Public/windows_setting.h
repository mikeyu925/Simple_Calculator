#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "../../BaseDefine/baseDefine.h"
typedef enum consoleColor {
	SIMPLE_BLACK = 0,           //��ɫ
	SIMPLE_BLUE,				//��ɫ
	SIMPLE_GREEN,				//��ɫ
	SIMPLE_LIGHE_BLUE,			//ǳ��ɫ
	SIMPLE_RED,					//��ɫ
	SIMPLE_VIOLET,				//��ɫ
	SIMPLE_YELLOW,				//��ɫ
	SIMPLE_WHITE,				//��ɫ
	SIMPLE_GREY,				//��ɫ
	SIMPLE_PALE_BLUE,			//����ɫ
	SIMPLE_PALE_GREEN,			//����ɫ
	SIMPLE_LIGHE_PALE_GREEN,	//��ǳ��ɫ
	SIMPLE_PALE_RED,			//����ɫ
	SIMPLE_PALE_VIOLET,			//����ɫ
	SIMPLE_PALE_YELLOW,			//����ɫ
	SIMPLE_BRIGHT_WHITE			//����ɫ
}console_w_color;

typedef enum
{
	SUCCESS,    //�ɹ�
	WARNING,    //����
	ERR,		//����
	INFO		//��ͨ��Ϣ
}showType;
void printPreInfo(void);
char* getCurrentTime(void);
void setConsoleColor(console_w_color pen_color, console_w_color background_color);
void printInfo(showType type, const char* formar, ...);

int get_printf(char* buf, char* format, ...);
#define printSuccessInfo(...) printInfo(SUCCESS,__VA_ARGS__)
#define printWarningInfo(...) printInfo(WARNING,__VA_ARGS__)
#define printErrorInfo(...) printInfo(ERR,__VA_ARGS__)
#define printNormalInfo(...) printInfo(INFO,__VA_ARGS__)