#include "main.h"

void print_buffer(char buff[], int *buff_ind);

/**
 * _printf - Printing the function
 * @fmt: fmt
 * Return: Printed input
 */
int _printf(const char *fmt, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flag, width, precision, size, buff_ind = 0;
	va_list list;
	char buff[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buff, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buff, &buff_ind);
			flag = get_flag(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handler_print(format, &i, list, buff,
					flag, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buff, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the content of the buffer
 * @buff: Array of chars
 * @buff_ind: Index of the buffer, it represents the len
 */

void print_buffer(char buff[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buff[0], *buff_ind);

	*buff_ind = 0;
}
