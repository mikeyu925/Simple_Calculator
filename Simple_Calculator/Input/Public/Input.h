#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "../../BaseDefine/baseDefine.h"
#include "../../DataStructure/myStructure.h"
#include "../../Calculator/Public/calculator.h"
typedef enum inputtype
{
	READ_STANDARD_OUT = 0x01,
	READ_FILE
}Input_Type;

extern char filePath[MAX_BUF_LEN];
extern char targetFilePath[MAX_BUF_LEN];
extern char resultSavePath[MAX_BUF_LEN];

bool inputExpression(Input_Type type, myStrs* strs);
bool readFileContents(const char* filePath, char* buf);
bool writeContentsToFile(const char* filePath, char* writeData);
bool addContentsToFile(const char* filePath, char* addData);
void separateString(const char* inStr, const char* subStr, myStrs* strs);
void getTargetFilePath(const char* srcFilePath, char* dstFilePath, int type);
void getnext(char const* sub_str, int* next);
int find_string_kmp(char* str, char const* sub_str);
void removeString(char* str, char const* sub_str);