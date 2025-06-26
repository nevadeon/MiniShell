#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include <unistd.h>
# include <errno.h>
# include "allocators/allocator.h"

char	*env_get_var(char **env, char *var_name);
char	*env_set_var_value(t_ctx *ctx, char *var);
char	*env_get_var_value(char **env, char *var_name);
int		env_remove_var(t_ctx *ctx, const char *var_name);

#endif
