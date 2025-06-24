#include "parsing.h"

t_redir_type	get_redir_type(char *s)
{
	if (str_equals(s, "<<"))
		return (E_REDIR_HEREDOC);
	if (str_equals(s, ">>"))
		return (E_REDIR_OUT_APPEND);
	if (str_equals(s, "<"))
		return (E_REDIR_IN);
	if (str_equals(s, ">"))
		return (E_REDIR_OUT_TRUNC);
	return (E_REDIR_LAST_INDEX);
}

t_token_type	get_token_type(char *s)
{
	if (str_equals(s, "|"))
		return (E_CONTROL_OPE);
	if (str_equals(s, "<<")
		|| str_equals(s, ">>")
		|| str_equals(s, "<")
		|| str_equals(s, ">"))
		return (E_REDIR_OPE);
	return (E_WORD);
}

t_token	*new_token(t_alloc *alloc, char *str, bool expanded, t_token_type type)
{
	t_token	*token;

	token = mem_alloc(alloc, sizeof(t_token));
	token->str = str;
	token->expanded = expanded;
	token->type = type;
	return (token);
}

static char	*_process_tokenize(t_ctx *ctx, char **input)
{
	size_t			index;
	char			*ret;

	while (*input && is_blank_meta(**input))
		(*input)++;
	if (!*input || str_len(*input) == 0)
		return (NULL);
	index = 0;
	if (**input == '|')
		ret = str_dup(*ctx->cmd, "|");
	else if (**input == '<' && *(*input + 1) == '<')
		ret = str_dup(*ctx->cmd, "<<");
	else if (**input == '>' && *(*input + 1) == '>')
		ret = str_dup(*ctx->cmd, ">>");
	else if (**input == '<')
		ret = str_dup(*ctx->cmd, "<");
	else if (**input == '>')
		ret = str_dup(*ctx->cmd, ">");
	else
	{
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
	}
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
