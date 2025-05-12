#include <fcntl.h>
#include <string.h>
#include "minishell.h"

static char	*_get_git_head(void)
{
	char	git_head[PATH_MAX];
	char	*cursor;
	int		fd;
	int		b_read;
	char	*last_slash;

	fd = open(".git/HEAD", O_RDONLY);
	if (fd != -1)
	{
		b_read = read(fd, git_head, PATH_MAX);
		git_head[b_read - 1] = '\0';
		cursor = git_head;
		last_slash = cursor;
		while (*cursor)
		{
			if (*cursor == '/')
				last_slash = cursor;
			cursor++;
		}
		return (last_slash + 1);
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
