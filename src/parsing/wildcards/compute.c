#include "minishell.h"
#include "path.h"

static bool	_match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (true);
		while (*str)
		{
			if (_match(pattern, str))
				return (true);
			str++;
		}
		return (false);
	}
	else
	{
		if (*pattern == *str)
			return (_match(pattern + 1, str + 1));
		else
			return (false);
	}
}

t_str_list	*compute_pattern(t_alloc *alloc, t_str_list *files, char *pattern)
{
	char		*file_n;
	t_str_list	*rep;
	t_str_list	*current;

	current = files;
	rep = NULL;
	while (current)
	{
		file_n = path_get_filename(alloc, current->content);
		if (pattern[0] != '.' && file_n[0] == '.')
		{
			current = current->next;
			continue ;
		}
		if (_match(pattern, file_n))
			lst_add_back((t_list **)&rep,
				lst_new(alloc, current->content));
		current = current->next;
	}
	return (rep);
}
