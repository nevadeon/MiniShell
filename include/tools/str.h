#ifndef STR_H
# define STR_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include "allocators/allocator.h"

# define GNL_BUFFER_SIZE 4096

typedef enum e_lifetime	t_lifetime;

typedef struct s_replace
{
	char	**str;
	char	*rep;
	int		start;
	int		end;
}	t_replace;

int		str_ncmp(const char *s1, const char *s2, size_t n);
bool	str_equals(const char *str1, const char *str2);
size_t	str_len(const char *str);
void	*str_memcpy(void *dst, void *src, size_t n);
char	*str_dup(t_alloc *alloc, char *s);
char	*str_vjoin(t_alloc *alloc, size_t nb_args, ...);
int		str_replace(t_alloc *alloc, t_replace d);
int		str_cmp(const char *s1, const char *s2);
char	**str_split(t_alloc *alloc, char const *s, char c);
char	*str_chr(const char *s, int c);
char	*str_rchr(const char *s, int c);
int		str_atoi(const char *s);
size_t	str_putfd(const char *s, int fd);
size_t	str_clen(const char *str, char c, bool include_char);
char	*str_gnl(t_alloc *alloc, int fd);
bool	str_escape(char *s, size_t *index, char start, char end);
bool	str_escape_with_context(char *s, size_t *index, char quote_char);
char	*str_extract(t_alloc *alloc, char *s, size_t start, size_t end);
bool	str_contains(const char *str, const char *substr);
void	*str_memset(void *s, int c, size_t n);

/**
 * @brief return an allocated string with the content between each delim.
 * The content can be empty;
 * @warning DOES NOT USE IT LIKE STANDARD STRTOK FUNCTION. Modify the str string
 * @param `alloc` The allocator.
 * @param `str` A string ptr.
 * @param `delim` An array of delimiters.
 * @return the content between 2 delimiters.
 */
char	*str_tok(t_alloc *alloc, char **str, const char *delim);

#endif
