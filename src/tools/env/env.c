#include "tools/env.h"
#include "tools/str.h"
#include "tools/num.h"

char	*env_get_var(char **env, char *var_name)
{
	int		len;

	len = str_len(var_name);
	while (*env)
	{
		if (str_ncmp(*env, var_name, len) == 0 && (*env)[len] == '=')
			return (*env);
		env++;
	}
	return (NULL);
}

char	*env_get_var_value(char **env, char *var_name)
{
	char	*var;
	char	*var_value;

	var = env_get_var(env, var_name);
	if (var)
	{
		var_value = var + str_len(var_name) + 1;
		return (var_value);
	}
	return (NULL);
}

int	env_remove_var(t_ctx *ctx, const char *var_name)
{
	char	**env;
	size_t	name_len;
	int		i;
	int		j;

	env = *ctx->env;
	name_len = str_len(var_name);
	if (!env || !var_name)
		return (0);
	i = -1;
	while (env[++i])
	{
		if (!str_ncmp(env[i], var_name, name_len) && env[i][name_len] == '=')
		{
			j = i - 1;
			while (env[++j])
				env[j] = env[j + 1];
			return (1);
		}
	}
	return (0);
}
