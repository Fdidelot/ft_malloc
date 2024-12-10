#include "libft_malloc.h"

void    *warning_bypass(t_block *addr)
{
    return ((char *)addr + BLOCK_HEADER);
}

void    *realloc(void *ptr, size_t size)
{
    t_block *block;
    void    *new;

    if (!ptr)
        return (malloc(size));
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }
    block = block_exist((t_block*)((char *)ptr - BLOCK_HEADER));
    if (block == NULL || block->is_free == 1)
        return NULL;
    if (block->size >= size)
        return (ptr);
    new = malloc(size);
    if (new == NULL)
        return NULL;
    ft_memcpy(new, ptr, block->size - BLOCK_HEADER);
    free(warning_bypass(block));
    return (new);
}