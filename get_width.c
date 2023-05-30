#include "main.h"

/**
 * get_width - Calculates the width for printing
 * @fmt: Formatted string in which to print args
 * @i: List of args to be printed
 * @list: list of args.
 *
 * Return: width
 */
int get_width(const char *fmt, int *i, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; fmt[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(fmt[curr_i]))
		{
			width *= 10;
			width += fmt[curr_i] - '0';
		}
		else if (fmt[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = curr_i - 1;
	return (width);
}
