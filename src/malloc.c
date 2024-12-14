# include "libft_malloc.h"

t_data  data;

void    *calloc(size_t count, size_t size)
{
    size_t  array;
    void    *ptr;

    if (!size)
        return NULL;
    array = count * size;
    ptr = malloc(array);
    if (ptr == NULL)
        return NULL;
    ft_memset(ptr, 0, array);
    return (ptr);

}

void    *malloc(size_t size)
{
    t_pages *page = NULL;
    t_block *block = NULL;

    size = align_size(size + BLOCK_HEADER, 16);
    if (size > MAX_ALLOCATION_SIZE)
    {
        ft_putstr_fd("Too big allocation\n", 2);
        return (NULL);
    }
    page = get_page(size, get_type(size));
    if (page == NULL)
        return NULL;
    block = get_block(size, page);
    if (block == NULL)
        return NULL;
    return ((void *)block + BLOCK_HEADER);
}