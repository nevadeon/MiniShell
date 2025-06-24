#include "env.h"
#include "str.h"
#include "num.h"

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

char	*env_set_var_value(t_ctx *ctx, char *var_name, char *var_value)
{
	char	**env;
	char	*new_var;
	int		i;
	int		len;
	char	**new_env;

	len = str_len(var_name);
	env = *ctx->env;
	new_var = str_vjoin(*ctx->prog, 3, var_name, "=", var_value);
	i = 0;
	while (env[i])
	{
		if (str_ncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] = new_var, env[i]);
		i++;
	}
	new_env = mem_alloc(*ctx->prog, sizeof(char *) * (i + 2));
	str_memcpy(new_env, env, sizeof(char *) * i);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env[i]);
}
