#include "signals.h"
#include "mem.h"
#include "minishell.h"

void	signal_handler(int sig)
{
	g_signal = sig;

	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
