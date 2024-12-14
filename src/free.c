# include "libft_malloc.h"

t_pages *is_in_page(void *ptr)
{
    t_pages *pages = data.tiny_pages;

    while (pages)
    {
        if ((size_t)ptr > (size_t)pages && (size_t)ptr < (size_t)pages + pages->page_size)
            return pages;
        pages = pages->next;
    }
    pages = data.small_pages;
    while (pages)
    {
        if ((size_t)ptr > (size_t)pages && (size_t)ptr < (size_t)pages + pages->page_size)
            return pages;
        pages = pages->next;
    }
    pages = data.large_pages;
    while (pages)
    {
        if ((size_t)ptr > (size_t)pages && (size_t)ptr < (size_t)pages + pages->page_size)
            return pages;
        pages = pages->next;
    }
    return NULL;
}

t_block *block_exist(t_pages *page, void *ptr)
{
    t_block *blocks = page->blocks;

    while (blocks)
    {
        if (ptr == (void *)blocks + BLOCK_HEADER)
            return blocks;
        blocks = blocks->next;
    }
    return NULL;
}

void    unmap_page(t_pages *page, t_pages **head)
{
    if (page->prev == NULL)
    {
        *head = page->next;
        if (page->next)
            page->next->prev = NULL;
    }
    else if (page->next == NULL)
        page->prev->next = NULL;
    else
    {
        page->prev->next = page->next;
        page->next->prev = page->prev;
    }
    if (munmap(page, page->page_size) != 0)
        print_str_and_addr("Invalid munmap() on addr", page);
}

void    free(void *ptr)
{
    t_block *block;
    t_pages *page;

    if (ptr == NULL)
        return ;
    page = is_in_page(ptr);
    if (page == NULL)
        return ;
    block = block_exist(page, ptr);
    if (block == NULL)
        return ;
    if (block->is_free == 1)
    {
        ft_putstr_fd("Double free()\n", 2);
        return ;
    }
    block->is_free = 1;
    if (page->type & LARGE)
        unmap_page(page, &(data.large_pages));
}