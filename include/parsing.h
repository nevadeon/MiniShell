#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include "allocator.h"
# include <stdio.h>
# include "str.h"
# include "list.h"
# include "env.h"

typedef enum e_token_type
{
	E_WORD,
	E_CONTROL_OPE,
	E_REDIR_OPE
}	t_token_type;

typedef enum e_redir_type
{
	E_REDIR_IN,
	E_REDIR_HEREDOC,
	E_REDIR_OUT_TRUNC,
	E_REDIR_OUT_APPEND,
	E_REDIR_LAST_INDEX
}	t_redir_type;

typedef struct s_list	t_list;

typedef struct s_str_list
{
	struct s_str_list	*next;
	char				*content;
}	t_str_list;

typedef struct s_token
{
	t_token_type	type;
	bool			expanded;
	char			*str;
}	t_token;

typedef struct s_token_list
{
	struct s_token_list	*next;
	t_token				*content;
}	t_token_list;

bool			is_blank_meta(char c);
bool			is_meta(char c);
bool			is_ope(char c);
bool			is_control(char c);
bool			is_redir(char c);
t_redir_type	get_redir_type(char *s);
t_token			*new_token(t_alloc *alloc, char *str, \
					bool expanded, t_token_type type);
void			parsing(t_alloc *alloc, char **input);
void			remove_comment(t_alloc *alloc, char **input);
t_token_list	*tokenize(t_alloc *alloc, char **input);
void			print_token(t_token *t);
void			tilde_expanding(t_alloc *alloc, t_token_list *token_list);
void			var_expanding(t_alloc *alloc, t_token_list *token_list);
void			word_splitting(t_alloc *alloc, t_token_list *token_list);
void			wildcard_expanding(t_alloc *alloc, t_token_list *token_list);
t_str_list		*compute_pattern(t_alloc *alloc, t_str_list *files, char *pattern);
void			quote_removal(t_alloc *alloc, t_token_list *token_list);

#endif
