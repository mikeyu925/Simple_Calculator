#include "../Public/myStack.h"

bool initmyDoubleStack(myDoubleStack* stack)
{
	assert(stack);
	stack->size = DEFAULT_SIZE;
	stack->top = -1;
	stack->data = (double*)malloc(sizeof(double) * stack->size);
	if (!stack->data)
	{
		printErrorInfo("Stack data malloc error!\r\n");
		return false;
	}
	memset(stack->data, 0, stack->size * sizeof(double));
	return true;
}

bool pushmyDoubleStack(myDoubleStack* stack, double in_data)
{
	assert(stack);
	if (stack->top >= stack->size - 1)
	{
		stack->size += DEFAULT_SIZE;
		stack->data = (double*)realloc(stack->data, sizeof(double) * stack->size);
		if (!stack->data)
		{
			printErrorInfo("Stack data realloc error!\r\n");
			return false;
		}
	}
	stack->data[++stack->top] = in_data;
	return true;
}

double popmyDoubleStack(myDoubleStack* stack)
{
	assert(stack);
	if (stack->top == -1)
	{
		printErrorInfo("None data! Pop error!\r\n");
		return -1;
	}
	double tmp = stack->data[stack->top--];
	return tmp;
}

bool isEmptymyDoubleStack(const myDoubleStack* stack)
{
	assert(stack);
	return stack->top == -1;
}

double topmyDoubleStack(myDoubleStack* stack)
{
	assert(stack);
	if (stack->top == -1)
	{
		printErrorInfo("None data! Pop error!\r\n");
		return -1;
	}
	return stack->data[stack->top];
}

void destorymyDoubleStack(myDoubleStack* stack)
{
	assert(stack);
	free(stack->data);
}

bool initmyCharStack(myCharStack* stack)
{
	assert(stack);
	stack->size = DEFAULT_SIZE;
	stack->top = -1;
	stack->data = (char*)malloc(sizeof(char) * stack->size);
	if (!stack->data)
	{
		printErrorInfo("Stack data malloc error!\r\n");
		return false;
	}
	memset(stack->data, 0, stack->size * sizeof(char));
	return true;
}

bool pushmyCharStack(myCharStack* stack, char in_data)
{
	assert(stack);
	if (stack->top >= stack->size - 1)
	{
		stack->size += DEFAULT_SIZE;
		stack->data = (char*)realloc(stack->data, sizeof(char) * stack->size);
		if (!stack->data)
		{
			printErrorInfo("Stack data realloc error!\r\n");
			return false;
		}
	}
	stack->data[++stack->top] = in_data;
	return true;
}

char popmyCharStack(myCharStack* stack)
{
	assert(stack);
	if (stack->top == -1)
	{
		printErrorInfo("None data! Pop error!\r\n");
		return -1;
	}
	char tmp = stack->data[stack->top--];
	return tmp;
}

bool isEmptymyCharStack(const myCharStack* stack)
{
	assert(stack);
	return stack->top == -1;
}

char topmyCharStack(myCharStack* stack)
{
	assert(stack);
	if (stack->top == -1)
	{
		printErrorInfo("None data! Pop error!\r\n");
		return -1;
	}
	return stack->data[stack->top];
}

void destorymyCharStack(myCharStack* stack)
{
	assert(stack);
	free(stack->data);
}