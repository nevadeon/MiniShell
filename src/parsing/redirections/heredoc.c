#include "parsing.h"

static void	_expand_var(t_ctx *ctx, char **str_ptr)
{
	size_t	index;

	index = 0;
	if (!*str_ptr)
		return ;
	while ((*str_ptr)[index])
	{
		if ((*str_ptr)[index] == '$')
			process_expanding(ctx, str_ptr, index + 1);
		if (ctx->last_error_type)
			return (throw_error(ctx, E_BAD_SUBSTITUTION, (*str_ptr)));
		index++;
	}
	return ;
}

static void	_hdoc_sigint(int signal, siginfo_t *info, void *ucontext)
{
	(void)signal;
	(void)info;
	(void)ucontext;
	rl_on_new_line();
	rl_replace_line("", 0);
	return ;
}

int	handle_heredoc(t_ctx *ctx, char *delim)
{
	char	*heredoc_string;
	char	*line;
	int		fd[2];

	heredoc_string = str_dup(*ctx->cmd, "");
	init_handler_int(&_hdoc_sigint);
	rl_getc_function = rl_getc;
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			if (ctx->last_exit_code == CTRL_D_TEMP_EXIT_CODE)
			{
				throw_error(ctx, E_HDOC_QUIT, delim);
				break ;
			}
			return (throw_error(ctx, E_HDOC_INT, NULL), -1);
		}
		if (str_equals(line, delim))
			break ;
		heredoc_string = str_vjoin(*(ctx->cmd), 3, heredoc_string, line, "\n");
		free(line);
	}
	toggle_signal(ctx, S_PARENT);
	_expand_var(ctx, &heredoc_string);
	if (pipe(fd) == -1)
		return (throw_error(ctx, E_USE_ERRNO, "ERRNO ERROR"), -1);
	io_dprintf(fd[1], "%s", heredoc_string);
	return (close(fd[1]), fd[0]);
}
