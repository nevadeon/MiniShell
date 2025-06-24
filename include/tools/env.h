#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include <unistd.h>
# include <errno.h>
# include "allocator.h"

char	*env_get_var(char **env, char *var_name);
char	*env_set_var_value(t_ctx *ctx, char *var_name, char *var_value);
char	*env_get_var_value(char **env, char *var_name);

#endif
