/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:51 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 16:02:03 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef void	(*t_redir_open_fn)(\
	t_ctx *ctx, t_redir_list *list, t_redir_data *redir);

typedef struct s_exec_fds
{
	int	out;
	int	in;
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

//core exec functions
void		execute_ast(t_ctx *ctx, t_ast *ast);
void		execute_ast_recursive(\
				t_ctx *ctx, t_exec_data *data, t_ast *ast, t_exec_fds fds);
void		execute_command(t_ctx *ctx, char **env_paths, char **args);
void		handle_leaf(t_ctx *c, t_exec_data *d, t_leaf *leaf, t_exec_fds fds);
void		handle_ope(t_ctx *c, t_exec_data *d, t_ope *ope, t_exec_fds fds);
bool		try_single_builtin(t_ctx *c, t_redir_list *redir_list, char **args);
bool		try_builtin(t_ctx *ctx, char **args);

//redirections
bool		single_builtin_redirection(\
				t_ctx *ctx, t_redir_list *list, int *out_cpy, char *cmd_name);
bool		handle_redirections(t_ctx *c, t_redir_list *list, t_exec_fds pipe);
void		open_append(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);
void		open_heredoc(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);
void		open_input(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);
void		open_truncate(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);
void		close_heredocs(t_ast *ast);

//tools
void		dup2_close(int source_fd, int dest_fd);
t_pid_list	*lst_pid_new(t_alloc *alloc, pid_t pid);

#endif
