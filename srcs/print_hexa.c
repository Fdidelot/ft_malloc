#include "ft_malloc.h"

void	print_hexa_char(char c)
{
	c += 48;
	if (c > 57)
		c += 17;
	write (1, &c, 1);
}

void	print_octet(char c)
{
	char o;

	o = c >> 4;
	print_hexa_char(o);
	o = (c << 4) >> 4;
	print_hexa_char(o);
}

void	print_hexa(char *ptr)
{
	char c;

	for (int i = 0; i < 8; i++)
	{
		c = ptr;
		print_octet(c);
		ptr++;
	}
}