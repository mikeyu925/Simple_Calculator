#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "../../BaseDefine/baseDefine.h"
typedef enum consoleColor {
	SIMPLE_BLACK = 0,           //黑色
	SIMPLE_BLUE,				//蓝色
	SIMPLE_GREEN,				//绿色
	SIMPLE_LIGHE_BLUE,			//浅蓝色
	SIMPLE_RED,					//红色
	SIMPLE_VIOLET,				//紫色
	SIMPLE_YELLOW,				//黄色
	SIMPLE_WHITE,				//白色
	SIMPLE_GREY,				//灰色
	SIMPLE_PALE_BLUE,			//淡蓝色
	SIMPLE_PALE_GREEN,			//淡绿色
	SIMPLE_LIGHE_PALE_GREEN,	//淡浅绿色
	SIMPLE_PALE_RED,			//淡红色
	SIMPLE_PALE_VIOLET,			//淡紫色
	SIMPLE_PALE_YELLOW,			//淡黄色
	SIMPLE_BRIGHT_WHITE			//亮白色
}console_w_color;

typedef enum
{
	SUCCESS,    //成功
	WARNING,    //警告
	ERR,		//错误
	INFO		//普通消息
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