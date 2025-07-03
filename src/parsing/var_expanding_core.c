#include "parsing.h"

static bool	_handle_quotes(char c, char *quote_state)
{
	if (c == '\'' || c == '"')
	{
		if (*quote_state == '\0')
			*quote_state = c;
		else if (*quote_state == c)
			*quote_state = '\0';
		return (true);
	}
	return (false);
}

static bool	_handle_variable_expansion(t_ctx *ctx, t_token_list *current, \
	size_t index, char quote_state)
{
	char	*s;

	s = current->content->str;
	if (s[index] == '$' && quote_state != '\'')
	{
		if (process_expanding(ctx, &current->content->str, index + 1))
		{
			current->content->expanded = true;
			return (true);
		}
	}
	return (false);
}

static void	_process_token_content(t_ctx *ctx, t_token_list *current)
{
	size_t	index;
	char	*s;
	size_t	len;
	char	quote_state;

	index = 0;
	quote_state = '\0';
	while (current->content->type == TOK_WORD && !ctx->last_error_type)
	{
		s = current->content->str;
		len = str_len(s);
		if (index >= len)
			break ;
		if (_handle_quotes(s[index], &quote_state))
		{
			index++;
			continue ;
		}
		if (_handle_variable_expansion(ctx, current, index, quote_state))
			continue ;
		index++;
	}
}

void	var_expanding(t_ctx *ctx, t_token_list *token_list)
{
	t_token_list	*current;

	current = token_list;
	while (current)
	{
		_process_token_content(ctx, current);
		current = current->next;
	}
}
