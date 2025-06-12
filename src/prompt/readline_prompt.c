#include <fcntl.h>
#include <string.h>
#include "minishell.h"

static char	*_get_git_head(void)
{
	static char	buffer[PATH_MAX];
	int			fd;
	int			b_read;

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

char	*readline_prompt(void)
{
	static char	buffer[PATH_MAX + 200];
	char		cwd[PATH_MAX];
	char		*git_head;
	size_t		index;
	size_t		tmp_len;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	index = 0;
	git_head = _get_git_head();
	tmp_len = str_len("\001\033[1;32mminishell\033[0m \033[1;35m");
	str_memcpy(buffer, "\001\033[1;32mminishell\033[0m \033[1;35m", tmp_len);
	index += tmp_len;
	tmp_len = str_len(cwd);
	str_memcpy(buffer + index, cwd, tmp_len);
	index += tmp_len;
	if (git_head)
	{
		tmp_len = str_len("\033[0m \033[1;32mgit:(\033[1;33m");
		str_memcpy(buffer + index, "\033[0m \033[1;32mgit:(\033[1;33m", tmp_len);
		index += tmp_len;
		tmp_len = str_len(git_head);
		str_memcpy(buffer + index, git_head, tmp_len);
		index += tmp_len;
	}
	tmp_len = str_len("\033[1;32m) #\033[0m \002");
	str_memcpy(buffer + index, "\033[1;32m) #\033[0m \002", tmp_len);
	index += tmp_len;
	return (buffer);
}
