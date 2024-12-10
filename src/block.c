#include "libft_malloc.h"

t_block *push_block_front(t_block *block, t_block **head)
{
    block->next = *head;
    block->prev = NULL;
    if (*head)
        (*head)->prev = block;
    return block;
}

void    *allocate_block(size_t size)
{
    t_pages *current_page = get_pages(size, data.type);
    t_block *new_block;

    if (current_page == NULL)
        return (NULL);
    new_block = (t_block *)((char *)current_page + (current_page->page_size - current_page->space_left));
    ft_memset(new_block, 0, BLOCK_HEADER);
    new_block->size = size;
    current_page->blocks = push_block_front(new_block, &(current_page->blocks));
    current_page->space_left -= size;
    data.total_size_alloc += size - BLOCK_HEADER;
    return ((char *)new_block + BLOCK_HEADER);
}