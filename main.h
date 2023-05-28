#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define NONUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
* struct fmt - Struct op
* @fmt: The format.
* @fn: The function associated
*/
struct fmt
{
char fmt;
int (*fn) (va_list, char[], int, int, int);
};
/**
* typedef struct format format_t - Struct op
* @fmt: The format.
* @fmt_t: The function associated.
*/
typedef struct fmt fmt_t;
int _printf(const char *format, ...);
int handler_print(const char *fmt, int *i,
va_list list, char buff[], int flag, int width, int precision, int size);
/***************** FUNCTIONS ******************/
/* Functions to print chars and strings */
int print_char(va_list types, char buff[],
int flag, int width, int precision, int size);
int print_string(va_list types, char buff[],
int flag, int width, int precision, int size);
int print_percent(va_list types, char buff[],
int flag, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list types, char buff[],
int flag, int width, int precision, int size);
int print_binary(va_list types, char buff[],
int flag, int width, int precision, int size);
int print_unsigned(va_list types, char buff[],
int flag, int width, int precision, int size);
int print_octal(va_list types, char buff[],
int flag, int width, int precision, int size);
