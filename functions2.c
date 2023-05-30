#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int indx = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_adrs;
	char map_to[] = "0123456789abcdef";
	void *adrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (adrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_adrs = (unsigned long)adrs;

	while (num_adrs > 0)
	{
		buffer[indx--] = map_to[num_adrs % 16];
		num_adrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	indx++;

	return (write_pointer(buffer, indx, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *ptr = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (ptr == NULL)
		return (write(1, "(null)", 6));

	while (ptr[i] != '\0')
	{
		if (is_printable(ptr[i]))
			buffer[i + offset] = ptr[i];
		else
			offset += append_hexa_code(ptr[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *ptr;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	ptr = va_arg(types, char *);

	if (ptr == NULL)
	{
		UNUSED(precision);

		ptr = ")Null(";
	}
	for (i = 0; ptr[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char c = ptr[i];

		write(1, &c, 1);
		count++;
	}
	return (count);
}
/**
 * print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c;
	char *ptr;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	ptr = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (ptr == NULL)
		ptr = "(AHYY)";
	for (i = 0; ptr[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == ptr[i])
			{
				c = out[j];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			c = ptr[i];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
