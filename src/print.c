#include "libft_malloc.h"

void	ft_putnbr_base_fd(size_t n, int base, int fd)
{
	long	nb;

    char base_char[16] = "0123456789ABCDEF";
    char to_input[2];

    to_input[1] = '\0';
	nb = n;
	if (nb > base - 1)
		ft_putnbr_base_fd(nb / base, base, fd);
    nb = (nb % base);
    to_input[0] = base_char[nb];
	ft_putstr_fd(to_input, fd);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void    print_str(char *str)
{
    ft_putstr_fd(str, 1);
}

void    print_number(size_t nb)
{
    ft_putnbr_base_fd(nb, 10, 1);
}

void    print_addr(void *addr)
{
    print_str("0x");
    ft_putnbr_base_fd((size_t)addr, 16, 1);
}

void    print_str_and_addr(char *str, void *addr)
{
    print_str(str);
    print_addr(addr);
    print_str("\n");
}

void    print_str_and_number(char *str, size_t nb)
{
    print_str(str);
    print_number(nb);
    print_str("\n");
}