# include "libft_malloc.h"

t_data  data;

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

void    *malloc(size_t size)
{
    size = align_size(size, 16);
    if (size > MAX_ALLOCATION_SIZE)
    {
        ft_putstr_fd("Too big allocation\n", 2);
        return (NULL);
    }
    data.size_alloc = size;
    size = size + BLOCK_HEADER;
    data.type = get_type(size);
    data.ptr = NULL;
    if((data.ptr = free_block_available(size)) != NULL)
        return (data.ptr);
    data.ptr = allocate_block(size);
    return (data.ptr);
}