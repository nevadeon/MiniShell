#ifndef SIGNALS_H
# define SIGNALS_H

# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "minishell.h"


typedef enum e_sigstatus
{
	S_IGNORE = 0,
	S_PARENT,
	S_CHILD,
}	t_sigstatus;

void	toggle_signal(t_ctx *ctx, int toggle);

#endif
