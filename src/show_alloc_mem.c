#include "libft_malloc.h"

void    show_alloc_mem_ex(void)
{
    t_pages *large = data.tiny_pages;
    t_block *blocks;

    print_str("Tiny :\n");
    while (large)
    {
        print_str("page :");print_addr(large);
        print_str(", prev = ");print_addr(large->prev);
        print_str(", next = ");print_addr(large->next);
        print_str(", size = ");print_number(large->page_size);
        print_str(", left = ");print_number(large->space_left);
        print_str(",type = ");print_str(large->type & TINY ? "TINY" : "bizarre");
        print_str("\n");
        blocks = large->blocks;
        print_str(" Blocks:\n");
        while (blocks)
        {
            print_str(" addr = ");print_addr(blocks);
            print_str(", prev = ");print_addr(blocks->prev);
            print_str(", next = ");print_addr(blocks->next);
            print_str(", is_free = ");print_number(blocks->is_free);
            print_str(", size = ");print_number(blocks->size);
            print_str(", size_alloc = ");print_number(blocks->size - BLOCK_HEADER);
            print_str("\n");
            print_str(" Content in str: [");
            write(1, (void *)blocks + BLOCK_HEADER, blocks->size - BLOCK_HEADER);
            print_str("]\n");
            print_str(" Content in hexadecimal: [");
            print_hex((int *)((void *)blocks + BLOCK_HEADER), blocks->size - BLOCK_HEADER);
            print_str("]\n  --------------\n");
            blocks = blocks->next;
        }
        large = large->next;
    }
    print_str("\n\nSmall :\n");
    large = data.small_pages;
    while (large)
    {
        print_str("page :");print_addr(large);
        print_str(", prev = ");print_addr(large->prev);
        print_str(", next = ");print_addr(large->next);
        print_str(", size = ");print_number(large->page_size);
        print_str(", left = ");print_number(large->space_left);
        print_str(",type = ");print_str(large->type & SMALL ? "SMALL" : "bizarre");
        print_str("\n");
        blocks = large->blocks;
        print_str(" Blocks:\n");
        while (blocks)
        {
            print_str(" addr = ");print_addr(blocks);
            print_str(", prev = ");print_addr(blocks->prev);
            print_str(", next = ");print_addr(blocks->next);
            print_str(", is_free = ");print_number(blocks->is_free);
            print_str(", size = ");print_number(blocks->size);
            print_str(", size_alloc = ");print_number(blocks->size - BLOCK_HEADER);
            print_str("\n");
            print_str(" Content in str: [");
            write(1, (void *)blocks + BLOCK_HEADER, blocks->size - BLOCK_HEADER);
            print_str("]\n");
            print_str(" Content in hexadecimal: [");
            print_hex((int *)((void *)blocks + BLOCK_HEADER), blocks->size - BLOCK_HEADER);
            print_str("]\n  --------------\n");
            blocks = blocks->next;
        }
        large = large->next;
    }
    print_str("\n\nLarge :\n");
    large = data.large_pages;
    while (large)
    {
        print_str("page :");print_addr(large);
        print_str(", prev = ");print_addr(large->prev);
        print_str(", next = ");print_addr(large->next);
        print_str(", size = ");print_number(large->page_size);
        print_str(", left = ");print_number(large->space_left);
        print_str(",type = ");print_str(large->type & LARGE ? "LARGE" : "bizarre");
        print_str("\n");
        blocks = large->blocks;
        print_str(" Blocks:\n");
        while (blocks)
        {
            print_str(" addr = ");print_addr(blocks);
            print_str(", prev = ");print_addr(blocks->prev);
            print_str(", next = ");print_addr(blocks->next);
            print_str(", is_free = ");print_number(blocks->is_free);
            print_str(", size = ");print_number(blocks->size);
            print_str(", size_alloc = ");print_number(blocks->size - BLOCK_HEADER);
            print_str("\n");
            print_str(" Content in str: [");
            write(1, (void *)blocks + BLOCK_HEADER, blocks->size - BLOCK_HEADER);
            print_str("]\n");
            print_str(" Content in hexadecimal: [");
            print_hex((int *)((void *)blocks + BLOCK_HEADER), blocks->size - BLOCK_HEADER);
            print_str("]\n  --------------\n");
            blocks = blocks->next;
        }
        large = large->next;
    }
}

size_t  display_block(t_block *blocks)
{
    size_t  total = 0;

    while (blocks)
    {
        if (blocks->is_free == 0)
        {
            print_addr((void *)blocks + BLOCK_HEADER);
            print_str(" - ");
            print_addr((void *)blocks + blocks->size);
            print_str(" : ");
            print_number(blocks->size - BLOCK_HEADER);
            print_str(" bytes\n");
            total += blocks->size - BLOCK_HEADER;
        }
        blocks = blocks->next;
    }
    return total;
}

size_t  display_page(t_pages *page)
{
    size_t total = 0;
    
    while (page)
    {
        print_addr(page);
        print_str("\n");
        total += display_block(page->blocks);
        page = page->next;
    }
    return total;
}

void    show_alloc_mem(void)
{
    size_t total = 0;
    print_str("TINY : ");
    total += display_page(data.tiny_pages);
    print_str("SMALL : ");
    total += display_page(data.small_pages);
    print_str("LARGE : ");
    total += display_page(data.large_pages);
    print_str("Total : ");
    print_number(total);
    print_str(" bytes\n");
}