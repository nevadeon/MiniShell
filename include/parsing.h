#ifndef PARSING_H
# define PARSING_H

# include "error.h"
# include "ast.h"
# include "str.h"
# include "list.h"

typedef enum e_error_parsing
{
	E_ERR_PARSING_OK = 0,
	E_ERR_PARSING_SYNTAX,
	E_ERR_PARSING_UNEXPECTED_TOKEN,
	E_ERR_PARSING_MISSING_OPERAND,
	E_ERR_PARSING_MISSING_REDIR_TARGET,
	E_ERR_PARSING_LAST_INDEX
}	t_error_parsing;

void		print_parsing_error(t_error_parsing error, char *word);
t_str_list	*compute_pattern(t_allocator *alloc, t_str_list *files, char *pattern);
char		*get_next_word(t_allocator *alloc, char **input);

#endif
