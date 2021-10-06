#include"../Public/windows_setting.h"

void setConsoleColor(console_w_color pen_color, console_w_color background_color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (unsigned short)pen_color + (unsigned short)background_color * 0x10);
}

void printInfo(showType type, const char* format, ...)
{
	char preInfoBuf[20] = { 0 };
	char buf[RW_FILE_SIZE] = { 0 };

	switch (type)
	{
	case SUCCESS:
		strcpy(preInfoBuf, "SUCCESS");
		setConsoleColor(SIMPLE_GREEN, SIMPLE_BLACK);
		break;
	case WARNING:
		strcpy(preInfoBuf, "WARNING");
		setConsoleColor(SIMPLE_YELLOW, SIMPLE_BLACK);
		break;
	case ERR:
		strcpy(preInfoBuf, "ERROR");
		setConsoleColor(SIMPLE_RED, SIMPLE_BLACK);
		break;
	case INFO:
		setConsoleColor(SIMPLE_WHITE, SIMPLE_BLACK);
		break;
	default:
		break;
	}

	va_list args;
	va_start(args, format);
	_vsnprintf_s(buf, RW_FILE_SIZE - 1, RW_FILE_SIZE, format, args);
	buf[RW_FILE_SIZE - 1] = '\0';
	char  text_buf[RW_FILE_SIZE * 2] = { 0 };
	if (type == INFO)
	{
		get_printf(text_buf, "%s \r\n", buf);
	}
	else {
		get_printf(text_buf, "[%s] %s \r\n", preInfoBuf, buf);
	}
	printf("%s", text_buf);
	setConsoleColor(SIMPLE_WHITE, SIMPLE_BLACK);
}

int get_printf(char* buf, char* format, ...) {
	va_list param_list;//初始化参数列表（参数指针）
	va_start(param_list, format);//必须调用该宏才能开始使用可选参数

	char param_char = *format++;//获取format中字符 先取值*，再++
	for (int i = 0; param_char != '\0'; i++)
	{//f u x d
		if (param_char != '%' && *(format - 1) != '%')
		{
			buf[i] = param_char;
		}
		else {
			param_char = *format++;
			switch (param_char)
			{
			case 'c':
			case 'C':
			{
				buf[i] = va_arg(param_list, char);
				break;
			}
			case 's':
			case 'S':
			{
				char* p = va_arg(param_list, char*);
				int len = strlen(p);
				for (int j = 0; j < len;)
				{
					buf[i++] = p[j++];
				}
				i--;//消除'\0'，因为外面大循环还有个i++
				break;
			}
			case 'd':
			case 'D':
			case 'i':
			case 'I':
			{
				int num = va_arg(param_list, int);
				char buf_int[8] = { 0 };
				char* p = _itoa(num, buf_int, 10);
				int len = strlen(p);
				for (int j = 0; j < len;)
				{
					buf[i++] = p[j++];
				}
				i--;//消除'\0'
				break;
			}
			case 'f':
			case 'F'://还需要优化
			{
				float num_f = va_arg(param_list, double);
				int ndigits = 16;
				int precision = 6;
				int sign, dec_pl;
				char* p_f = _ecvt(num_f, ndigits, &dec_pl, &sign);
				int len = strlen(p_f);
				for (int j = 0, precnt = 0, add = 0; j < len && precnt < precision;)
				{
					if (j == dec_pl)
					{
						buf[i++] = '.';
						add = 1;
					}
					buf[i++] = p_f[j++];
					if (add)
					{
						precnt++;
					}
				}
				i--;//消除'\0'
				break;
			}
			default:
				break;
			}
		}
		param_char = *format++;
	}

	va_end(param_list);

	return strlen(buf) + 1;
}

void printPreInfo(void)
{
	printf("\r\n");
	setConsoleColor(SIMPLE_GREEN, SIMPLE_BLACK);
	printf("$ SimpleCalculator $");
	setConsoleColor(SIMPLE_PALE_YELLOW, SIMPLE_BLACK);
	printf(" Design by ");
	setConsoleColor(SIMPLE_VIOLET, SIMPLE_BLACK);
	printf("SmallFish");
	setConsoleColor(SIMPLE_WHITE, SIMPLE_BLACK);
	printf(" [ Input --help to get help ]\r\n");
	printf("$ >>>");
}

char* getCurrentTime(void) {
	time_t now;
	time(&now);
	return ctime(&now);
}