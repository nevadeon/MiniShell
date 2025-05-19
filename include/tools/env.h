#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include "allocator.h"

void	env_set(void *e);
void	*env_get(void);
char	*env_get_var(char *var_name);
char	*env_get_var_value(t_allocator *alloc, char *var_name);
char	*env_set_var_value(t_allocator *alloc, char *var_name, char *var_value);

#endif
