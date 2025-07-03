#include "minishell.h"

void	init_handler_quit(void *func)
{
	struct sigaction	sigquit_handler;

	str_memset(&sigquit_handler, 0, sizeof(struct sigaction));
	sigquit_handler.sa_flags = SA_SIGINFO;
	sigquit_handler.sa_handler = func;
	sigaction(SIGQUIT, &sigquit_handler, NULL);
}
