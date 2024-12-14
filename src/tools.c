#include "libft_malloc.h"

size_t  align_size(size_t size, size_t alignment)
{
    size = (size + (alignment - 1)) & ~(alignment - 1);
    return size;
}

int     get_type(size_t size)
{
    if ((long int)size <= TINY_ALLOC)
        return TINY;
    if ((long int)size <= SMALL_ALLOC)
        return SMALL;
    return LARGE;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*str;
	const char	*str2;

	if (dst == src)
		return (dst);
	str = (char *)dst;
	str2 = (const char *)src;
	while (n--)
		*str++ = *str2++;
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)b;
	while (len-- > 0)
		*str++ = c;
	return (b);
}

size_t	ft_strlen(const char *s)
{
	int	i;

    if (!s)
        return 0;
    i = 0;
    while (s[i])
        i++;
    return (i);
}