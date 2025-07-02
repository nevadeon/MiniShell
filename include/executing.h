#ifndef EXECUTING_H
# define EXECUTING_H

# include "forward.h"
# include "ast.h"
# include "parsing.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "allocators/allocator.h"

# define CMD_NAME 0

# ifndef IN
#  define IN 1
# endif
# ifndef OUT
#  define OUT 0
# endif

typedef enum e_error
{
	OK,
	E_PIPE,
	E_UNEXPECTED_NODE_TYPE,
}	t_error;

typedef struct s_exec_fds
{
	int	fd1;
	int	fd2;
	int	to_close;
}	t_exec_fds;

typedef struct s_redir_fds
{
	int		in;
	int		out;
	bool	error;
	bool	is_heredoc;
}	t_redir_data;

typedef struct s_pid_list
{
	struct s_pid_list	*next;
	pid_t				pid;
}	t_pid_list;

typedef struct s_exec_data
{
	t_ctx		*c;
	char		**paths;
	t_ast		*root;
	t_pid_list	*processes;
	int			to_close;
}	t_exec_data;

void		execute_ast(t_ctx *ctx, t_ast *ast);
void		execute_ast_recursive(\
				t_ctx *ctx, t_exec_data *data, t_ast *ast, t_exec_fds fds);
void		execute_command(t_ctx *ctx, char **env_paths, char **args);
void		handle_leaf(t_ctx *c, t_exec_data *d, t_leaf *leaf, t_exec_fds fds);
void		handle_ope(t_ctx *c, t_exec_data *d, t_ope *ope, t_exec_fds fds);
bool		handle_redirections(t_ctx *c, t_redir_list *list, t_exec_fds pipe);
void		handle_in(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);
void		_handle_heredoc(t_ctx *c, t_redir_list *list, t_redir_data *redir);
void		handle_trunc(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);
void		handle_append(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);
bool		try_single_builtin(t_ctx *c, t_redir_list *redir_list, char **args);
bool		try_builtin(t_ctx *ctx, char **args);
bool		single_builtin_redirection(
	t_ctx *ctx, t_redir_list *redir_list, int *stdout_cpy, char *cmd_name);

//tools
void		dup2_close(int source_fd, int dest_fd);
t_pid_list	*lst_pid_new(t_alloc *alloc, pid_t pid);
void	close_heredocs(t_ast *ast);

#endif
