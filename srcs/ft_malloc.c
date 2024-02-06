#include "ft_malloc.h"

void	*malloc(size_t size)
{
	void *ptr;
	if (size != 0)
	{
		ptr = mmap(NULL, size, 0, 0, 0, 0);
		print_hexa(ptr);
		write(1, &ptr, 8);
		write(1, "\n", 1);
	}
	return (NULL);
}