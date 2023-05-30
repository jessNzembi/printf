#include "main.h"

/**
 * flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flagz:
 */
int flags(const char *format, int *i)
{
	int j, curr_i;
	int flagz = 0;
	const char FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		for (j = 0; FLAGS_CHAR[j] != '\0'; j++)
			if (format[curr_i] == FLAGS_CHAR[j])
			{
				flagz |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CHAR[j] == 0)
			break;
	}

	*i = curr_i - 1;

	return (flagz);
}

/**
 * precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Prec.
 */
int precision(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int prec = -1;

	if (format[curr_i] != '.')
		return (prec);

	prec = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			prec *= 10;
			prec += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			prec = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (prec);
}

/**
 * size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: siz.
 */
int size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int siz = 0;

	if (format[curr_i] == 'l')
		siz = S_LONG;
	else if (format[curr_i] == 'h')
		siz = S_SHORT;

	if (siz == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (siz);
}

/**
 * width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: wid.
 */
int width(const char *format, int *i, va_list list)
{
	int curr_i;
	int wid = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			wid *= 10;
			wid += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			wid = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (wid);
}
