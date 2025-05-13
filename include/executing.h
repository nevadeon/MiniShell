#ifndef EXECUTING_H
# define EXECUTING_H

# include <unistd.h>
# include <sys/wait.h>

# define CMD_NAME_INDEX 0

typedef struct s_str_list	t_str_list;
typedef struct s_ast		t_ast;

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
	t_ast		*root;
	t_ast		*last_ope;
	int			prev_pipe_fd;
	int			pipefd[2];
	char		**env_paths;
	t_pid_list	*pid_list;
}	t_exec_data;

void		execute_ast(t_ast *ast);
void		exec_cmd(char **env_paths, t_str_list *arg_list);
void		dup_close(int source_fd, int dest_fd);
t_pid_list	*lst_pid_new(pid_t pid);

#endif
