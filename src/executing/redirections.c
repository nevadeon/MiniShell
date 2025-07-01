#include "executing.h"

void	handle_redirections(int redir_fd[2], t_fds pipe_fd)
{
	dup2_close(redir_fd[IN], STDIN_FILENO);
	dup2_close(pipe_fd.in, STDIN_FILENO);
	dup2_close(redir_fd[OUT], STDIN_FILENO);
	dup2_close(pipe_fd.out, STDIN_FILENO);
	if (pipe_fd.prev)
		close(pipe_fd.prev);
}
