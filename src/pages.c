#include "libft_malloc.h"

t_pages *push_page_front(t_pages *page, t_pages **head)
{
    page->next = *head;
    page->prev = NULL;
    if (*head)
        (*head)->prev = page;
    return page;
}

size_t  get_page_size(size_t size_alloc, int type)
{
    size_t page_size;

    if (type & TINY)
        page_size = TINY_PAGE_SIZE;
    else if (type & SMALL)
        page_size = SMALL_PAGE_SIZE;
    else if (type & LARGE)
        page_size = align_size(size_alloc + PAGE_HEADER, PAGE_SIZE);
    return (page_size);
}

t_pages *create_page(size_t size_alloc)
{
    size_t  page_size = get_page_size(size_alloc, data.type);
    t_pages *new_page;

    new_page = mmap(NULL, page_size, PROT_READ | PROT_WRITE
                                   , MAP_PRIVATE | MAP_ANONYMOUS
                                   , -1, 0);
    if (new_page == MAP_FAILED)
    {
        print_str("mmap() failed.\n");
        return (NULL);
    }
    ft_memset(new_page, 0, PAGE_HEADER);
    new_page->page_size = page_size;
    new_page->space_left = page_size - PAGE_HEADER;
    data.total_pages_size += page_size;
    return (new_page);
}

t_pages *get_large_page(size_t size)
{
    t_pages *page;

    page = create_page(size);
    if (page == NULL)
        return NULL;
    data.large_pages = push_page_front(page, &(data.large_pages));
    return page;
}

t_pages *get_tiny_page(size_t size)
{
    t_pages *tmp_page = data.tiny_pages;

    while (tmp_page)
    {
        if (tmp_page->space_left > size)
            return (tmp_page);
        tmp_page = tmp_page->next;
    }
    tmp_page = create_page(size);
    if (tmp_page)
        data.tiny_pages = push_page_front(tmp_page, &(data.tiny_pages));
    return (tmp_page);
}

t_pages *get_small_page(size_t size)
{
    t_pages *tmp_page = data.small_pages;

    while (tmp_page)
    {
        if (tmp_page->space_left >= size)
            return (tmp_page);
        tmp_page = tmp_page->next;
    }
    tmp_page = create_page(size);
    if (tmp_page)
        data.small_pages = push_page_front(tmp_page, &(data.small_pages));
    return (tmp_page);
}

t_pages *get_pages(size_t size, int type)
{
    t_pages *page;

    if (type & LARGE)
        page = get_large_page(size);
    else if (type & TINY)
        page = get_tiny_page(size);
    else if (type & SMALL)
        page = get_small_page(size);
    return (page);
}