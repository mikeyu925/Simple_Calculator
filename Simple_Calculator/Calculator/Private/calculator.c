#include "../Public/calculator.h"
#include<inttypes.h>
#include<math.h>
void calculateExpression(myStrs* expression, double* resultBuf, unsigned int* errBuf)
{
	for (int i = 0; i < expression->size; i++)
	{
		errBuf[i] = getValue(expression->data[i].str, &resultBuf[i]);
	}
}

ERROR_TYPE getValue(const char* expression, double* result)
{
	ERROR_TYPE error;
	if ((error = checkOperator(expression)) != NONE_ERROR) {
		return error;
	}
	myStrs infix;
	myStrs posfix;
	myDoubleStack doubleStack;
	initmyDoubleStack(&doubleStack);
	initMyStrs(&infix, DEFAULT_SIZE);
	initMyStrs(&posfix, DEFAULT_SIZE);
	separateString(expression, " ", &infix);
	if ((error = infixToPosfix(&infix, &posfix)) != NONE_ERROR)
	{
		return error;
	}
	for (int i = 0; i < posfix.size; i++)
	{
		if (!isContainOperator(posfix.data[i].str))//数字直接入栈
		{
			double num = atof(posfix.data[i].str);
			pushmyDoubleStack(&doubleStack, num);
		}
		else {
			if (strstr(posfix.data[i].str, "@")) {//((@4 + 2))
				double a = popmyDoubleStack(&doubleStack);
				pushmyDoubleStack(&doubleStack, sqrt(a));
			}
			else {
				double a = popmyDoubleStack(&doubleStack);
				double b = popmyDoubleStack(&doubleStack);
				if (strstr(posfix.data[i].str, "+"))
				{
					pushmyDoubleStack(&doubleStack, b + a);
				}
				else if (strstr(posfix.data[i].str, "-")) {
					pushmyDoubleStack(&doubleStack, b - a);
				}
				else if (strstr(posfix.data[i].str, "*")) {
					pushmyDoubleStack(&doubleStack, b * a);
				}
				else if (strstr(posfix.data[i].str, "/")) {
					if (a >= -DOUBLE_ZERO_NUM && a <= DOUBLE_ZERO_NUM)
					{
						return ERROR_DIVISOR_ZERO;
					}
					pushmyDoubleStack(&doubleStack, b / a);
				}
				else if (strstr(posfix.data[i].str, "^")) {
					pushmyDoubleStack(&doubleStack, pow(b, a));
				}
			}
		}
	}
	*result = topmyDoubleStack(&doubleStack);
	destoryMyStrs(&infix);
	destoryMyStrs(&posfix);
	return NONE_ERROR;
}
/*test expression
1 + ( ( 2 + 3 ) ) * 4  - 5
7.4 + 2.3 * ( ( 4 / 2 - 3.12 ) + 3.09 ) - ( 3.3 / 3 )
*/
ERROR_TYPE infixToPosfix(myStrs* infix, myStrs* posfix)
{
	myCharStack charStack;
	initmyCharStack(&charStack);
	int index = 0;
	char posfixBuf[MAX_BUF_LEN] = { 0 };
	for (int i = 0; i < infix->size; i++)
	{
		char ch = infix->data[i].str[0];
		if (!isContainOperator(infix->data[i].str))//数 或 括号
		{
			//如果是 括号
			if (isParentheses(infix->data[i].str))
			{
				if (ch == '(')
				{
					pushmyCharStack(&charStack, ch);
				}
				else {// ')'
					while (!isEmptymyCharStack(&charStack) && topmyCharStack(&charStack) != '(')
					{
						char topChar = popmyCharStack(&charStack);
						posfixBuf[index++] = topChar;
						posfixBuf[index++] = ' ';
					}
					if (isEmptymyCharStack(&charStack)) return ERROR_FORMAT;
					else popmyCharStack(&charStack);
				}
			}
			else {//是数字
				strcat(posfixBuf, infix->data[i].str);
				index += strlen(infix->data[i].str);
				posfixBuf[index++] = ' ';
			}
		}//操作符
		else {
			//栈空 或者 栈顶是左括号 或者 优先级大于栈顶优先级，则入栈
			while (!isEmptymyCharStack(&charStack) && topmyCharStack(&charStack) != '(' && lessOrEqualTop(ch, topmyCharStack(&charStack)))
			{
				char topChar = popmyCharStack(&charStack);
				posfixBuf[index++] = topChar;
				posfixBuf[index++] = ' ';
			}
			pushmyCharStack(&charStack, ch);
		}
	}
	while (!isEmptymyCharStack(&charStack))
	{
		char topChar = popmyCharStack(&charStack);
		posfixBuf[index++] = topChar;
		posfixBuf[index++] = ' ';
	}
	if (strstr(posfixBuf, "("))
	{
		return ERROR_FORMAT;
	}
	separateString(posfixBuf, " ", posfix);
	return NONE_ERROR;
}

