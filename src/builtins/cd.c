#include "minishell.h"
#include "path.h"
#include "env.h"
#include "builtins.h"

static const char	*g_cd_error_msg[] = {
	E_ERR_CD_OK = "No error",
	E_ERR_CD_ARGS = "Too many arguments",
	E_ERR_CD_FILE_EXIST = "No such file or directory",
	E_ERR_CD_NOT_DIR = "Not a directory"
}

static void	_print_err(t_error_cd e, char *path)
{
	printf("[cd] %s", g_cd_error_msg[e]);
	if (path)
		printf(": %s", path);
	printf("\n");
}

bool	check_permissions(char *path)
{
	if (!path_check(path, E_PATH_EXIST))
		return (_print_err(E_ERR_CD_FILE_EXIST, path), path);
	if (!path_check(path, E_PATH_IS_DIRECTORY))
		return (_print_err(E_ERR_CD_NOT_DIR, path), path);
	return (false);
}

int	builtin_cd(t_alloc *alloc, char **args)
{
	char	cwd[PATH_MAX];
	char	*path;

	if (!args[1])
	{
		chdir(env_get_var_value(alloc, "HOME"));
		exit(errno);
	}
	if (args[2])
	{
		//wip
		exit();
	}
	path = args->content;
	if (str_equals(path, "-"))
		path = env_get_var_value(alloc, "OLDPWD");
	if (check_permissions(path))
		return (false);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	env_set_var_value(alloc, "OLDPWD", cwd);
	return (chdir(path));
}
