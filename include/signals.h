#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_signal;

void	signal_handler(int sig);

#endif