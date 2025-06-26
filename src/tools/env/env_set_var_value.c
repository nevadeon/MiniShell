#include "tools/env.h"
#include "tools/str.h"
#include "tools/num.h"
#include "tools/memory.h"

static char	*set_existing_env_var(char **env,
	char *new_var, size_t name_len)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (!str_ncmp(env[i], new_var, name_len) && env[i][name_len] == '=')
		{
			env[i] = new_var;
			return (new_var);
		}
		i++;
	}
	return (NULL);
}

static char	*add_new_env_var(t_ctx *ctx, char *new_var)
{
	char	**env;
	size_t	count;
	char	**new_env;

	env = *ctx->env;
	count = 0;
	while (env && env[count])
		count++;
	new_env = mem_alloc(*ctx->prog, sizeof(char *) * (count + 2));
	if (env)
		mem_cpy(new_env, env, sizeof(char *) * count);
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	*ctx->env = new_env;
	return (new_var);
}

char	*env_set_var_value(t_ctx *ctx, char *var)
{
	char	*eq;
	size_t	name_len;
	char	*new_var;
	char	**env;
	char	*res;

	eq = str_chr(var, '=');
	if (!eq)
		return (NULL);
	name_len = eq - var;
	new_var = mem_alloc(*ctx->prog, str_len(var) + 1);
	str_memcpy(new_var, var, str_len(var) + 1);
	env = *ctx->env;
	res = set_existing_env_var(env, new_var, name_len);
	if (res)
		return (res);
	return (add_new_env_var(ctx, new_var));
}
