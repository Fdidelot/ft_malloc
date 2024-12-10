#include "libft_malloc.h"

void    print_blocks(t_block *blocks)
{  
    while (blocks && blocks->next)
        blocks = blocks->next;
    while (blocks)
    {
        if (blocks->is_free == 0)
        {
            print_addr((char *)blocks + BLOCK_HEADER);
            print_str(" - ");
            print_addr((char *)blocks + blocks->size);
            print_str(" : ");
            print_number(blocks->size - BLOCK_HEADER);
            print_str(" bytes\n");
        }
        blocks = blocks->prev;
    }
}

void    print_pages_content(t_pages *pages)
{
    print_str_and_addr("", pages);
    while (pages)
    {
        print_blocks(pages->blocks);
        pages = pages->next;
    }
}

void    show_alloc_mem(void)
{
    if (data.tiny_pages)
    {
        print_str("TINY : ");
        print_pages_content(data.tiny_pages);
    }
    if (data.small_pages)
    {
        print_str("SMALL : ");
        print_pages_content(data.small_pages);
    }
    if (data.large_pages)
    {
        print_str("LARGE : ");
        print_pages_content(data.large_pages);
    }
    print_str("Total : ");
    print_number(data.total_size_alloc);
    print_str(" bytes\n");
}