#include"../Public/Input.h"
char filePath[MAX_BUF_LEN] = { 0 };
char targetFilePath[MAX_BUF_LEN] = { 0 };
char resultSavePath[MAX_BUF_LEN] = { 0 };
bool inputExpression(Input_Type type, myStrs* strs)
{
	if (READ_STANDARD_OUT == type)
	{
		char inputBuf[MAX_BUF_LEN] = { 0 };
		printNormalInfo("$ 请输入要计算的表达式: [输入 q 可退出此模式]");
		printf("$ >>>");
		scanf("%[^\n]s", inputBuf);
		getchar();
		if (strstr(inputBuf, "q")) {
			return false;
		}
		changeFormat(inputBuf);
		addOneStr(strs, inputBuf);
	}
	else if (READ_FILE == type)
	{
		printNormalInfo("$ 请输入要打开的文件路径: [输入 q 可退出此模式]");
		printf("$ >>>");
		char readDataBuf[RW_FILE_SIZE] = { 0 };
		scanf("%[^\n]s", filePath);
		getchar();
		if (strstr(filePath, "q")) {
			return false;
		}
		readFileContents(filePath, readDataBuf);
		separateString(readDataBuf, "\n", strs);
		for (int i = 0; i < strs->size; i++) {
			changeFormat(strs->data[i].str);
		}
	}
	return true;
}

bool readFileContents(const char* filePath, char* buf)
{
	FILE* fp = NULL;
	fp = fopen(filePath, "r");
	if (fp)
	{
		char readBuf[RW_FILE_SIZE] = { 0 };
		int  readSize = 0;
		while ((readSize = fread(readBuf, sizeof(char), RW_FILE_SIZE, fp)) > 0) {
			strcat(buf, readBuf);
			memset(readBuf, 0, RW_FILE_SIZE);
		}
		fclose(fp);
		return true;
	}
	printErrorInfo("Open file error! no such file or directory!\r\n");
	return false;
}

bool writeContentsToFile(const char* filePath, char* writeData)
{
	FILE* fp = NULL;
	fp = fopen(filePath, "w");
	if (fp != NULL)
	{
		fprintf(fp, "%s", writeData);
		fclose(fp);
		return true;
	}
	printErrorInfo("Open file error! no such file or directory!\r\n");
	return false;
}

bool addContentsToFile(const char* filePath, char* addData)
{
	FILE* fp = NULL;
	fp = fopen(filePath, "a");
	if (fp != NULL)
	{
		fprintf(fp, "%s", addData);
		fclose(fp);
		return true;
	}
	printErrorInfo("Open file error! no such file or directory!\r\n");
	return false;
}

//注意，传入的  myStrs strs 需要初始化
void separateString(const char* inStr, const char* subStr, myStrs* strs)
{
	char tmpBuf[RW_FILE_SIZE] = { 0 };
	strcpy(tmpBuf, inStr);

	char* p = strtok(tmpBuf, subStr);
	while (p != NULL)
	{
		addOneStr(strs, p);
		p = strtok(NULL, subStr);
	}
}

void getTargetFilePath(const char* srcFilePath, char* dstFilePath, int type)
{//F:\网课\开课吧\C&CPP\pic.txt
	char srcTmpBuf[MAX_BUF_LEN] = { 0 };
	if (0 == type) {
		strcpy(srcTmpBuf, srcFilePath);
		removeString(srcTmpBuf, ".txt");
		strcat(srcTmpBuf, ".out");
		strcpy(dstFilePath, srcTmpBuf);
	}
	else if (1 == type)
	{
		myStrs strs;
		initMyStrs(&strs, DEFAULT_SIZE);
		//获取源文件文件名xxx.txt
		separateString(srcFilePath, "\\", &strs);
		char tmp[MAX_BUF_LEN] = { 0 };
		strcpy(tmp, getOneStrByIndex(&strs, strs.size - 1));
		//修改后缀
		removeString(tmp, ".txt");
		strcat(tmp, ".out");

		strcpy(dstFilePath, resultSavePath);
		strcat(dstFilePath, "\\");
		strcat(dstFilePath, tmp);
	}
}

void getnext(char const* sub_str, int* next) {
	int len = strlen(sub_str);
	int k = -1;
	int j = 0;
	next[0] = -1;
	while (j < len - 1)
	{
		if (k == -1 || sub_str[k] == sub_str[j])
		{
			++j;
			++k;
			if (sub_str[k] != sub_str[j])
			{
				next[j] = k;
			}
			else {
				next[j] = next[k];
			}
		}
		else {
			k = next[k];
		}
	}
}

int find_string_kmp(char* str, char const* sub_str) {
	int index = -1;
	int len_str = strlen(str);
	int len_substr = strlen(sub_str);
	if (len_str == 0 || len_substr == 0)
	{
		return index;
	}
	int* next = (int*)malloc(sizeof(int) * len_substr);
	if (!next)
	{
		printf("get next array with malloc error!\r\n");
		return index;
	}
	getnext(sub_str, next);
	int i = 0, j = 0;
	while (i < len_str && j < len_substr)
	{
		if (j == -1 || str[i] == sub_str[j])
		{
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	free(next);
	return j == len_substr ? i - j : -1;
}

void removeString(char* str, char const* sub_str) {
	int index = find_string_kmp(str, sub_str);
	if (index != -1)
	{
		strcpy(&str[index], &str[index + strlen(sub_str)]);
	}
}