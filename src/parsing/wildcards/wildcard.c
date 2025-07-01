#include "minishell.h"
#include "tools/sort.h"
#include "tools/list.h"
#include "tools/path.h"
#include "parsing.h"

static void	_apply_wildcard(t_alloc *alloc,
	t_token_list *item, t_str_list *result)
{
	t_token_list	*temp;
	t_str_list		*current;

	current = result;
	item->content->str = current->content;
	current = current->next;
	temp = item;
	while (current != NULL)
	{
		temp->next = (t_token_list *)lst_new(alloc,
				(void *)new_token(alloc, current->content, false, TOK_WORD));
		current = current->next;
		temp = temp->next;
	}
}

static void	_process_expanding(t_alloc *alloc, t_token_list *item)
{
	char		*pattern;
	char		*directory;
	t_str_list	*files;
	t_str_list	*result;

	result = NULL;
	pattern = path_get_filename(alloc, item->content->str);
	directory = path_get_path(alloc, item->content->str);
	if (str_len(directory) == 0)
		directory = str_dup(alloc, ".");
	if (path_check(directory, E_PATH_IS_DIRECTORY))
	{
		files = (t_str_list *)path_get_dir_content(alloc, directory);
		result = compute_pattern(alloc, files, pattern);
	}
	if (!result)
		return ;
	return (_apply_wildcard(alloc, item, result));
}

void	wildcard_expanding(t_alloc *alloc, t_token_list *token_list)
{
	t_token_list	*current;

	current = token_list;
	while (current)
	{
		if (str_chr(current->content->str, '*'))
			_process_expanding(alloc, current);
		current = current->next;
	}
}
