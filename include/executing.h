#ifndef EXECUTING_H
# define EXECUTING_H

typedef struct s_ptrlist t_args;
typedef struct s_ast t_ast;

void	execute_ast(t_ast *ast);
void	exec_cmd(char **env_paths, char *cmd_name, t_args *arg_list);

#endif
