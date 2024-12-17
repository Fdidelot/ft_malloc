# include "libft_malloc.h"
# include <stdio.h>

int main(void)
{
    char *ptr0, *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9;

    ptr0 = malloc(90);
    ptr0[0] = 'a';
    ptr1 = malloc(77);
    ptr1[0] = 'b';
    ptr2 = malloc(2);
    ptr2[0] = 'c';

    ptr3 = malloc(2000);
    ptr3[0] = 'd';
    ptr4 = malloc(1024);
    ptr4[0] = 'e';
    ptr4[888] = '8';
    ptr5 = malloc(510);
    ptr5[0] = 'f';

    ptr6 = malloc(4096);
    ptr6[0] = 'g';
    ptr7 = malloc(12200);
    ptr7[0] = 'h';
    ptr8 = malloc(6666);
    ptr8[0] = 'i';


    free(ptr1);
    free(ptr4);
    free(ptr7);
    ptr5 = realloc(ptr5, 100);
    ptr5[0] = 'j';
    show_alloc_mem();
    // show_alloc_mem_ex();

    printf("Tiny size = %ld, Tiny page = %ld\n", TINY_ALLOC, TINY_PAGE_SIZE);
    printf("(Tiny size + Metadata) * 100 = %ld\n", (TINY_ALLOC + BLOCK_HEADER) * 100);
    printf("Small size = %ld, Small page = %ld\n", SMALL_ALLOC, SMALL_PAGE_SIZE);
    printf("(Small size + Metadata) * 100 = %ld\n", (SMALL_ALLOC + BLOCK_HEADER) * 100);
    return 0;
}