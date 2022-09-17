#include <stdio.h>
#include <stdarg.h>
#include <ctime>

#define LOG_WARN(str, ...) LOG_print("WARN", __FILE__, __FUNCTION__, __LINE__, __TIME__, str, ##__VA_ARGS__)
#define LOG_ERROR(str, ...) LOG_print("ERROR", __FILE__, __FUNCTION__, __LINE__, __TIME__, str, ##__VA_ARGS__)
#define LOG_INFO(str, ...) LOG_print("INFO", __FILE__, __FUNCTION__, __LINE__, __TIME__, str, ##__VA_ARGS__)
#define LOG_DEBUG(str, ...) LOG_print("DEBUG", __FILE__, __FUNCTION__, __LINE__, __TIME__, str, ##__VA_ARGS__)
#define LOG_TRACE(str, ...) LOG_print("TRACE", __FILE__, __FUNCTION__, __LINE__, __TIME__, str, ##__VA_ARGS__)
#define LOG_ALL(str, ...) LOG_print("ALL", __FILE__, __FUNCTION__, __LINE__, __TIME__)printf(str, ##__VA_ARGS__, "\n")

void LOG_print(const char* log_type,
	const char* filename,
	const char* funcname,
	const int linenum,
	const char* time,
	const char* str, ...)
{
	va_list List;
	va_start(List,str);
	printf("%s | ", time);
	printf("%s | ", log_type);
	printf("FILE : %s / FUNC : %s / NUM : %d | ", filename, funcname, linenum);
	vprintf(str,List);
	va_end(List);
	printf("\n");
}