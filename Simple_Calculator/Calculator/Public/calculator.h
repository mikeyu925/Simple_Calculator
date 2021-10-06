#pragma once
#include "../../DataStructure/myStructure.h"
#include "../../Input/Public/Input.h"

typedef enum
{
	ERROR_FORMAT = 0x00,
	ERROR_DIVISOR_ZERO,
	ERROR_OPERATOR,
	NONE_ERROR
}ERROR_TYPE;

void calculateExpression(myStrs* expression, double* resultBuf, unsigned int* errBuf);
ERROR_TYPE getValue(const char* expression, double* result);
ERROR_TYPE infixToPosfix(myStrs* infix, myStrs* posfix);
ERROR_TYPE checkOperator(const char* expression);
void printExpressionError(ERROR_TYPE type);
bool lessOrEqualTop(const char a, const char b);
void changeFormat(char* expression);
bool isContainOperator(const char* val);
bool isParentheses(const char* val);
bool isOperatorOrPartent(const char ch);
bool isDigital(const char ch);
double mySqrt(const double num);
double gety(double x, double m, int n);
double getdy(double x, int n);
double getNRoot(double num, int n, int maxCyc);
double myPow(double x, double n);