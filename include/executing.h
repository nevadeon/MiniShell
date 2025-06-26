#ifndef EXECUTING_H
# define EXECUTING_H

# include "forward.h"
# include "ast.h"
# include "parsing.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "allocators/allocator.h"

# define CMD_NAME 0
# define PIPE_OUT 0
# define PIPE_IN 1

typedef enum e_error
{
	OK,
	ERR_PIPE,
	ERR_UNEXPECTED_NODE_TYPE,
}	t_error;

typedef struct s_pid_list
{
	struct s_pid_list	*next;
	pid_t				pid;
}	t_pid_list;

typedef struct s_exec_data
{
	t_pid_list	*processes;
	t_ctx		*c;
	char		**paths;
	int			to_close;
}	t_exec_data;

t_exec_data	make_exec_data(t_ctx *c);
void		execute_ast(t_ctx *ctx, t_ast *ast);
void		exec_cmd(t_ctx *ctx, char **env_paths, char **args);
int			handle_input_redir(t_alloc *a, t_redir_list *redir, int pipe_fd);
int			handle_output_redir(t_redir_list *redir, int pipe_fd);
void		builtin_redir(t_alloc *a, t_redir_list *in, t_redir_list *out);
void		dup_close(int source_fd, int dest_fd);
t_pid_list	*lst_pid_new(t_alloc *alloc, pid_t pid);
bool		try_single_builtin(t_ctx *ctx, t_ast *ast);

#endif
