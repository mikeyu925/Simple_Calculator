#include"Source.h"

//F:\Ywh\test.txt
void initCalculator(void)
{
	setConsoleColor(SIMPLE_PALE_RED, SIMPLE_BLACK);
	printf("$ Welcome to SimpleCalculator_1.0.1 $\r\n");
	setConsoleColor(SIMPLE_PALE_YELLOW, SIMPLE_BLACK);
	printf("$ Calculators support addition, subtraction, multiplication, division, power and square root operations! $\r\n");
	setConsoleColor(SIMPLE_WHITE, SIMPLE_BLACK);
	printf("$ EXAMPLE : 7.4^2 + 2.3 *((-4 / 2 - 3.12 ) + 3.09 ) - ( @4 /8) +0.1  $\r\n");

	if (resultSavePath[0] == '\0')
	{
		_getcwd(resultSavePath, MAX_BUF_LEN);
		strcat(resultSavePath, "\\Result");
		if (_access(resultSavePath, 0) == -1)
		{
			_mkdir(resultSavePath);
		}
	}
}

void runCalculator(void)
{
	myStrs strs;
	bool b_exit = false;
	while (!b_exit) {
		printPreInfo();
		char cmd[MAX_BUF_LEN] = { 0 };
		fgets(cmd, MAX_BUF_LEN, stdin);
		if (strstr(cmd, "--help")) {
			printf("\r\n");
			printNormalInfo("  mode one : 进入标准输入模式，在此模式用户可以输入要计算的表达式!\r\n");
			printNormalInfo("  mode two : 进入文件输入模式，在此模式用户可以输入要计算的目标文件路径!\r\n");
			printNormalInfo("  exit	  : 退出程序!");
		}
		else if (strstr(cmd, "mode one")) {
			while (true)
			{
				myStrs strs;
				initMyStrs(&strs, DEFAULT_SIZE);
				if (!inputExpression(READ_STANDARD_OUT, &strs)) {
					break;
				}
				//计算
				double* res = (double*)malloc(sizeof(double) * strs.size);
				unsigned int* err = (unsigned int*)malloc(sizeof(unsigned int) * strs.size);
				calculateExpression(&strs, res, err);
				for (int i = 0; i < strs.size; i++)
				{
					if (err[i] != NONE_ERROR) printExpressionError(err[i]);
					else printSuccessInfo("%s = %lf\r\n", strs.data[i].str, res[i]);
				}
				free(res);
				free(err);
				destoryMyStrs(&strs);
			}
		}
		else if (strstr(cmd, "mode two")) {
			while (true)
			{
				myStrs strs;
				initMyStrs(&strs, DEFAULT_SIZE);
				if (!inputExpression(READ_FILE, &strs)) {
					break;
				}
				//计算
				double* res = (double*)malloc(sizeof(double) * strs.size);
				unsigned int* err = (unsigned int*)malloc(sizeof(unsigned int) * strs.size);
				calculateExpression(&strs, res, err);
				getTargetFilePath(filePath, targetFilePath, 1);
				for (int i = 0; i < strs.size; i++)
				{
					char exptmp[MAX_BUF_LEN * 2] = { 0 };
					if (err[i] != NONE_ERROR) {
						printExpressionError(err[i]);
						sprintf(exptmp, "%s error!\n", strs.data[i].str);
					}
					else {
						printSuccessInfo("%s = %lf\r\n", strs.data[i].str, res[i]);
						sprintf(exptmp, "%s = %f\n", strs.data[i].str, res[i]);
					}
					addContentsToFile(targetFilePath, exptmp);
				}
				free(res);
				free(err);
				destoryMyStrs(&strs);
			}
		}
		else if (strstr(cmd, "exit")) {
			b_exit = true;
			printSuccessInfo("Exit successfully! Thanks using!\r\n");
		}
		else {
			printWarningInfo("No such command! input --help check command!\r\n");
		}
	}
}

void exitCalculator(void)
{
}

int main(int argc, char* argv[]) {
	initCalculator();//初始化

	runCalculator();//循环工作

	exitCalculator();//退出

	system("pause");
	return EXIT_SUCCESS;
}