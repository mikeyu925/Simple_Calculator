#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../../BaseDefine/baseDefine.h"
#include "../../WindowsSetting/Public/windows_setting.h"
//存储一条字符串
typedef struct oneString
{
	char str[MAX_BUF_LEN];
}oneStr;

//存储多条字符串集合
typedef struct Strings
{
	int size;
	int maxSize;
	oneStr* data;
}myStrs;

bool initMyStrs(myStrs* strs, int init_size);

bool addOneStr(myStrs* strs, const char* in_data);

char* getOneStrByIndex(myStrs* strs, int index);

void destoryMyStrs(myStrs* strs);
