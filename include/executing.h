#ifndef EXECUTING_H
# define EXECUTING_H

# include <unistd.h>
# include <sys/wait.h>


void	dup_close(int source_fd, int dest_fd);

#endif
