#include "parsing.h"

static char	*tokenize_meta(t_ctx *ctx, char **input)
{
	if (**input == '|')
		return (str_dup(*ctx->cmd, "|"));
	else if (**input == '<' && *(*input + 1) == '<')
		return (*input += 2, str_dup(*ctx->cmd, "<<"));
	else if (**input == '>' && *(*input + 1) == '>')
		return (*input += 2, str_dup(*ctx->cmd, ">>"));
	else if (**input == '<')
		return ((*input)++, str_dup(*ctx->cmd, "<"));
	else if (**input == '>')
		return ((*input)++, str_dup(*ctx->cmd, ">"));
	else if (**input == '|')
		return ((*input)++, str_dup(*ctx->cmd, "|"));
	return (NULL);
}

static bool	handle_quote_char(char **input, size_t *index, t_ctx *ctx)
{
	char	quote;

	quote = (*input)[*index];
	if (quote == '"')
		return (str_escape(*input, index, '"', '"')
			|| (throw_error(ctx, E_UNCLOSED, "\""), false));
	if (quote == '\'')
		return (str_escape(*input, index, '\'', '\'')
			|| (throw_error(ctx, E_UNCLOSED, "'"), false));
	if (quote == '{')
		return (str_escape(*input, index, '{', '}'), true);
	return (false);
}

static char	*_process_tokenize(t_ctx *ctx, char **input)
{
	size_t	index;
	char	*ret;

	while (**input && is_blank_meta(**input))
		(*input)++;
	if (!**input)
		return (NULL);
	ret = tokenize_meta(ctx, input);
	if (ret)
		return (ret);
	index = 0;
	while ((*input)[index] && !is_meta((*input)[index]))
	{
		if (handle_quote_char(input, &index, ctx))
			continue ;
		if (!ctx->last_error_type)
			index++;
		else
			return (NULL);
	}
	ret = str_extract(*ctx->cmd, *input, 0, index);
	*input += index;
	return (ret);
}

t_token_list	*tokenize(t_ctx *ctx, char **input)
{
	t_token_list	*token_list;
	t_token			*tok;
	char			*word;

	token_list = NULL;
	word = _process_tokenize(ctx, input);
	while (word)
	{
		if (ctx->last_error_type)
			return (NULL);
		tok = new_token(*ctx->cmd, word, false, get_token_type(word));
		if (!tok)
			return (NULL);
		lst_add_back((t_list **)&token_list, lst_new(*ctx->cmd, (void *)tok));
		word = _process_tokenize(ctx, input);
	}
	return (token_list);
}
