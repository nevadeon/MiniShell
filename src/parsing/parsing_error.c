#include "error.h"
#include "parsing.h"

static const char	*lib_name(void)
{
	return ("parsing");
}

static const char	*lib_message(int err)
{
	if (err == E_ERR_PARSING_OK)
		return ("No error");
	if (err == E_ERR_PARSING_SYNTAX)
		return ("syntax error");
	if (err == E_ERR_PARSING_UNEXPECTED_TOKEN)
		return ("syntax error near unexpected token");
	if (err == E_ERR_PARSING_MISSING_OPERAND)
		return ("syntax error: missing operand");
	if (err == E_ERR_PARSING_MISSING_REDIR_TARGET)
		return ("syntax error: missing redirection target");
	return ("an error occured");
}

t_error_category	get_parsing_category(void)
{
	static const t_error_category	lib_category = {
		.name = lib_name,
		.message = lib_message
	};

	return (lib_category);
}
