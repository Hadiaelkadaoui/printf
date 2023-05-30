#include "main.h"

/**
 * get_size - Calculates the size to cast arg
 * @fmt: Formatted string in which to print args
 * @i: List of args to be printed
 *
 * Return: Precision specifier
 */
int get_size(const char *fmt, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (fmt[curr_i] == 'l')
		size = SIZE_LONG;
	else if (format[curr_i] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
