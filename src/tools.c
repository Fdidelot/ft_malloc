#include "libft_malloc.h"

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