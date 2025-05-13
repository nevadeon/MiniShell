#ifndef STR_H
# define STR_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdarg.h>

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
char	*str_dup(t_lifetime lft, char *s);
char	*str_vjoin(t_lifetime lft, size_t nb_args, ...);
void	str_replace(t_lifetime lft, t_replace data);
int		str_cmp(const char *s1, const char *s2);
char	**str_split(t_lifetime lft, char const *s, char c);
char	*str_chr(const char *s, int c);
char	*str_rchr(const char *s, int c);

#endif
