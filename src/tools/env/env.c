#include "env.h"

static void	**_env(void)
{
	static void	*env;

	return (&env);
}

inline void	*env_get(void)
{
	return (*_env());
}

inline void	env_set(void *e)
{
	*_env() = e;
}

char	*env_get_var(char *var_name)
{
	char	**env;
	int		len;

	env = env_get();
	len = str_len(var_name);
	while (*env)
	{
		if (str_ncmp(*env, var_name, len) == 0 && (*env)[len] == '=')
			return (*env);
		env++;
	}
	return (NULL);
}

char	*env_get_var_value(char *var_name)
{
	char	*var_value;

	if (str_ncmp(var_name, "$", str_len("$")) == 0)
		return (num_itoa((int) getpid()));
	var_value = env_get_var(var_name);
	if (var_value)
		return (env_get_var(var_name) + str_len(var_name) + 1);
	return ("");
}

char	*env_set_var_value(char *var_name, char *var_value)
{
	char	**env;
	char	*new_var;
	int		i;
	int		len;
	char 	**new_env;

	len = str_len(var_name);
	env = env_get();
	new_var = str_vjoin(E_LFT_TASK, 3, var_name, "=", var_value);
	i = 0;
	while (env[i])
	{
		if (str_ncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (env[i] = new_var, env[i]);
		i++;
	}
	new_env = mem_alloc(E_LFT_PROG, sizeof(char *) * (i + 2));
	str_memcpy(new_env, env, sizeof(char *) * i);
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	env_set(new_env);
	return (new_env[i]);
}
