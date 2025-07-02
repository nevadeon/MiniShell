#ifndef PARSING_H
# define PARSING_H

# include "forward.h"
# include "allocators/allocator.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "tools/str.h"
# include "tools/list.h"
# include "tools/env.h"

typedef enum e_token_type
{
	TOK_WORD,
	TOK_CONTROL_OPE,
	TOK_REDIR_OPE
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	bool			expanded;
}	t_token;

typedef struct s_token_list
{
	struct s_token_list	*next;
	t_token				*content;
}	t_token_list;

typedef struct s_ast_context
{
	t_token_list	*tok_l;
	t_ast			*root;
	t_ast			*prev;
	t_ast			*prev_ope;
}	t_ast_context;

bool			is_blank_meta(char c);
bool			is_meta(char c);
bool			is_ope(char c);
bool			is_control(char c);
bool			is_redir(char c);
t_redir_type	get_redir_type(char *s);
t_token_type	get_token_type(char *s);
t_token			*new_token(t_alloc *alloc, char *str, \
					bool expanded, t_token_type type);
t_token_list	*parsing(t_ctx *ctx, char *input);
void			remove_comment(t_alloc *alloc, char **input);
t_token_list	*tokenize(t_ctx *ctx, char **input);
void			tilde_expanding(t_ctx *ctx, t_token_list *token_list);
void			var_expanding(t_ctx *ctx, t_token_list *token_list);
void			word_splitting(t_ctx *ctx, t_token_list *token_list);
void			wildcard_expanding(t_alloc *alloc, t_token_list *token_list);
t_str_list		*compute_pattern(\
					t_alloc *alloc, t_str_list *files, char *pattern);
void			quote_removal(t_alloc *alloc, t_token_list *token_list);
void			print_ast(t_ast *ast, int indent);
bool			is_var_name_valid(char *str);
bool			handle_redir(t_ctx *ctx, t_token_list **tok_l, t_ast *node);
int				handle_heredoc(t_ctx *ctx, char *delim);
bool			process_expanding(t_ctx *ctx, char **str_ptr, size_t index);

#endif
