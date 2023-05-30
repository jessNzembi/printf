#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flag, wid, prec, siz, buff_indx = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_indx++] = format[i];
			if (buff_indx == BUFF_SIZE)
				print_buffer(buffer, &buff_indx);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_indx);
			flag = flags(format, &i);
			wid = width(format, &i, list);
			prec = precision(format, &i, list);
			siz = size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flag, wid, prec, siz);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_indx);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, rep the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
