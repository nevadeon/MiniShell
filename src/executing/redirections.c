#include "executing.h"

static int	_heredoc(char *stop)
{
	t_alloc	*cmd;
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(666);
	}
	cmd = new_mgc_allocator(GNL_BUFFER_SIZE);
	stop = str_vjoin(cmd, 2, stop, "\n");
	while (1)
	{
		str_putfd("> ", STDOUT_FILENO);
		line = str_gnl(cmd, STDIN_FILENO);
		if (!line || str_equals(line, stop))
			break ;
		str_putfd(line, pipe_fd[1]);
	}
	free_allocator(&cmd);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	builtin_redir_out(t_redir_list *out)
{
	int	stdout_backup;
	int	fd;

	stdout_backup = 0;
	if (out)
		stdout_backup = dup(STDIN_FILENO);
	while (out)
	{
		if (out->type == REDIR_OUT_TRUNC)
			fd = open(out->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(out->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd >= 0)
			dup_close(fd, STDOUT_FILENO);
		out = out->next;
	}
	return (stdout_backup);
}

int	builtin_redir_in(t_redir_list *in)
{
	int	stdin_backup;
	int	fd;

	stdin_backup = 0;
	if (in)
		stdin_backup = dup(STDIN_FILENO);
	while (in)
	{
		if (in->type == REDIR_IN)
		{
			fd = open(in->content, O_RDONLY);
			if (fd == -1)
				return (close(stdin_backup), io_dprintf(\
					2, "bash: %s: %s\n", in->content, strerror(errno)), -1);
		}
		else
			fd = _heredoc(in->content);
		if (fd >= 0)
			dup_close(fd, STDIN_FILENO);
		in = in->next;
	}
	return (stdin_backup);
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
		if (redir->type == REDIR_IN)
		{
			fd = open(redir->content, O_RDONLY);
			if (fd == -1)
				return (io_dprintf(\
					2, "bash: %s: %s\n", redir->content, strerror(errno)), -1);
		}
		else if (redir->type == REDIR_HEREDOC)
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
		if (redir->type == REDIR_OUT_TRUNC)
			fd = open(redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_OUT_APPEND)
			fd = open(redir->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redir->next)
			close(fd);
		redir = redir->next;
	}
	if (redir_origin || pipe_fd)
		dup_close(fd, STDOUT_FILENO);
	return (fd);
}
