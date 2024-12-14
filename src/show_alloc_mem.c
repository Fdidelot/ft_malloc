#include "libft_malloc.h"

void    show_alloc_mem(void)
{
    print_str("Tiny :\n");
    t_pages *large = data.tiny_pages;
    t_block *blocks;
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
            print_str("]\n--------------\n");
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
            print_str("]\n--------------\n");
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
            print_str("]\n--------------\n");
            blocks = blocks->next;
        }
        large = large->next;
    }
}