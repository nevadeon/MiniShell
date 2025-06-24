#include "parsing.h"
#include <errno.h>
#include "num.h"
#include "char.h"

static t_replace	*_replace_special_parameters(t_alloc *alloc, \
	char **s, size_t index)
{
	t_replace	*ret;

	if ((*s)[index] == '?' || (*s)[index] == '$')
	{
		ret = mem_alloc(alloc, sizeof(t_replace));
		if ((*s)[index] == '?')
			ret->rep = num_itoa(alloc, errno);
		else if ((*s)[index] == '$')
			ret->rep = num_itoa(alloc, getpid());
		ret->str = s;
		ret->start = index - 1;
		ret->end = index + 1;
		return (ret);
	}
	return (NULL);
}

static t_replace	*_replace_bracketed_variable(t_alloc *alloc, char **s, \
	size_t index)
{
	t_replace	*ret;
	char		*var_name;

	if ((*s)[index] == '{')
	{
		ret = mem_alloc(alloc, sizeof(t_replace));
		ret->start = index - 1;
		ret->str = s;
		str_escape(*s, &index, '{', '}');
		ret->end = index;
		var_name = str_extract(alloc, *ret->str, ret->start + 2, ret->end - 1);
		ret->rep = env_get_var_value(var_name, NULL);
		return (ret);
	}
	return (NULL);
}

static t_replace	*_replace_variable(t_alloc *alloc, char **s, \
	size_t index)
{
	t_replace	*ret;
	char		*var_name;

	if ((*s)[index] != '_' && !char_isalpha((*s)[index]))
		return (NULL);
	ret = mem_alloc(alloc, sizeof(ret));
	ret->str = s;
	ret->start = index - 1;
	while (char_isalnum((*s)[index]) || (*s)[index] == '_')
		index++;
	ret->end = index;
	var_name = str_extract(alloc, *ret->str, ret->start + 1, ret->end);
	ret->rep = env_get_var_value(var_name, NULL);
	return (ret);
}

static void	_process_expanding(t_alloc *alloc, t_token *token, size_t index)
{
	char		**s;
	t_replace	*var;

	s = &token->str;
	var = NULL;
	var = _replace_special_parameters(alloc, s, index);
	if (!var)
		var = _replace_bracketed_variable(alloc, s, index);
	if (!var)
		var = _replace_variable(alloc, s, index);
	if (var)
	{
		str_replace(alloc, *var);
		if (str_ncmp(token->str, "\"", 1) \
			&& str_ncmp(token->str + str_len(token->str) - 1, "\"", 1))
			token->expanded = true;
	}
}

void	var_expanding(t_alloc *alloc, t_token_list *token_list)
{
	t_token_list	*current;
	size_t			index;

	current = token_list;
	while (current)
	{
		index = 0;
		while (current->content->type == E_WORD \
			&& current->content->str[index])
		{
			str_escape(current->content->str, &index, '\'', '\'');
			if (current->content->str[index] == '$')
				_process_expanding(alloc, current->content, index + 1);
			index++;
		}
		current = current->next;
	}
}
