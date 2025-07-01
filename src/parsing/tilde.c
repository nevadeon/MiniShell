/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/07/01 13:24:59 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>

static char	*_get_usr_directory(t_alloc *alloc, char *user_name)
{
	char	*line;
	int		fd;
	int		index;
	char	*sep_line;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = str_gnl(alloc, fd);
	while (line)
	{
		sep_line = str_tok(alloc, &line, ":");
		if (!sep_line || str_equals(sep_line, user_name))
		{
			index = -1;
			while (line && ++index < 5)
				sep_line = str_tok(alloc, &line, ":");
			return (close(fd), sep_line);
		}
		line = str_gnl(alloc, fd);
	}
	close (fd);
	return (NULL);
}

static char	*_handle_tilde_expanding(t_ctx *ctx, char *str)
{
	char	*usr_name;
	int		len;

	if (str[1] == '\0' || str[1] == '/')
		return (env_get_var_value(*ctx->env, "HOME"));
	if (str[1] == '+')
		return (env_get_var_value(*ctx->env, "PWD"));
	if (str[1] == '-')
		return (env_get_var_value(*ctx->env, "OLDPWD"));
	len = str_clen(str, '/', false);
	usr_name = str_extract(*ctx->cmd, str, 1, len);
	return (_get_usr_directory(*ctx->cmd, usr_name));
}

static void	_process_tilde_token(t_ctx *ctx, t_token_list *token)
{
	t_replace	rep;
	char		**content;

	content = &token->content->str;
	if (!(*content) || (*content)[0] != '~')
		return ;
	rep.str = content;
	rep.start = 0;
	rep.end = str_clen(*content, '/', false);
	rep.rep = _handle_tilde_expanding(ctx, *content);
	if (rep.rep)
	{
		str_replace(*ctx->cmd, rep);
		token->content->expanded = true;
	}
	return ;
}

void	tilde_expanding(t_ctx *ctx, t_token_list *token_list)
{
	t_token_list	*current;

	current = token_list;
	while (current)
	{
		if (current->content->type == TOK_WORD)
			_process_tilde_token(ctx, current);
		current = current->next;
	}
}
