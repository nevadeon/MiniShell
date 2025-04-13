#include "minishell.h"
#include "sort.h"
#include "list.h"

static t_dir	_explore_directory(void)
{
	t_list			*list;
	struct dirent	*ent;
	struct stat		st;
	int				count = 0;
	DIR				*rep;
	
	rep = opendir(".");
	list = NULL;
	if (rep == NULL)
	{
		perror("Erreur lors de l'ouverture du répertoire");
		exit(EXIT_FAILURE);
	}
	while ((ent = readdir(rep)) != NULL)
	{
		if (ent->d_name[0] == '.' && (ent->d_name[1] == '\0' || (ent->d_name[1] == '.' && ent->d_name[2] == '\0')))
			continue;
		if (stat(ent->d_name, &st) == 0)
		{
			count++;
			lst_add_back(&list, lst_new(E_LFT_TASK, strdup(ent->d_name)));
		}
	}
	closedir(rep);
	return ((t_dir) {.head = ft_qsort(list, ascii_sort), .nb_dir = count});
}

static bool	_match(const char *pattern, const char *str)
{
	if (*pattern == '\0')
		return *str == '\0';
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

static char	*_compute_pattern(char *pattern)
{
	t_dir	dir;
	t_list	*current;
	char	*file_n;
	char	*rep;

	dir = _explore_directory();
	current = dir.head;
	rep = NULL;
	while (current)
	{
		file_n = current->content;
		if (pattern[0] != '.' && file_n[0] == '.')
		{
			current = current->next;
			continue ;
		}
		if (_match(pattern, file_n))
		{
			if (!rep)
				rep = file_n;
			else
				rep = str_vjoin(E_LFT_TASK, 3, rep, " ", file_n);
		}
		current = current->next;
	}
	return (rep);
}

void	expand_wildcard(char **word)
{
	size_t	index;
	bool	expand_double;
	bool	expand_single;
	char	*w;
	
	index = 0;
	expand_double = true;
	expand_single = true;
	while ((*word)[index] && !isspace((*word)[index]) && (*word)[index] != '*')
	{
		if ((*word)[index] == '\'')
			expand_single = !expand_single;
		if ((*word)[index] == '"')
			expand_double = !expand_double;
		index++;
	}
	if ((*word)[index] != '*' || !expand_double || !expand_single)
		return ;
	index = 0;
	while ((*word)[index] && !isspace((*word)[index]))
		index++;
	w = _compute_pattern(*word);
	if (!w)
		w = "";
	str_replace(E_LFT_TASK, (t_replace) {word, w, 0, index });
}
