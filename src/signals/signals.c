#include "signals.h"
#include "tools/str.h"

#define CTRL_D 4

static t_ctx	*g_ctx = NULL;

int	rl_getc(FILE *stream)
{
	char	c;

	(void)stream;
	if (read(0, &c, 1) <= 0)
		return (EOF);
	if (c == CTRL_D)
		g_ctx->last_exit_code = CTRL_D_TEMP_EXIT_CODE;
	return ((unsigned char)c);
}

void	handle_sigint(int signal, siginfo_t *info, void *ucontext)
{
	(void)signal;
	(void)info;
	(void)ucontext;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (g_ctx)
		g_ctx->last_exit_code = 130;
	return ;
}

void	init_handler_int(void *func)
{
	struct sigaction	sigint_handler;

	str_memset(&sigint_handler, 0, sizeof(struct sigaction));
	sigint_handler.sa_flags = SA_SIGINFO;
	sigint_handler.sa_sigaction = func;
	sigaction(SIGINT, &sigint_handler, NULL);
}

void	init_handler_quit(void *func)
{
	struct sigaction	sigquit_handler;

	str_memset(&sigquit_handler, 0, sizeof(struct sigaction));
	sigquit_handler.sa_flags = SA_SIGINFO;
	sigquit_handler.sa_handler = func;
	sigaction(SIGQUIT, &sigquit_handler, NULL);
}

void	init_handler_pipe(void *func)
{
	struct sigaction	sigpipe_handler;

	str_memset(&sigpipe_handler, 0, sizeof(struct sigaction));
	sigpipe_handler.sa_handler = func;
	sigaction(SIGPIPE, &sigpipe_handler, NULL);
}

void	toggle_signal(t_ctx *ctx, int toggle)
{
	g_ctx = ctx;
	if (toggle == S_PARENT)
	{
		init_handler_int(&handle_sigint);
		init_handler_pipe(SIG_IGN);
		init_handler_quit(SIG_IGN);
	}
	else if (toggle == S_IGNORE)
	{
		init_handler_int(SIG_IGN);
		init_handler_quit(SIG_IGN);
		init_handler_pipe(SIG_IGN);
	}
	else if (toggle == S_CHILD)
	{
		init_handler_pipe(SIG_DFL);
		init_handler_int(SIG_DFL);
		init_handler_quit(SIG_DFL);
	}
}
