#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>
# include <sys/mman.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/resource.h>

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

void	print_hexa(char *ptr);

#endif