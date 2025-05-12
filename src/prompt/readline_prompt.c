#include <fcntl.h>
#include <string.h>
#include "minishell.h"

static char	*_get_git_head(void)
{
	static char	buffer[PATH_MAX];
	int		fd;
	int		b_read;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd == -1)
		return (NULL);
	b_read = read(fd, buffer, PATH_MAX - 1);
	buffer[b_read - 1] = '\0';
	close(fd);
	if (b_read <= 0)
		return (NULL);
	while (b_read)
	{
		if (buffer[b_read] == '/')
			return (&buffer[b_read + 1]);
		b_read--;
	}
	return (NULL);
}

char	*readline_prompt(char *buf, size_t size)
{
	char	cwd[PATH_MAX];
	int		n;
	char	*git_head;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	git_head = _get_git_head();
	if (git_head)
	{
		n = snprintf(buf, size,
			"\033[1;32mminishell\033[0m \033[1;35m%s\033[0m \033[1;32mgit:(\033[1;33m%s\033[1;32m) #\033[0m\n",
			cwd, git_head);
	}
	else
	{
		n = snprintf(buf, size,
			"\033[1;32mminishell\033[0m \033[1;35m%s\033[0m \033[1;32m# \033[0m",
			cwd);
	}
	if (n < 0 || (size_t)n >= size)
		return (NULL);
	return (buf);
}
