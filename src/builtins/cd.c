#include "minishell.h"
#include "path.h"
#include "env.h"
#include "builtins.h"

static const char	*_lib_name(void)
{
	return ("cd");
}

static const char	*_lib_message(int err)
{
	if (err == E_ERR_CD_OK)
		return ("No error");
	if (err == E_ERR_CD_FILE_EXIST)
		return ("No such file or directory");
	if (err == E_ERR_CD_ARGS)
		return ("Too many arguments");
	if (err == E_ERR_CD_NOT_DIR)
		return ("Not a directory");
	return ("an error occured");
}

static void	_print_err(t_error_cd e, char *path)
{
	t_error_code		code;
	t_error_category	err_cat;

	err_cat = (t_error_category){.name = _lib_name, .message = _lib_message};
	code = make_error(e, &err_cat);
	printf("[%s] %s", error_name(&code), error_message(&code));
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

int	builtin_cd(t_str_list *args)
{
	char		cwd[PATH_MAX];
	char		*path;

	if (!args || !args->content)
		return (chdir(env_get_var_value("HOME")));
	if (args->next)
		return (_print_err(E_ERR_CD_ARGS, NULL), 0);
	path = args->content;
	if (str_equals(path, "-"))
		path = env_get_var_value("OLDPWD");
	if (check_permissions(path))
		return (false);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	env_set_var_value("OLDPWD", cwd);
	return (chdir(path));
}
