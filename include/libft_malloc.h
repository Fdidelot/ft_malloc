#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/mman.h>

// Page size and limit definition
# define MAX_ALLOCATION_SIZE (1L << 30)  // 1GB
# define PAGE_SIZE sysconf(_SC_PAGESIZE)

# define TINY_PAGE_SIZE PAGE_SIZE * 4 // N 16ko
# define SMALL_PAGE_SIZE PAGE_SIZE * 64 // M 256ko

# define TINY_ALLOC TINY_PAGE_SIZE / 128 // n 128o
# define SMALL_ALLOC SMALL_PAGE_SIZE / 128 // m 2ko

// Header size
# define BLOCK_HEADER sizeof(t_block)
# define PAGE_HEADER sizeof(t_pages)

// Type definition
enum
{
    TINY = 1 << 0,
    SMALL = 1 << 1,
    LARGE = 1 << 2
};

// Data structures
typedef struct  s_block
{
    size_t          size;
    bool            is_free;
    struct s_block  *next;
    struct s_block  *prev;
}               t_block;

typedef struct  s_pages
{
    int             type;
    size_t          page_size;
    size_t          space_left;
    t_block         *blocks;
    struct s_pages  *next;
    struct s_pages  *prev;
}               t_pages;

typedef struct  s_data
{
    t_pages     *tiny_pages;
    t_pages     *small_pages;
    t_pages     *large_pages;
}               t_data;

// Global Data def
extern  t_data  data;

// Malloc core functions
void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);
void    show_alloc_mem(void);

// Page management
t_pages  *get_page(size_t size, int type);
t_pages *is_in_page(void *ptr);

// Block management
t_block *get_block(size_t size, t_pages *page);
t_block *block_exist(t_pages *page, void *ptr);
t_block *new_block(size_t size, void *addr);
void    create_sub_block(t_block *block, size_t size);

// Print functions
void    print_str_and_addr(char *str, void *addr);
void    print_str_and_number(char *str, size_t nb);
void    print_addr(void *addr);
void    print_str(char *str);
void    print_number(size_t nb);
void	ft_putnbr_base_fd(size_t n, int base, int fd);
void	ft_putstr_fd(char *s, int fd);
void    print_hex(int *ptr, size_t size);

// Tools function
size_t	ft_strlen(const char *s);
void    *ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int     get_type(size_t size);
size_t  align_size(size_t size, size_t alignment);

#endif