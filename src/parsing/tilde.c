#include "parsing.h"
#include <fcntl.h>

static	char *_get_usr_directory(t_alloc *alloc, char *user_name)
{
	char	*line;
	char	**split_line;
	int		fd;

	fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = str_gnl(alloc, fd);
	while (line)
	{
		split_line = str_split(alloc, line, ':');
		if (!split_line && !split_line[0] && !split_line[5])
			return (close(fd), NULL);
		if (str_equals(split_line[0], user_name))
			return (close(fd), split_line[5]);
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
		if (current->content->type == E_WORD)
			_process_tilde_token(ctx, current);
		current = current->next;
	}
}
