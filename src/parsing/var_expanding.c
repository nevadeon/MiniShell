#include "parsing.h"
#include <errno.h>
#include "num.h"
#include "char.h"

static bool	_is_var_name_valid(char *str)
{
	size_t	index;

	index = 0;
	if ((str)[index] != '_' && !char_isalpha((str)[index]))
		return (false);
	while (char_isalnum((str)[index]) || (str)[index] == '_')
		index++;
	return (index == str_len(str));
}

static t_replace	*_replace_special_parameters(t_ctx *ctx, \
	char **s, size_t index)
{
	t_replace	*ret;

	if ((*s)[index] == '?' || (*s)[index] == '$')
	{
		ret = mem_alloc(*ctx->cmd, sizeof(t_replace));
		if ((*s)[index] == '?')
			ret->rep = num_itoa(*ctx->cmd, ctx->last_exit_code);
		else if ((*s)[index] == '$')
			ret->rep = num_itoa(*ctx->cmd, getpid());
		ret->str = s;
		ret->start = index - 1;
		ret->end = index + 1;
		return (ret);
	}
	return (NULL);
}

static t_replace	*_replace_bracketed_variable(t_ctx *ctx, char **s, size_t index)
{
	t_replace	*ret;
	char		*var_name;

	if ((*s)[index] == '{')
	{
		ret = mem_alloc(*ctx->cmd, sizeof(t_replace));
		ret->start = index - 1;
		ret->str = s;
		if (!str_escape(*s, &index, '{', '}'))
			return (throw_error(ctx, ERR_UNCLOSED, "{"), NULL);
		ret->end = index;
		var_name = str_extract(*ctx->cmd, *ret->str, ret->start + 2, ret->end - 1);
		if (!_is_var_name_valid(var_name))
			return (throw_error(ctx, ERR_BAD_SUBSTITUTION, *s), NULL);
		ret->rep = env_get_var_value(*ctx->env, var_name);
		return (ret);
	}
	return (NULL);
}

static t_replace	*_replace_variable(t_ctx *ctx, char **s, \
	size_t index)
{
	t_replace	*ret;
	char		*var_name;

	if ((*s)[index] != '_' && !char_isalpha((*s)[index]))
		return (NULL);
	ret = mem_alloc(*ctx->cmd, sizeof(ret));
	ret->str = s;
	ret->start = index - 1;
	while (char_isalnum((*s)[index]) || (*s)[index] == '_')
		index++;
	ret->end = index;
	var_name = str_extract(*ctx->cmd, *ret->str, ret->start + 1, ret->end);
	ret->rep = env_get_var_value(*ctx->env, var_name);
	return (ret);
}

static void	_process_expanding(t_ctx *ctx, t_token *token, size_t index)
{
	char		**s;
	t_replace	*var;

	s = &token->str;
	var = NULL;
	var = _replace_special_parameters(ctx, s, index);
	if (!var && !ctx->last_error_type)
		var = _replace_bracketed_variable(ctx, s, index);
	if (!var && !ctx->last_error_type)
		var = _replace_variable(ctx, s, index);
	if (var && !ctx->last_error_type)
	{
		str_replace(*ctx->cmd, *var);
		if (str_ncmp(token->str, "\"", 1) \
			&& str_ncmp(token->str + str_len(token->str) - 1, "\"", 1))
			token->expanded = true;
	}
}

void	var_expanding(t_ctx *ctx, t_token_list *token_list)
{
	t_token_list	*current;
	size_t			index;

	current = token_list;
	while (current)
	{
		index = 0;
		while (current->content->type == E_WORD \
			&& current->content->str[index] && !ctx->last_error_type)
		{
			str_escape(current->content->str, &index, '\'', '\'');
			if (current->content->str[index] == '$')
				_process_expanding(ctx, current->content, index + 1);
			index++;
		}
		current = current->next;
	}
}
