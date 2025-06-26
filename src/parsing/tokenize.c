#include "parsing.h"

static char	*tokenize_meta(t_ctx *ctx, char **input)
{
	if (**input == '|')
		return (str_dup(*ctx->cmd, "|"));
	else if (**input == '<' && *(*input + 1) == '<')
		return (str_dup(*ctx->cmd, "<<"));
	else if (**input == '>' && *(*input + 1) == '>')
		return (str_dup(*ctx->cmd, ">>"));
	else if (**input == '<')
		return (str_dup(*ctx->cmd, "<"));
	else if (**input == '>')
		return (str_dup(*ctx->cmd, ">"));
	return (NULL);
}

static char	*_process_tokenize(t_ctx *ctx, char **input)
{
	size_t	index;
	char	*ret;

	while (*input && is_blank_meta(**input))
		(*input)++;
	if (!*input || str_len(*input) == 0)
		return (NULL);
	ret = tokenize_meta(ctx, input);
	if (ret)
		return (*input += str_len(ret), ret);
	index = 0;
	while ((*input)[index] && !is_meta((*input)[index]))
	{
		if (!str_escape(*input, &index, '"', '"'))
			return (throw_error(ctx, ERR_UNCLOSED, "\""), NULL);
		if (!str_escape(*input, &index, '\'', '\''))
			return (throw_error(ctx, ERR_UNCLOSED, "'"), NULL);
		str_escape(*input, &index, '{', '}');
		if ((*input)[index] && !is_meta((*input)[index]))
			index++;
	}
	ret = str_extract(*ctx->cmd, *input, 0, index);
	*input += str_len(ret);
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
		lst_add_back((t_list **)&token_list, lst_new(*ctx->cmd, (void *)tok));
		word = _process_tokenize(ctx, input);
	}
	return (token_list);
}
