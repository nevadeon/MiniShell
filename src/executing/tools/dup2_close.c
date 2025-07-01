#include "executing.h"

void	dup2_close(int source_fd, int dest_fd)
{
	if (source_fd < 0 || dest_fd < 0)
		return ;
	dup2(source_fd, dest_fd);
	close(source_fd);
}
