#include "minishell.h"
#include "sort.h"
#include "list.h"

static t_dir	_explore_directory(char *path)
{
	t_list			*list;
	struct dirent	*ent;
	struct stat		st;
	int				count;
	DIR				*rep;
	char			*full_path;

	count = 0;
	rep = opendir(path);
	list = NULL;
	if (rep == NULL)
	{
		perror("Erreur lors de l'ouverture du répertoire");
		exit(EXIT_FAILURE); // TODO HANDLE ERROR
	}
	while ((ent = readdir(rep)) != NULL)
	{
		if (ent->d_name[0] == '.' && (ent->d_name[1] == '\0' || (ent->d_name[1] == '.' && ent->d_name[2] == '\0')))
			continue ;
		full_path = str_vjoin(E_LFT_TASK, 3, path, "/", ent->d_name);
		if (stat(full_path, &st) == 0)
		{
			count++;
			lst_add_back(&list, lst_new(E_LFT_TASK, strdup(ent->d_name)));
		}
	}
	closedir(rep);
	return ((t_dir){.head = ft_qsort(list, ascii_sort), .nb_dir = count});
}

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

static t_strlist	*_compute_pattern(t_dir dir, char *pattern)
{
	t_list		*current;
	char		*file_n;
	t_strlist	*rep;

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
			lst_add_back((t_list **)&rep, lst_new(E_LFT_TASK, (char *)file_n));
		current = current->next;
	}
	return (rep);
}

static char	*_get_directory(char *word)
{
	size_t	index;
	size_t	last_slash_index;
	char	*word_cpy;

	last_slash_index = 0;
	index = 0;
	word_cpy = mem_alloc(E_LFT_TASK, (str_len(word) + 1) * sizeof(char));
	word_cpy = str_memcpy(word_cpy, word, str_len(word));
	while (word[index])
	{
		if (word[index] == '/')
			last_slash_index = index;
		index++;	
	}
	if (last_slash_index == 0)
		return (".");
	word_cpy[last_slash_index] = '\0';
	return (word_cpy);
}

static char	*_get_pattern(char *word)
{
	char	*pattern;

	pattern = str_rchr(word, '/');
	if (str_equals(pattern, word))
		return (word);
	return (pattern + 1);
}

void	expand_wildcard(char **input, char **word)
{
	size_t		index;
	t_strlist	*w;
	t_dir		dir;
	char		*files;

	index = 0;
	while ((*word)[index] && (*word)[index] != '*')
		index++;
	if ((*word)[index] != '*')
		return ;
	index = 0;
	while ((*word)[index] && !isspace((*word)[index]))
		index++;
	dir = _explore_directory(_get_directory(*word));
	w = _compute_pattern(dir, _get_pattern(*word));
	files = "";
	*word = files;
	if (w)
	{
		*word = w->content;
		w = w->next;
	}
	while (w)
	{
		files = str_vjoin(E_LFT_TASK, 3, files, " ", w->content);
		w = w->next;
	}
	str_replace(E_LFT_TASK, (t_replace){input, files, 0, 0});
}
