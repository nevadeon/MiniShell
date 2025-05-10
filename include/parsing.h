#ifndef PARSING_H
# define PARSING_H

# include "error.h"

typedef enum e_error_parsing
{
	E_ERR_PARSING_OK = 0,
	E_ERR_PARSING_SYNTAX,
	E_ERR_PARSING_UNEXPECTED_TOKEN,
	E_ERR_PARSING_MISSING_OPERAND,
	E_ERR_PARSING_MISSING_REDIR_TARGET,
	E_ERR_PARSING_LAST_INDEX
}	t_error_parsing;

t_error_category	get_parsing_category(void);

#endif