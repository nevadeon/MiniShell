#ifndef ENV_H
# define ENV_H

# include "mem.h"
# include "str.h"
# include "num.h"
# include <unistd.h>

void	env_set(void *e);
void	*env_get(void);
char	*env_get_var(char *var_name);
char	*env_get_var_value(char *var_name);

#endif