bool lessOrEqualTop(const char a, const char b) {
	if (a == '+' || a == '-') {
		return true;
	}
	else if (a == '*' || a == '/')
	{
		if (b == '+' || b == '-') return false;
		else return true;
	}
	else {
		if (b == '^' || b == '@') return true;
		else return false;
	}
}
/*
是否包含运算符
^ : 幂次运算符
@ ：开平方运算符
*/
bool isContainOperator(const char* val)
{
	return strstr(val, "+") || strstr(val, "-") || strstr(val, "*") || strstr(val, "/") || strstr(val, "^") || strstr(val, "@");
}
/*
是否是字符
*/
bool isParentheses(const char* val) {
	return strstr(val, "(") || strstr(val, ")");
}
/*
是否是字符或括号
*/
bool isOperatorOrPartent(const char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '^' || ch == '@';
}
/*
是否是数字
*/
bool isDigital(const char ch) {
	return ch >= '0' && ch <= '9';
}

ERROR_TYPE checkOperator(const char* expression) {
	if (strstr(expression, "%") || strstr(expression, "$") || strstr(expression, "#")) return ERROR_OPERATOR;
	else return NONE_ERROR;
}
void printExpressionError(ERROR_TYPE type) {
	if (ERROR_DIVISOR_ZERO == type)
	{
		printErrorInfo("除数不能为0！\r\n");
	}
	else if (ERROR_FORMAT == type)
	{
		printErrorInfo("格式出错，请检查格式！\r\n");
	}
	else if (ERROR_OPERATOR == type)
	{
		printErrorInfo("运算符出错！目前仅支持+-*/运算\r\n");
	}
}
//1+(( 2+3 ))*45
void changeFormat(char* expression) {
	char tmpBuf[MAX_BUF_LEN] = { 0 };
	int indexExp = 0;//expression索引下标
	int indexTmp = 0;//tmpBuf索引下标
	char lastCh = '\0';//上一个 字符
	while (expression[indexExp] != '\0')
	{
		if (expression[indexExp] == ' ') {//是空格
			indexExp++;
		}
		else if (isDigital(expression[indexExp])) {//是数字 0~9 .也会算进来，因为包含浮点数
			while (expression[indexExp] != '\0' && expression[indexExp] != ' ' && (!isOperatorOrPartent(expression[indexExp]))) {
				tmpBuf[indexTmp++] = expression[indexExp++];
			}
			tmpBuf[indexTmp++] = ' ';
		}
		else {//是操作符 +-*/()
			if (expression[indexExp] == '-' || expression[indexExp] == '+') {
				if (indexTmp >= 2 && tmpBuf[indexTmp - 2] == '(') {
					tmpBuf[indexTmp++] = '0';
					tmpBuf[indexTmp++] = ' ';
				}
			}
			tmpBuf[indexTmp++] = expression[indexExp++];
			tmpBuf[indexTmp++] = ' ';
		}
	}
	strcpy(expression, tmpBuf);
}

double mySqrt(const double num)
{
#define EPS_L 1e-5
	double head = 0, tail = 1.0 + num, mid;
	do {
		mid = (head + tail) / 2;
		if (mid * mid - num > EPS_L) {
			tail = mid;
		}
		else if (mid * mid - num < -EPS_L) {
			head = mid;
		}
	} while (fabs(mid * mid - num) > EPS_L);
#undef EPS_L
	return mid;
}

double gety(double x, double m, int n) {
	double v = 1;
	for (int i = 0; i < n; i++) {
		v *= x;
	}
	return v - m;
}

double getdy(double x, int n) {
	double v = n;
	for (int i = 0; i < n - 1; i++) {
		v *= x;
	}
	return v;
}
//对num开n次方
double getNRoot(double num, int n, int maxCyc) {
	if (num == 0.0) return 0.0;
	double x1, x0;
	x0 = num;
	for (int i = 0; i < maxCyc; i++) {
		if (getdy(x0, n) == 0.0) {
			printf("dy is zero!\r\n");
			return -1;
		}
		x1 = x0 - gety(x0, num, n) / getdy(x0, n);
		if (fabs(x1 - x0) <= 1e-4 || fabs(gety(x1, num, n)) < 1e-4) {
			return x1;
		}
		else {
			x0 = x1;
		}
	}
	printf("超过最大迭代次数!\r\n");
	return -1;
}

double myPow(double x, double n) {
	if (x == 0.0) return 0.0;
	double tmpx = x;
	double res = 1;
	int64_t intN = (int64_t)n;
	if (intN < 0) {
		x = 1 / x;
		intN = -intN;
	}
	while (intN) {
		if (intN & 1) res *= x;
		x *= x;
		intN >>= 1;
	}
	//开始计算小数的幂次
	n = n - (int64_t)n;
	if (n <= 0.1) {//没有小数部分幂次需要计算
		return res;
	}
	else {
		int tmpN = (int)(n * 10);
		int baifenwei = (int)(n * 100) % 10;
		if (baifenwei > 5) tmpN++;
		return res * getNRoot(myPow(tmpx, tmpN), 10, 300);
	}
}