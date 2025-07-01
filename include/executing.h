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

typedef struct s_fds
{
	int	in;
	int	out;
	int	to_close;
}	t_fds;

typedef struct s_pid_list
{
	struct s_pid_list	*next;
	pid_t				pid;
}	t_pid_list;

typedef struct s_exec_data
{
	char		**paths;
	t_ast		*root;
	t_pid_list	*processes;
}	t_exec_data;

t_exec_data	make_exec_data(t_ctx *c);
void		execute_ast(t_ctx *ctx, t_ast *ast);
void		exec_recursive(\
				t_ctx *ctx, t_exec_data *data, t_ast *ast, t_fds prev);
void		handle_leaf(\
				t_ctx *ctx, t_exec_data *data, t_leaf *leaf, t_fds pipe_fd);
void		handle_ope(t_ctx *ctx, t_exec_data *data, t_ope *ope, t_fds next);
void		execute_command(t_ctx *ctx, char **env_paths, char **args);
void		handle_redirections(int redir_fd[2], t_fds pipe_fd);
bool		try_single_builtin(t_ctx *ctx, int redir_fd[2], char **args);
bool		try_builtin(t_ctx *ctx, char **args);

//tools
void		dup2_close(int source_fd, int dest_fd);
int			replace_std(int	redir_fd, int std_fileno);
t_pid_list	*lst_pid_new(t_alloc *alloc, pid_t pid);
void		close_redirections(t_ast *ast);

#endif
