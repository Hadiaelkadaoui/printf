#include "main.h"
/**
 * handler_print - Prints strg
 * @fmt: Formatted string in which to prints args
 * @list: List of args to be printed
 * @ind: index
 * @buff: Buffer array to handle print
 * @flag: Calculates active flag
 * @width: get width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: 1 or 2
 */
int handler_print(const char *fmt, int *ind, va_list list, char buff[],
	int flag, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	fmt_t format_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa}, {'p', print_ptr}, {'S', print_non_printable},
		{'r', print_rev}, {'R', print_rot13str}, {'\0', NULL}
	};
	for (i = 0; format_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == format_types[i].fmt)
			return (format_types[i].fn(list, buff, flag, width, precision, size));

	if (format_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (-1);
	}
	return (printed_chars);
}
return
