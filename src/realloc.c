#include "libft_malloc.h"

void    create_sub_block(t_block *block, size_t size)
{
    size_t  diff = align_size(block->size - size, 16);
    t_block *new;

    if (diff > BLOCK_HEADER)
    {
        block->size = size;
        new = new_block(diff, (void *)block + block->size);
        new->is_free = 1;
        new->prev = block;
        new->next = block->next;
        if (block->next)
            block->next->prev = new;
        block->next = new;
    }
}

void    *realloc(void *ptr, size_t size)
{
    t_pages *page;
    t_block *block;
    void    *new;

    if (!ptr)
        return (malloc(size));
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }
    page = is_in_page(ptr);
    if (page == NULL)
        return NULL;
    block = block_exist(page, ptr);
    if (block == NULL || block->is_free == 1)
        return NULL;
    if (block->size == size + BLOCK_HEADER)
        return (ptr);
    if (block->size - BLOCK_HEADER > size)
        return ptr;
    new = malloc(size);
    ft_memcpy(new, ptr, block->size - BLOCK_HEADER);
    free(ptr);
    return (new);
}