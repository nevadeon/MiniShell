#ifndef EXECUTING_H
# define EXECUTING_H

# include <unistd.h>
# include <sys/wait.h>

# define CMD_NAME_INDEX 0

typedef struct s_str_list t_str_list;

void	exec_cmd(char **env_paths, t_str_list *arg_list);
void	dup_close(int source_fd, int dest_fd);

#endif
