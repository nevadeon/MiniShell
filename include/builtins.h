#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

typedef enum	e_error_cd
{
	E_ERR_CD_OK = 0,
	E_ERR_CD_FILE_EXIST,
	E_ERR_CD_ARGS,
	E_ERR_CD_NOT_DIR
}	t_error_cd;

int	builtin_cd(t_str_list *args);

#endif