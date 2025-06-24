#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include <errno.h>
# include "allocator.h"

void	env_set(void *e);
void	*env_get(void);
char	*env_get_var(char *var_name);
char	*env_set_var_value(t_alloc *alloc, char *var_name, char *var_value);

/**
 * @brief return the value of the variable found in the env. Returns "" if not found.
 * @param `var_name` the variable name
 * @param `status` a pointer to the status. Set to 0 if the variable is not found, otherwise 1.
 * @return return the value of the variable found in the env. Returns "" if not found.
 */
char	*env_get_var_value(char *var_name, int *status);

#endif
