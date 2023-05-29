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
int (*fn)(va_list, char[], int, int, int, int);
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
int print_hexadecimal(va_list types, char buff[],
		int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buff[],
		int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[],
char buff[], int flag, char flag_ch, int width, int precision, int size);
/* Functions to print non printable characters */
int print_non_printable(va_list types, char buff[],
		int flags, int width, int precision, int size);
/* Function to print memory address */
int print_ptr(va_list types, char buff[],
		int flag, int width, int precision, int size);
/* Functions to other specifiers */
int get_flag(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);
/* Function to print string in reverse */
int print_rev(va_list types, char buff[],
		int flag, int width, int precision, int size);
/* prints string in rot13'ed  */
int print_rot13str(va_list types, char buff[],
	int flag, int width, int precision, int size);
/* width handler */
int write_char_handle(char c, char buff[],
	int flag, int width, int precision, int size);
int write_num(int is_positive, int ind, char buff[],
	int flag, int width, int precision, int size);
int write_num(int ind, char buff[], int flag, int width, int precision,
		int length, char padd, char extra_c);
int write_ptr(char buff[], int ind, int length,
	int width, int flag, char pad, char extra_c, int pad_start);
int write_unsgnd(int is_negative, int ind,
char buff[],
int flags, int width, int precision, int size);
/****************** UTILS ******************/
int is_printable(char);
int append_hexadecimal(char, char[], int);
int is_digit(char);
long int convert_size_num(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */
