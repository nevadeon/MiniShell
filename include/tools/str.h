#ifndef STR_H
# define STR_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "allocator.h"

#define GNL_BUFFER_SIZE 4096

typedef enum e_lifetime	t_lifetime;

typedef struct s_replace
{
	char	**str;
	char	*rep;
	int		start;
	int		end;
}	t_replace;

int		str_ncmp(char *s1, char *s2, size_t n);
bool	str_equals(const char *str1, const char *str2);
size_t	str_len(const char *str);
void	*str_memcpy(void *dst, void *src, size_t n);
char	*str_dup(t_alloc *alloc, char *s);
char	*str_vjoin(t_alloc *alloc, size_t nb_args, ...);
void	str_replace(t_alloc *alloc, t_replace data);
int		str_cmp(const char *s1, const char *s2);
char	**str_split(t_alloc *alloc, char const *s, char c);
char	*str_chr(const char *s, int c);
char	*str_rchr(const char *s, int c);
int		str_atoi(const char *s);
size_t	str_putfd(const char *s, int fd);
size_t	str_clen(const char *str, char c, bool include_char);
char	*str_gnl(int fd);

#endif
