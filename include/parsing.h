#ifndef PARSING_H
# define PARSING_H

# include "allocator.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "str.h"
# include "list.h"
# include "env.h"

typedef enum s_parsing_errors
{
	E_PARS_NO = 0,
	E_PARS_GEN = 1,
	E_PARS_UNEX_TOKEN = 2
}	t_parsing_errors;

typedef struct s_list	t_list;

typedef struct s_str_list
{
	struct s_str_list	*next;
	char				*content;
}	t_str_list;

typedef enum e_token_type
{
	E_WORD,
	E_CONTROL_OPE,
	E_REDIR_OPE
}	t_token_type;

typedef t_token_type	t_node_type;

typedef enum e_redir_type
{
	E_REDIR_IN,
	E_REDIR_HEREDOC,
	E_REDIR_OUT_TRUNC,
	E_REDIR_OUT_APPEND,
	E_REDIR_LAST_INDEX
}	t_redir_type;

typedef enum e_ope_type
{
	E_OPE_PIPE,
	E_OPE_LAST_INDEX
}	t_ope_type;

typedef struct s_redir_list
{
	struct s_redir_list	*next;
	char				*content;
	t_redir_type		type;
}	t_redir_list;

typedef struct s_ast
{
	t_node_type	type;
	union
	{
		struct
		{
			t_str_list		*func;
			t_redir_list	*redir_in;
			t_redir_list	*redir_out;
		}	s_leaf;
		struct
		{
			t_ope_type		type;
			struct s_ast	*left;
			struct s_ast	*right;
		}	s_ope;
	};
}	t_ast;

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

typedef struct s_ast_context
{
	t_token_list	*token_list_item;
	t_ast			*root;
	t_ast			*prev;
	t_ast			*prev_ope;
}	t_ast_context;

void			toggle_pars_err(t_parsing_errors err_code, char *arg);
bool			is_blank_meta(char c);
bool			is_meta(char c);
bool			is_ope(char c);
bool			is_control(char c);
bool			is_redir(char c);
t_redir_type	get_redir_type(char *s);
t_token			*new_token(t_alloc *alloc, char *str, \
					bool expanded, t_token_type type);
t_ast			*parsing(t_alloc *alloc, char **input);
void			remove_comment(t_alloc *alloc, char **input);
t_token_list	*tokenize(t_alloc *alloc, char **input);
void			print_token(t_token *t);
void			tilde_expanding(t_alloc *alloc, t_token_list *token_list);
void			var_expanding(t_alloc *alloc, t_token_list *token_list);
void			word_splitting(t_alloc *alloc, t_token_list *token_list);
void			wildcard_expanding(t_alloc *alloc, t_token_list *token_list);
t_str_list		*compute_pattern(t_alloc *alloc, t_str_list *files, char *pattern);
void			quote_removal(t_alloc *alloc, t_token_list *token_list);
t_ast			*create_ast(t_alloc *alloc, t_ast_context *data);
void			print_ast(t_ast *ast, int indent);

#endif
