#include "executing.h"

void	dupe_close(int source_fd, int dest_fd)
{
	dup2(source_fd, dest_fd);
	close(source_fd);
}
