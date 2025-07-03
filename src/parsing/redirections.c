#include "parsing.h"
#include "signals.h"

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

static int	_read_heredoc_lines(t_ctx *ctx, char *delim, char **heredoc_string)
{
	char	*line;

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
		*heredoc_string = str_vjoin(*(ctx->cmd), 3, *heredoc_string, line, "\n");
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_ctx *ctx, char *delim)
{
	char	*heredoc_string;
	int		fd[2];

	heredoc_string = str_dup(*ctx->cmd, "");
	init_handler_int(&_hdoc_sigint);
	rl_getc_function = rl_getc;
	_read_heredoc_lines(ctx, delim, &heredoc_string);
	toggle_signal(ctx, S_PARENT);
	_expand_var(ctx, &heredoc_string);
	if (pipe(fd) == -1)
		return (throw_error(ctx, E_USE_ERRNO, "ERRNO ERROR"), -1);
	io_dprintf(fd[1], "%s", heredoc_string);
	return (close(fd[1]), fd[0]);
}

bool	handle_redir(t_ctx *ctx, t_token_list **tok_l, t_ast *node)
{
	t_token			*tok;
	t_redir_type	redir_type;
	t_redir_list	*redir;
	int				hdoc_fd;

	hdoc_fd = -1;
	tok = (*tok_l)->content;
	assert((tok->type) == TOK_REDIR_OPE);
	redir_type = get_redir_type(tok->str);
	(*tok_l) = (*tok_l)->next;
	if (!(*tok_l))
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "newline"), false);
	tok = (*tok_l)->content;
	if (get_token_type(tok->str) == TOK_CONTROL_OPE \
		|| get_token_type(tok->str) == TOK_REDIR_OPE)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, tok->str), false);
	if (redir_type == REDIR_HEREDOC)
		hdoc_fd = handle_heredoc(ctx, tok->str);
	redir = mem_alloc(*ctx->cmd, sizeof(t_redir_list));
	if (hdoc_fd == -1)
		*redir = (t_redir_list){.type = redir_type, .filename = tok->str};
	else
		*redir = (t_redir_list){.type = redir_type, .heredoc = hdoc_fd};
	return (lst_add_back(\
		(t_list **)&(node->leaf.redir_list), (t_list *)redir), true);
}
