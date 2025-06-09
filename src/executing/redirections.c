#include "minishell.h"

static int	_heredoc(char *stop)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(666);
	}
	while (1)
	{
		str_putfd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || str_ncmp(line, stop, str_clen(line, '\n', false)) == 0)
			break ;
		str_putfd(line, pipe_fd[1]);
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	handle_input_redir(t_redir_list *redir, int pipe_fd)
{
	t_redir_list	*redir_origin;
	int				fd;

	fd = pipe_fd;
	redir_origin = redir;
	if (redir_origin && pipe_fd)
		close(pipe_fd);
	while (redir)
	{
		if (redir->type == E_REDIR_IN)
			fd = open(redir->content, O_RDONLY);
		else if (redir->type == E_REDIR_HEREDOC)
			fd = _heredoc(redir->content);
		if (redir->next)
			close(fd);
		redir = redir->next;
	}
	if (redir_origin || pipe_fd)
		dup_close(fd, STDIN_FILENO);
	return (fd);
}

int	handle_output_redir(t_redir_list *redir, int pipe_fd)
{
	t_redir_list	*redir_origin;
	int				fd;

	fd = pipe_fd;
	redir_origin = redir;
	if (redir_origin && pipe_fd)
		close(pipe_fd);
	while (redir)
	{
		if (redir->type == E_REDIR_OUT_TRUNC)
			fd = open(redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == E_REDIR_OUT_APPEND)
			fd = open(redir->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redir->next)
			close(fd);
		redir = redir->next;
	}
	if (redir_origin || pipe_fd)
		dup_close(fd, STDOUT_FILENO);
	return (fd);
}

