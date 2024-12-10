# include "libft_malloc.h"

t_block *is_in_page(t_block *block, t_pages *pages)
{
    t_block *tmp_block;

    while (pages)
    {
        tmp_block = pages->blocks;
        while (tmp_block)
        {
            if (tmp_block == block)
                return tmp_block;
            tmp_block = tmp_block->next;
        }
        pages = pages->next;
    }
    return NULL;
}

t_block *block_exist(t_block *block)
{
    t_block *block_found = NULL;

    if ((block_found = is_in_page(block, data.large_pages)) != NULL)
        return block_found;
    if ((block_found = is_in_page(block, data.small_pages)) != NULL)
        return block_found;
    if ((block_found = is_in_page(block, data.tiny_pages)) != NULL)
        return block_found;
    return block_found;
}

bool    all_blocks_freed(t_block *blocks)
{
    while (blocks)
    {
        if (blocks->is_free == 0)
            return false;
        blocks = blocks->next;
    }
    return true;
}

void    munmap_page(t_pages *page, int type)
{
    t_pages *head = NULL;

    if (page->prev == NULL)
    {
        head = page->next;
        if (head)
            head->prev = NULL;
        if (type & TINY)
            data.tiny_pages = head;
        if (type & SMALL)
            data.small_pages = head;
        if (type & LARGE)
            data.large_pages = head;
    }
    else if (page->next == NULL)
        page->prev->next = NULL;
    else
    {
        page->prev->next = page->next;
        page->next->prev = page->prev;
    }
    data.total_pages_size -= page->page_size;
    if (munmap(page, page->page_size) != 0)
        print_str_and_addr("Invalid munmap() on addr", page);
}

bool    is_empty_page(t_pages *pages, int type)
{
    while(pages)
    {
        if (all_blocks_freed(pages->blocks))
        {
            munmap_page(pages, type);
            return true;
        }
        pages = pages->next;
    }
    return false;
}

void    free_page(size_t type)
{
    if (type & LARGE)
        is_empty_page(data.large_pages, LARGE);
    if (type & SMALL)
        is_empty_page(data.small_pages, SMALL);
    if (type & TINY)
        is_empty_page(data.tiny_pages, TINY);
}

t_block *is_free_block_in_pages(t_pages *pages, size_t size)
{
    t_block *block;

    while(pages)
    {
        block = pages->blocks;
        while (block)
        {
            if (block->is_free && block->size >= size)
            {
                block->is_free = 0;
                data.total_size_alloc += size - BLOCK_HEADER;
                return ((t_block *)((char *)block + BLOCK_HEADER));
            }
            block = block->next;
        }
        pages = pages->next;
    }
    return NULL;
}

t_block *free_block_available(size_t size)
{
    if (data.type & SMALL)
        return (is_free_block_in_pages(data.small_pages, size));
    return (is_free_block_in_pages(data.tiny_pages, size));
}

void    free(void *ptr)
{
    t_block *block;

    if (ptr == NULL)
        return ;
    block = block_exist((t_block*)((char *)ptr - BLOCK_HEADER));
    if (block == NULL)
        return ;
    if (block->is_free == 1)
    {
        print_str_and_addr("Double free on addr : ", ptr);
        return ;
    }
    block->is_free = 1;
    data.total_size_alloc -= block->size - BLOCK_HEADER;
    free_page(get_type(block->size));
}