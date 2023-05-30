#include "main.h"

/**
 * write_char_handle - Prints string
 * @c: char types
 * @buff: Buffer array to handle print
 * @flag: Calculates active flag
 * @width: Widthspecifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed
 */
int write_char_handle(char c, char buff[],
	int flag, int width, int precision, int size)
{
	int i = 0;
	char pad = ' ';

	NONUSED(precision);
	NONUSED(size);

	if (flag & FLAG_ZERO)
		pad = '0';

	buff[i++] = c;
	buff[i] = '\0';

	if (width > 1)
	{
		buff[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buff[BUFF_SIZE - i - 2] = pad;

		if (flag & FLAG_MINUS)
			return (write(1, &buff[0], 1) +
					write(1, &buff[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buff[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buff[0], 1));
	}

	return (write(1, &buff[0], 1));
}


/**
 * write_num - Prints a string
 * @is_negative: Lista of args
 * @ind: char types
 * @buff: Buffer array to handle print
 * @flag:  Calculates active flag
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_num(int is_negative, int ind, char buff[],
	int flag, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1;
	char pad = ' ', xtra_ch = 0;

	NONUSED(size);

	if ((flag & FLAG_ZERO) && !(flag & FLAG_MINUS))
		pad = '0';
	if (is_negative)
		xtra_ch = '-';
	else if (flag & FLAG_PLUS)
		xtra_ch = '+';
	else if (flag & FLAG_SPACE)
		xtra_ch = ' ';

	return (write_num(ind, buff, flag, width, precision,
		len, pad, xtra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buff
 * @buff: Buffer
 * @flag: Flags
 * @width: width
 * @prec: Precision specifier
 * @len: Number len
 * @pad: Pading char
 * @xtra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buff[],
	int flag, int width, int prec,
	int len, char pad, char xtra_c)
{
	int i, pad_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0')
		buff[ind] = pad = ' '; /* width is displayed with pading ' ' */
	if (prec > 0 && prec < len)
		pad = ' ';
	while (prec > len)
		buff[--ind] = '0', len++;
	if (xtra_c != 0)
		len++;
	if (width > len)
	{
		for (i = 1; i < width - len + 1; i++)
			buff[i] = pad;
		buff[i] = '\0';
		if (flag & FLAG_MINUS && pad == ' ')/* Asign xtra char to left of buff */
		{
			if (xtra_c)
				buff[--ind] = xtra_c;
			return (write(1, &buff[ind], len) + write(1, &buff[1], i - 1));
		}
		else if (!(flag & FLAG_MINUS) && pad == ' ')/* xtra char to left of buff */
		{
			if (xtra_c)
				buff[--ind] = xtra_c;
			return (write(1, &buff[1], i - 1) + write(1, &buff[ind], len));
		}
		else if (!(flag & FLAG_MINUS) && pad == '0')/* xtra char to left of pad */
		{
			if (xtra_c)
				buff[--pad_start] = xtra_c;
			return (write(1, &buff[pad_start], i - pad_start) +
				write(1, &buff[ind], len - (1 - pad_start)));
		}
	}
	if (xtra_c)
		buff[--ind] = xtra_c;
	return (write(1, &buff[ind], len));
}

/**
 * write_unsignd - Writes an unsigned number
 * @is_negative: Number indexicating if the num is negative
 * @ind: Index at which the number starts in the buff
 * @buff: Array of chars
 * @flag: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsignd(int is_negative, int ind,
	char buff[],
	int flag, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int len = BUFF_SIZE - ind - 1, i = 0;
	char pad = ' ';

	NONUSED(is_negative);
	NONUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		pad = ' ';

	while (precision > len)
	{
		buff[--ind] = '0';
		len++;
	}

	if ((flag & FLAG_ZERO) && !(flag & FLAG_MINUS))
		pad = '0';

	if (width > len)
	{
		for (i = 0; i < width - len; i++)
			buff[i] = pad;

		buff[i] = '\0';

		if (flag & FLAG_MINUS) /* Asign xtra char to left of buff [buff>pad]*/
		{
			return (write(1, &buff[ind], len) + write(1, &buff[0], i));
		}
		else /* Asign xtra char to left of pading [pad>buff]*/
		{
			return (write(1, &buff[0], i) + write(1, &buff[ind], len));
		}
	}

	return (write(1, &buff[ind], len));
}

/**
 * write_ptr - Write a memory address
 * @buff: Arrays of chars
 * @ind: Index at which the number starts in the buff
 * @len: Length of number
 * @width: Wwidth specifier
 * @flag: Flags specifier
 * @pad: Char representing the pading
 * @xtra_c: Char representing xtra char
 * @pad_start: Index at which pading should start
 *
 * Return: Number of written chars.
 */
int write_ptr(char buff[], int ind, int len,
	int width, int flag, char pad, char xtra_c, int pad_start)
{
	int i;

	if (width > len)
	{
		for (i = 3; i < width - len + 3; i++)
			buff[i] = pad;
		buff[i] = '\0';
		if (flag & FLAG_MINUS && pad == ' ')/* Asign xtra char to left of buff */
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (xtra_c)
				buff[--ind] = xtra_c;
			return (write(1, &buff[ind], len) + write(1, &buff[3], i - 3));
		}
		else if (!(flag & FLAG_MINUS) && pad == ' ')/* xtra char to left of buff */
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (xtra_c)
				buff[--ind] = xtra_c;
			return (write(1, &buff[3], i - 3) + write(1, &buff[ind], len));
		}
		else if (!(flag & FLAG_MINUS) && pad == '0')/* xtra char to left of pad */
		{
			if (xtra_c)
				buff[--pad_start] = xtra_c;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[pad_start], i - pad_start) +
				write(1, &buff[ind], len - (1 - pad_start) - 2));
		}
	}
	buff[--ind] = 'x';
	buff[--ind] = '0';
	if (xtra_c)
		buff[--ind] = xtra_c;
	return (write(1, &buff[ind], BUFF_SIZE - ind - 1));
}
