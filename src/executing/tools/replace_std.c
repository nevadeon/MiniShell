#include "executing.h"

int	replace_std(int redir, int std_fileno)
{
	int	std_temporary_fd;

	if (redir < 0 || std_fileno < 0)
		return (-1);
	std_temporary_fd = dup(std_fileno);
	dup2(redir, std_fileno);
	close(redir);
	return (std_temporary_fd);
}
