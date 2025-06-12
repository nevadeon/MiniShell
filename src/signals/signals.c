#include "signals.h"
#include "minishell.h"

sig_atomic_t	g_signal = 0;

void signal_handler(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
