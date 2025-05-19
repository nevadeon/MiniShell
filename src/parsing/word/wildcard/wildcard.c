#include "minishell.h"
#include "sort.h"
#include "list.h"
#include "path.h"
#include "parsing.h"

static bool	_has_to_expand(char *word)
{
	size_t		index;

	index = 0;
	while (word[index] && word[index] != '*')
		index++;
	return (word[index] == '*');
}

static void	_apply_wildcard(t_allocator *alloc, char **input, char **word, t_str_list *result)
{
	char		*files;

	files = "";
	*word = files;
	if (result)
	{
		*word = result->content;
		result = result->next;
	}
	while (result)
	{
		files = str_vjoin(alloc, 3, files, " ", result->content);
		result = result->next;
	}
	str_replace(alloc, (t_replace){input, files, 0, 0});
}

void	expand_wildcard(t_allocator *alloc, char **input, char **word)
{
	t_str_list	*result;
	char		*pattern;
	char		*directory;
	t_str_list	*files;

	if (!_has_to_expand(*word))
		return ;
	pattern = path_get_filename(alloc, *word);
	directory = path_get_path(alloc, *word);
	result = NULL;
	if (str_len(directory) == 0)
		directory = str_dup(alloc, ".");
	if (path_check(directory, E_PATH_IS_DIRECTORY))
	{
		files = (t_str_list *)path_get_dir_content(alloc, directory);
		result = compute_pattern(alloc, files, pattern);
	}
	if (!result)
		fprintf(stderr, "No match found: %s", *word);
	_apply_wildcard(alloc, input, word, result);
}
