#ifndef STR_H
# define STR_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdarg.h>
# include "mem.h"

typedef struct	s_replace
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
char	*str_vjoin(t_lifetime lft, size_t nb_args, ...);
void	str_replace(t_lifetime lft, t_replace data);

#endif
