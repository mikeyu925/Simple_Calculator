#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "../../BaseDefine/baseDefine.h"
#include "../../WindowsSetting/Public/windows_setting.h"
//ջ
typedef struct dstack {
	int size;
	int top;
	double* data;
}myDoubleStack;

typedef struct cstack {
	int size;
	int top;
	char* data;
}myCharStack;

bool initmyDoubleStack(myDoubleStack* stack);

bool pushmyDoubleStack(myDoubleStack* stack, double in_data);

double popmyDoubleStack(myDoubleStack* stack);

bool isEmptymyDoubleStack(const myDoubleStack* stack);

double topmyDoubleStack(myDoubleStack* stack);

void destorymyDoubleStack(myDoubleStack* stack);

//
bool initmyCharStack(myCharStack* stack);

bool pushmyCharStack(myCharStack* stack, char in_data);

char popmyCharStack(myCharStack* stack);

bool isEmptymyCharStack(const myCharStack* stack);

char topmyCharStack(myCharStack* stack);

void destorymyCharStack(myCharStack* stack);