#include "libft_malloc.h"

void    push_page_front(t_pages *page, t_pages **head)
{
    page->next = *head;
    page->prev = NULL;
    if (*head)
        (*head)->prev = page;
    *head = page;
}

t_pages *create_page(size_t size)
{
    t_pages *new_page;

    new_page = mmap(NULL, size, PROT_READ | PROT_WRITE
                                   , MAP_PRIVATE | MAP_ANONYMOUS
                                   , -1, 0);
    if (new_page == MAP_FAILED)
    {
        print_str("mmap() failed.\n");
        return (NULL);
    }
    ft_memset(new_page, 0, PAGE_HEADER);
    new_page->page_size = size;
    new_page->space_left = size - PAGE_HEADER;
    return (new_page);
}

t_pages *available_page(size_t size, t_pages **head, int type)
{
    t_pages *pages = *head;
    size_t  page_size;

    while (pages)
    {
        if (pages->space_left >= size)
            return pages;
        pages = pages->next;
    }
    if (type & SMALL)
        page_size = SMALL_PAGE_SIZE;
    else if (type & TINY)
        page_size = TINY_PAGE_SIZE;
    pages = create_page(page_size);
    if (type & SMALL)
        pages->type = SMALL;
    else if (type & TINY)
        pages->type = TINY;
    push_page_front(pages, head);
    return pages;
}

t_pages *get_page(size_t size, int type)
{
    t_pages *page = NULL;

    if (type & LARGE)
    {
        page = create_page(align_size(size + PAGE_HEADER, PAGE_SIZE));
        if (page == NULL)
            return NULL;
        page->type = LARGE;
        push_page_front(page, &(data.large_pages));
    }
    else if (type & SMALL)
        page = available_page(size, &(data.small_pages), type);
    else if (type & TINY)
        page = available_page(size, &(data.tiny_pages), type);
    return page;
}