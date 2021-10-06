#include"../Public/myStrings.h"

bool initMyStrs(myStrs* strs, int init_size)
{
	assert(strs);
	int size = init_size > 0 ? init_size : DEFAULT_SIZE;
	strs->size = 0;
	strs->maxSize = size;
	strs->data = (oneStr*)malloc(sizeof(oneStr) * strs->maxSize);
	if (!strs->data)
	{
		printf("malloc error!\r\n");
		return false;
	}
	memset(strs->data, 0, strs->maxSize);
	return true;
}

bool addOneStr(myStrs* strs, const char* in_data)
{
	assert(strs);
	if (strs->size >= strs->maxSize)
	{
		strs->maxSize += DEFAULT_SIZE;
		strs->data = (oneStr*)realloc(strs->data, sizeof(oneStr) * strs->maxSize);
		if (!strs->data)
		{
			printf("realloc error\r\n");
			return false;
		}
	}
	strcpy(strs->data[strs->size++].str, in_data);
	return true;
}

char* getOneStrByIndex(myStrs* strs, int index)
{
	assert(strs);
	return strs->data[index].str;
}

void destoryMyStrs(myStrs* strs)
{
	assert(strs);
	free(strs->data);
}
//ջ