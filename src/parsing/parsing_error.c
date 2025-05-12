#include "error.h"
#include "parsing.h"

static const char	*_lib_name(void)
{
	return ("parsing");
}

static const char	*_lib_message(int err)
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

static t_error_category	_get_parsing_category(void)
{
	static const t_error_category	lib_category = {
		.name = _lib_name,
		.message = _lib_message
	};

	return (lib_category);
}

void	print_parsing_error(t_error_parsing error, char *word)
{
	t_error_code		error_code;
	t_error_category	error_cat;

	error_cat = _get_parsing_category();
	error_code = make_error(error, &error_cat);
	printf("[%s] %s: %s\n",
		error_name(&error_code),
		error_message(&error_code), word);
}
