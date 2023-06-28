#include "main.h"
#include <stdio.h>
#include <unistd.h>

/************************* WRITE HANDLE *************************/
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = (flags & F_ZERO) ? '0' : ' ';
	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		snprintf(&buffer[1], BUFF_SIZE - 1, "%*c", width - 1, padd);

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) + write(1,
						&buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1],
						width - 1) + write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = (flags & F_ZERO) && !(flags & F_MINUS) ? '0' : ' ';
	char extra_ch = 0;

	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
				length, padd, extra_ch));
}

int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';

	while (prec > length)
		buffer[--ind] = '0', length++;

	if (extra_c != 0)
		length++;

	if (width > length)
	{
		snprintf(&buffer[1], BUFF_SIZE - 1, "%*c", width - length, padd);

		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[1], width - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], width - 1)
					+ write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], width - 1)
					+ write(1, &buffer[ind], length));
		}
	}

	if (extra_c)
		buffer[--ind] = extra_c;

	return (write(1, &buffer[ind], length));
}
