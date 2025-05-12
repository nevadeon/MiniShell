#include "minishell.h"
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
	if (err == E_ERR_CD_NOT_DIR)
		return ("Not a directory");
	return ("an error occured");
}

static void	_print_err(t_error_cd e, t_error_category *cat, char *path)
{
	t_error_code	code;

	code = make_error(e, cat);
	printf("[%s] %s: %s\n", error_name(&code), error_message(&code), path);
}

bool	check_permissions(char *path)
{
	struct stat			sb;
	t_error_category	err_cat;
	int					ret;

	err_cat = (t_error_category){.name = _lib_name, .message = _lib_message};
	ret = access(path, F_OK);
	if (ret == -1)
		return (_print_err(E_ERR_CD_FILE_EXIST, &err_cat, path), path);
	ret = stat(path, &sb) != 0;
	if (!S_ISDIR(sb.st_mode))
		_print_err(E_ERR_CD_NOT_DIR, &err_cat, path);
	return (false);
}

int	builtin_cd(t_strlist *args)
{
	char		cwd[PATH_MAX];
	char		*path;

	if (!args || !args->content)
		return (chdir(env_get_var_value("HOME")));
	if (args->next)
		return (printf("erreur"), 0);
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
