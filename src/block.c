#include "libft_malloc.h"

void    push_block_back(t_block *new_block, t_block **head)
{
    t_block *blocks = *head;

    if (*head == NULL)
    {
        *head = new_block;
        return ;
    }
    while (blocks->next)
        blocks = blocks->next;
    blocks->next = new_block;
    new_block->prev = blocks->next;
}

t_block *new_block(size_t size, void *addr)
{
    t_block *new = addr;

    ft_memset(new, 0, BLOCK_HEADER);
    new->size = size;
    return new;
}

t_block *get_block(size_t size, t_pages *page)
{
    t_block *blocks = page->blocks;

    while (blocks)
    {
        if (blocks->is_free == 1 && blocks->size >= size)
        {
            blocks->is_free = 0;
            if (blocks->size == size)
                return blocks;
            // create_sub_block(blocks, size);
            return blocks;
        }
        blocks = blocks->next;
    }
    blocks = new_block(size, (void *)page + (page->page_size - page->space_left));
    page->space_left -= size;
    push_block_back(blocks, &(page->blocks));
    return blocks;
}
