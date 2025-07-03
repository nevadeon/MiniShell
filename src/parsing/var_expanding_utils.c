#include "parsing.h"
#include <errno.h>
#include "tools/num.h"
#include "tools/char.h"

static t_replace	*\
	_replace_special_parameters(t_ctx *ctx, char **s, size_t index)
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

static t_replace	*\
	_replace_bracketed_variable(t_ctx *ctx, char **s, size_t index)
{
	t_replace	*r;
	char		*var_name;

	if ((*s)[index] == '{')
	{
		r = mem_alloc(*ctx->cmd, sizeof(t_replace));
		r->start = index - 1;
		r->str = s;
		if (!str_escape(*s, &index, '{', '}'))
		{
			throw_error(ctx, E_UNCLOSED, "{");
			return (NULL);
		}
		r->end = index;
		var_name = str_extract(*ctx->cmd, *r->str, r->start + 2, r->end - 1);
		if (!is_var_name_valid(var_name))
		{
			throw_error(ctx, E_BAD_SUBSTITUTION, *s);
			return (NULL);
		}
		r->rep = env_get_var_value(*ctx->env, var_name);
		return (r);
	}
	return (NULL);
}

static t_replace	*\
	_replace_variable(t_ctx *ctx, char **s, size_t index)
{
	t_replace	*ret;
	char		*var_name;

	if ((*s)[index] != '_' && !char_isalpha((*s)[index]))
		return (NULL);
	ret = mem_alloc(*ctx->cmd, sizeof(t_replace));
	ret->str = s;
	ret->start = index - 1;
	while (char_isalnum((*s)[index]) || (*s)[index] == '_')
		index++;
	ret->end = index;
	var_name = str_extract(*ctx->cmd, *ret->str, ret->start + 1, ret->end);
	ret->rep = env_get_var_value(*ctx->env, var_name);
	return (ret);
}

bool	process_expanding(t_ctx *ctx, char **str_ptr, size_t index)
{
	t_replace	*rep;
	size_t		len;
	bool		expanded;

	rep = NULL;
	expanded = false;
	rep = _replace_special_parameters(ctx, str_ptr, index);
	if (!rep && !ctx->last_error_type)
		rep = _replace_bracketed_variable(ctx, str_ptr, index);
	if (!rep && !ctx->last_error_type)
		rep = _replace_variable(ctx, str_ptr, index);
	if (rep && !ctx->last_error_type)
	{
		str_replace(*ctx->cmd, *rep);
		len = str_len(*str_ptr);
		if (len > 0
			&& (*str_ptr)[0] != '"'
			&& (*str_ptr)[len - 1] != '"')
		{
			expanded = true;
		}
	}
	return (expanded);
}
